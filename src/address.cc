//
// Created by srdczk on 2019/11/24.
//
#include "address.h"
#include <arpa/inet.h>
#include <string.h>
namespace zlsmart {
    Address::Address(ushort family, int port, const char *ip) {
        memset(&addr_, 0, sizeof(addr_));
        addr_.sin_family = family;
        addr_.sin_port = htons(port);
        inet_pton(family, ip, &addr_.sin_addr);
    }
    sockaddr *Address::AddrPtr() const {
        return (sockaddr *) &addr_;
    }
    socklen_t Address::AddrLen() const {
        return sizeof(addr_);
    }
}

