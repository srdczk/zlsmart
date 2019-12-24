//
// Created by srdczk on 2019/12/23.
//


#include <cerrno>
#include <cstring>
#include <functional>
#include <iostream>
#include "Logger.h"
#include "ReadConfig.h"

namespace zlsmart {
    // 静态变量 初始化
    Logger::LoggerPtr Logger::ptr_ = nullptr;
    pthread_once_t Logger::ponce_ = PTHREAD_ONCE_INIT;
    const unsigned Logger::BUFSIZE = 20;

    Logger::Logger(const std::string &logFile): waitWrite_(BUFSIZE), write_(BUFSIZE), waitSize_(0), writeSize_(0), running_(true) {
        out_.open(logFile);
        if (!out_.good()) {
            // printf 线程安全, 尽量使用
            printf("Open log File Error\n");
            // 线程安全 退出
            quick_exit(EXIT_FAILURE);
        }
    }

    // 获取 唯一 实例, init 多线程 只会被 调用 一次
    const Logger::LoggerPtr& Logger::instance() {
        pthread_once(&ponce_, &Logger::init);
        return ptr_;
    }

    void Logger::init() {
        if (!ptr_) ptr_ =
                Logger::LoggerPtr(
                        new Logger(ReadConfig::instance()
                        ->get("logfile")));
        ptr_->thread_ = std::make_shared<std::thread>(std::bind(&Logger::writeLog, ptr_));
    }

    // 析构函数
    Logger::~Logger() {
        out_.close();
        printf("Logger exit");
    }

    void Logger::writeLog() {

        while (running_) {
            {
                std::unique_lock<std::mutex> lck(mutex_);
                // 待写入 缓冲区没有满
                if (waitSize_ < BUFSIZE && running_) {
                    // 当 一直 循环
                    while (condA_.wait_for(lck, std::chrono::seconds(5)) == std::cv_status::no_timeout) {
                        if (waitSize_ == BUFSIZE || !running_) break;
                    }
                }
                // 如果 待缓冲 区 有可以写入的
                if (waitSize_) {
                    std::swap(waitSize_, writeSize_);
                    waitSize_ = 0;
                    std::swap(waitWrite_, write_);
                }
            }
            // 临界区 结束
            // 操作 waitSize_ 需要上锁, 而 操作 write不用上锁
            if (writeSize_ == BUFSIZE) condB_.notify_all();
            for (unsigned i = 0; i < writeSize_; ++i) {
                out_ << write_[i] << "\n";
            }
            out_ << std::flush;
            // 写完成 后
            writeSize_ = 0;
        }

        // running false <--> 如果 待写 缓冲区 中 还有 未写入 的
        std::lock_guard<std::mutex> lock(mutex_);
        std::cout << waitSize_ << "\n";
        if (waitSize_) {
            for (unsigned i = 0; i < waitSize_; ++i) {
                out_ << waitWrite_[i] << "\n";
            }
            out_ << std::flush;
            waitSize_ = 0;
        }
    }

    void Logger::append(zlsmart::Level level, std::initializer_list<std::string> list) {
        if (!running_) return;
        // 向 待写缓冲区中添加 log
        // 线程 安全 的 时间
        // 能够被 多个线程 调用
        auto now = std::chrono::system_clock::now();
        auto nowTime = std::chrono::system_clock::to_time_t(now);
        struct tm tmBuf{};
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
                msg += errorHandler(errno) + " ";
                break;
            default:
                msg += " UnKown ";
                break;
        }
        for (const auto &str : list)
            msg += str + " ";


        // 操作 waitSize_ 加锁
        {
            std::unique_lock<std::mutex> lck(mutex_);
            while (waitSize_ >= BUFSIZE) {
                condA_.notify_one();
                condB_.wait(lck, [this]() { return waitSize_ < BUFSIZE; });
            }
            // 减少复制
            waitWrite_[waitSize_++] = std::move(msg);
        }

        if (level == Level::ERROR) stop();

    }

    void Logger::stop() {
        running_ = false;
        if (thread_->joinable()) thread_->join();
        // 写线程 唤醒
        condA_.notify_one();
        printf("Logger stop\n");
    }

    std::string Logger::errorHandler(int error) {
        char buff[128], *errStr;
        std::memset(buff, '\0', sizeof(buff));
        // 线程 安全 错误 转换
        errStr = strerror_r(error, buff, sizeof(buff));
        if (buff[0] == '\0')
            return std::string(errStr);
        else
            return std::string(buff);
    }

}