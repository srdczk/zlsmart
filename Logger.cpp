//
// Created by admin on 2019/12/23.
//

#include <iostream>
#include "Logger.h"
#include "ReadConfig.h"


namespace zlsmart {
    // 静态变量
    Logger::LoggerPtr Logger::ptr_ = nullptr;
    pthread_once_t Logger::ponce_ = PTHREAD_ONCE_INIT;
    const int Logger::BUFSIZE = 20;

    const Logger::LoggerPtr &Logger::instance() {
        pthread_once(&ponce_, init);
        if (!ptr_) init();
        return ptr_;
    }

    void Logger::init() {
        if (!ptr_) ptr_ = std::shared_ptr<Logger>(new Logger(zlsmart::ReadConfig::instance()
                ->get("logfile")));
        // 初始化 线程
    }

    Logger::~Logger() {
        // 关闭文件
        out_.close();
        std::cout << "Logger exit\n";
    }

    Logger::Logger(const std::string &logFile): curWirte_(BUFSIZE), write_(BUFSIZE), curSize_(0), writeSize_(0), running_(true) {
        out_.open(logFile, std::ios::app);
        if (!out_.good()) {
            std::cerr << "open logFile fail\n";
            // 多线程退出
            quick_exit(EXIT_FAILURE);
        }
    }
}