//
// Created by srdczk on 2019/11/24.
//

#ifndef ZLSMART_EPOLL_H
#define ZLSMART_EPOLL_H


#include <bits/stdc++.h>
#include <sys/epoll.h>
#include "types.h"
#include "noncopyable.h"

namespace zlsmart {
    // 不可复制
    class Epoll : public Noncopyable {
    public:
        // epoll 的智能指针
        typedef std::shared_ptr<Epoll> ptr;
        // 初始化, 包括epoll_size_ 和 最大监听事件数
        void Init(int epoll_size = 5000, int max_events = 1024);

        void Add(int fd, bool isET = 1, bool isOneshot = 1);
        void Remove(int fd);

    private:
        // epoll 句柄
        int max_events_;
        int epoll_size_;
        int epfd;
        EpollEvent *events;
        std::vector<int> fds;
    };
}
#endif //ZLSMART_EPOLL_H
