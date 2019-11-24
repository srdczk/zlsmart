//
// Created by srdczk on 2019/11/24.
//
#include "epoll.h"

namespace zlsmart {
    void Epoll::Init(int epoll_size, int max_events) {
        epoll_size_ = epoll_size;
        max_events_ = max_events;
        epfd = epoll_create(epoll_size);
        epoll_event es[max_events];
        events = es;
    }

}

