//
// Created by srdczk on 2019/12/16.
//

#ifndef INETADDRESS_H
#define INETADDRESS_H

#include <arpa/inet.h>
#include <cstring>
#include <string>

namespace zlsmart {

    class InetAddress {
    public:
        InetAddress(std::string ip, uint16_t port);

        void setIpAndPort(std::string ip, uint16_t port);

        // 通过传入socketaddrin 结构体
        explicit InetAddress(const sockaddr_in &addr);

        std::string ip() const;

        std::string ipAndPort() const;

        uint16_t port() const;

        struct sockaddr *sockaddr() const;

    private:

        struct sockaddr_in addr_;

    };
}


#endif //ZLSMART_INETADDRESS_H
