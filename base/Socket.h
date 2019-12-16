//
// Created by srdczk on 2019/12/16.
//

#ifndef SOCKET_H
#define SOCKET_H

#include "Noncopyable.h"

namespace zlsmart {
    // Socket api 的封装
    // 不可复制
    class Socket : public Noncopyable {
    public:
        explicit Socket(int sockfd): sockfd_(sockfd) {}
        ~Socket();

        int getFd() const { return sockfd_; }
        // 绑定 Address
        void bind(const);
        // 建立监听数量
        void listen(int size);

        bool accept();

        // 设置端口复用
        void setReusePort();
        void setTcpNoDelay();
        void setKeepAlive();

    private:
        int sockfd_;
    };
}


#endif //ZLSMART_SOCKET_H
