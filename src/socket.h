//
// Created by srdczk on 2019/11/23.
//

#ifndef ZLSMART_SOCKET_H
#define ZLSMART_SOCKET_H

#include <memory>
#include <sys/socket.h>
#include "noncopyable.h"
#include "address.h"
namespace zlsmart {
    // 不可复制
    // 协议类型
enum SocketType {
    TCP = SOCK_STREAM,
    UDP = SOCK_DGRAM
};
// 协议族
enum SocketFamily {
    IPv4 = AF_INET,
    IPv6 = AF_INET6
};
// 可构造智能指针, 不可复制
class Socket : public std::enable_shared_from_this<Socket>, Noncopyable {
public:
    typedef std::shared_ptr<Socket> ptr;
    /**
     *  创建 TCP 的Socket
     * @param address
     * @return Socket
     */
    static Socket::ptr CreateTCP(zlsmart::Address::ptr address);
    /**
     * 创建 UDP 的Socket
     * @param address
     * @return Socket
     */
    static Socket::ptr CreateUDP(zlsmart::Address::ptr address);
    // 创建ipv4 的 TCP Socket
    static Socket::ptr CreateTCPSocket();
    // 创建ipv4 的 UDP Socket
    static Socket::ptr CreateUDPSocket();
    // 创建ipv6 的 TCP Socket
    static Socket::ptr CreateTCPSocket6();
    // 创建ipv6 的 UDP Socket
    static Socket::ptr CreateUDPSocket6();
    // 构造函数
    Socket(int family, int type, int protocol = 0);
    // 析构函数
    virtual ~Socket();

private:
    // socket 文件描述符
    int fd_;
    // 类型
    int type_;
    // 协议族
    int family_;
    // 协议
    int protocol_;
    // 判断是否建立了连接
    bool is_connected_;
    // 本地地址
    Address::ptr local_addr_;
    // 远端地址
    Address::ptr remote_addr_;
};
}
#endif //ZLSMART_SOCKET_H
