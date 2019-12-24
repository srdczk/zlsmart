//
// Created by admin on 2019/12/23.
//
#include <cstring>
#include <cerrno>
#include <iostream>
#include <functional>
#include "Logger.h"
#include "ReadConfig.h"


namespace zlsmart {
    // 静态变量
    Logger::LoggerPtr Logger::ptr_ = nullptr;
    pthread_once_t Logger::ponce_ = PTHREAD_ONCE_INIT;
    const unsigned Logger::BUFSIZE = 20;

    const Logger::LoggerPtr &Logger::instance() {
        pthread_once(&ponce_, &Logger::init);
        return ptr_;
    }

    void Logger::init() {
        if (!ptr_) ptr_ = std::shared_ptr<Logger>(new Logger(zlsmart::ReadConfig::instance()
                ->get("logfile")));
        // 初始化 线程
        // 绑定 writeLog
        ptr_->thread_ = std::make_shared<std::thread>(std::bind(&Logger::writeLog, ptr_));
    }

    Logger::~Logger() {
        // 关闭文件
        out_.close();
        std::cout << "Logger exit\n";
    }
    // 只会被初始化 一次
    Logger::Logger(const std::string &logFile): curWirte_(BUFSIZE), write_(BUFSIZE), curSize_(0), writeSize_(0), running_(true) {
        out_.open(logFile, std::ios::app);
        if (!out_.good()) {
            std::cerr << "open logFile fail\n";
            // 多线程退出
            quick_exit(EXIT_FAILURE);
        }
    }
    void Logger::writeLog() {
        // 写 日志
        while (running_) {
//            std::cout << "I'm running\n";
            std::unique_lock<std::mutex> lck(mutex_);
            if (curSize_ < BUFSIZE && running_) {
                // 等待 待缓冲区 满
                while (condA_.wait_for(lck, std::chrono::seconds(5)) == std::cv_status::no_timeout) {
                    if (curSize_ == BUFSIZE || !running_) break;
                }
            }
            // 如果 待写缓冲区域 > 0
            if (curSize_) {
                std::swap(curSize_, writeSize_);
                // 待写缓冲 区域清空
                curSize_ = 0;
                std::swap(curWirte_, write_);
            }
            // 写入 之后 并且 唤醒 condB_;
            for (unsigned i = 0; i < writeSize_; ++i) {
                out_ << write_[i] << "\n";
            }
            out_ << std::flush;
            unsigned tmp = writeSize_;
            writeSize_ = 0;
            if (tmp) condB_.notify_all();
        }
        // 如果 已经 stop 但是 代写入区域还有 数据
        std::lock_guard<std::mutex> guard(mutex_);
        if (curSize_) {
            for (unsigned i = 0; i < curSize_; ++i) {
                out_ << curWirte_[i] << "\n";
            }
            out_ << std::flush;
            curSize_ = 0;
        }
    }
    void Logger::append(zlsmart::Level level, std::initializer_list<std::string> list) {
        // 线程 安全 的 时间
        // 能够被 多个线程 调用
        auto now = std::chrono::system_clock::now();
        auto nowTime = std::chrono::system_clock::to_time_t(now);
        struct tm tmBuf;
        localtime_r(&nowTime, &tmBuf); //将time_t转换为当地时区的时间日期，线程安全
        char formatTime[32];
        strftime(formatTime, sizeof(formatTime), "%Y/%m/%d %X", &tmBuf);
        std::string msg(formatTime);
        switch (level) {
            case Level::INFO:
                msg += " INFO ";
                break;
            case Level::WARN:
                msg += " WARN ";
                break;
            case Level::ERROR:
                msg += " ERROR ";
                msg += handError(errno) + " ";
                break;
            default:
                msg += " UnKown ";
                break;
        }
        for (const auto &str : list)
            msg += str + " ";

        // 加入 待缓冲 区域
        {
            std::unique_lock<std::mutex> lck(mutex_);
            while (curSize_ >= BUFSIZE) {
                condA_.notify_one();
                condB_.wait(lck, [this]() { return this->curSize_ < BUFSIZE; });
            }
            // 减少复制
            curWirte_[curSize_++] = std::move(msg);
        }

        if (level == Level::ERROR) {
            stop();
        }
    }

    void Logger::stop() {
        running_ = false;
        thread_->join();
        // 唤醒 写 线程
        condA_.notify_one();
        std::cout << "Log Stop\n";
    }

    std::string Logger::handError(int error) {
        char buff[128], *errStr;
        std::memset(buff, '\0', sizeof(buff));
        // 线程 安全 转换
        errStr = strerror_r(error, buff, sizeof(buff));
        if (buff[0] == '\0')
            return std::string(errStr);
        else
            return std::string(buff);
    }
}