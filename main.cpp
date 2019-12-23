//
// Created by admin on 2019/12/23.
//

#include <iostream>
#include "ReadConfig.h"

int main() {
    zlsmart::ReadConfig::ReadConfigPtr ptr = zlsmart::ReadConfig::instance();
//    logfile =./conf/httpd.log
//    port=9999
//    host=Any
//    listen_num=100
//    thread_num=2
//    epoll_num=100
    std::cout << ptr->get("host") << "\n";
    std::cout << ptr->get("port") << "\n";
    std::cout << ptr->get("listen_num") << "\n";
    std::cout << ptr->get("epoll_num") << "\n";
    return 0;
}
