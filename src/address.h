//
// Created by srdczk on 2019/11/23.
//

#ifndef ZLSMART_ADDRESS_H
#define ZLSMART_ADDRESS_H

#include <netinet/in.h>

/**
 * 地址类型, 封装ipv4 tcp
 */
namespace zlsmart {
class Address {
public:
    Address(ushort family = AF_INET, int port = 9999, const char *ip = "127.0.0.1");
    sockaddr *AddrPtr() const;
    socklen_t AddrLen() const;
private:
    sockaddr_in addr_;
};
}

#endif //ZLSMART_ADDRESS_H
