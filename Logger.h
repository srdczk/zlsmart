//
// Created by srczk on 2019/12/23.
//

#ifndef LOGGER_H
#define LOGGER_H

#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <atomic>
#include <fstream>
#include "NotCopyable.h"

namespace zlsmart {
    enum class Level { INFO, WARN, ERROR };
    // 做成 单例模式
    class Logger : public NotCopyable {
    public:
        using LoggerPtr = std::shared_ptr<Logger>;
        ~Logger();
        // 单例模式 获取唯一实例
        static const LoggerPtr &instance();
        // 追加 日志, 向外界提供的接口, 会被多个线程调用
        void append(Level, std::initializer_list<std::string>);
        // 停止, 调用 join 等待 写入 完成
        void stop();
    private:
        // 构造函数
        explicit Logger(const std::string &);
        static std::string errorHandler(int error);
        static void init();
        // 写入日志, 线程 该干的活儿
        void writeLog();
        static LoggerPtr ptr_;
        // 多线程 只初始化 一次
        static pthread_once_t ponce_;
        // 缓冲区的大小
        static const unsigned BUFSIZE;
        // 文件输出流
        std::ofstream out_;
        // 主要 的 工作线程, 负责 写入 log
        std::shared_ptr<std::thread> thread_;
        std::mutex mutex_;
        // 两个条件变量实现 append 和 write 的互斥操作
        std::condition_variable condA_, condB_;
        // 待写入 以及正在写入的 缓冲
        std::vector<std::string> waitWrite_, write_;
        // 两个缓冲 的 size
        unsigned waitSize_, writeSize_;
        // 是否正在 运行
        std::atomic<bool> running_;
    };
}

#endif //LOGGER_H
