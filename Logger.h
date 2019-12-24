//
// Created by admin on 2019/12/23.
//

#ifndef LOGGER_H
#define LOGGER_H

#include <memory>
#include <vector>
#include <fstream>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <thread>
#include "Noncopyable.h"

namespace zlsmart {
    enum class Level { INFO, WARN, ERROR };
class Logger : public Noncopyable {
    public:
        using cond = std::condition_variable;
        using LoggerPtr = std::shared_ptr<Logger>;
        static const LoggerPtr &instance();
        void stop();
        void append(Level, std::initializer_list<std::string> );
        ~Logger();
    private:
        explicit Logger(const std::string &);

        void writeLog();

        // 多线程 只 初始化 一次
        static void init();

        static std::string handError(int error);

        static LoggerPtr ptr_;
        // 多线程 只会 初始 化 一次, 保证线程 安全
        static pthread_once_t ponce_;
        // 写入 流
        std::ofstream out_;
        std::shared_ptr<std::thread> thread_;
        static const unsigned BUFSIZE;
        std::vector<std::string> curWirte_; // 待写入的日志
        // 在写入日志
        std::vector<std::string> write_;
        // 记录两个缓冲的 大小
        unsigned curSize_, writeSize_;
        // 互斥量
        std::mutex mutex_;
        // 两个 条件变量 <--> 生产者 消费者模式
        cond condA_;
        cond condB_;
        std::atomic<bool> running_;
    };
}


#endif //ZLSMART_LOGGER_H
