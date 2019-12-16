//
// Created by srdczk on 2019/12/16.
//

#include "InetAddress.h"

namespace zlsmart {
    InetAddress::InetAddress(std::string ip, uint16_t port) {
        // 初始化结构体
        std::memset(&addr_, '\0', sizeof(addr_));
        addr_.sin_family = AF_INET;
        inet_pton(AF_INET, ip.data(), &addr_.sin_addr);
        addr_.sin_port = htons(port);
    }
    InetAddress::InetAddress(const sockaddr_in &addr) {
        std::memcpy(&addr_, &addr, sizeof(addr));
    }
    std::string InetAddress::ip() const {
        // getIp
        // 返回需要的 ip 地址
        //
    }
    uint16_t InetAddress::port() const {

    }
    std::string InetAddress::ipAndPort() const {

    }
    void InetAddress::setIpAndPort(std::string ip, uint16_t port) {
        inet_pton(AF_INET, ip.data(), &addr_.sin_addr);
        addr_.sin_port = htons(port);
    }

    struct sockaddr* InetAddress::sockaddr() const {
        return (struct sockaddr *)&addr_;
    }

}