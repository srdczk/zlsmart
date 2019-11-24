//
// Created by srdczk on 2019/11/23.
//
#include "socket.h"

namespace zlsmart {
    Socket::Socket(bool init, int domain, int type, int protocol) {
        if (init) {
            if ((fd_ = socket(domain, type, protocol)) == -1) enable_ = 0;
        }
    }
    bool Socket::Bind(const zlsmart::Address &address) {
        if (!enable_) return false;
        // 绑定到地址上
        if (bind(fd_, address.AddrPtr(), address.AddrLen()) == -1) return 0;
        return true;
    }

    Socket& Socket::Accept(const zlsmart::Address &address, bool is_blocking) {
        // 如果不可用
        if (!enable_) return *this;
        Socket socket(false);
        socklen_t size = address.AddrLen();
        int cfd = accept(fd_, address.AddrPtr(), &size);
        if (cfd == -1) {
            socket.enable_ = false;
        } else {
            socket.fd_ = cfd;
            socket.isblocking_ = is_blocking;
        }
        return socket;
    }

    bool Socket::Listen(uint32_t listen_num) {
        if (!enable_) return false;
        if (listen(fd_, listen_num) == -1) return 0;
        return true;
    }
    // 连接
    bool Socket::Connect(zlsmart::Address &address) {
        if (!enable_) return false;
        if (connect(fd_, address.AddrPtr(), address.AddrLen()) == -1) return false;
        return true;
    }
    void Socket::Close() {
        if (enable_ && fd_ != -1) close(fd_);
    }
    int Socket::GetFd() const { return fd_; }
    bool Socket::GetEnable() const { return enable_; }
    bool Socket::GetIsBlocking() const { return isblocking_; }
}
