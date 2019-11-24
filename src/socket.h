//
// Created by srdczk on 2019/11/23.
//

#ifndef ZLSMART_SOCKET_H
#define ZLSMART_SOCKET_H

#include <memory>
#include <unistd.h>
#include <sys/socket.h>
#include "noncopyable.h"
#include "address.h"

namespace zlsmart {
    // 封装Socket
    class Socket {
    public:
        Socket(bool init = true, int domain = PF_INET, int type = SOCK_STREAM, int protocol = 0);
        // 析构函数
        ~Socket() = default;
        bool Bind(const Address &address);
        // Accept 一个, 生成一个Socket
        Socket &Accept(const Address &address, bool is_blocking);
        bool Listen(uint32_t listen_num = 5);
        bool Connect(Address &address);
        void Close();
        int GetFd() const;
        bool GetEnable() const;
        bool GetIsBlocking() const;
    private:
        // 句柄
        int fd_ = -1;
        bool enable_ = true;
        bool isblocking_ = true;
    };
}
#endif //ZLSMART_SOCKET_H
