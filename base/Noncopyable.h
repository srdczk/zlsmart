//
// Created by srdczk on 2019/12/16.
//

#ifndef NONCOPYABLE_H
#define NONCOPYABLE_H
// 不可复制类
namespace zlsmart {
    class Noncopyable {
    public:
        Noncopyable() = default;
        ~Noncopyable() = default;
        Noncopyable(const Noncopyable&) = delete;
        Noncopyable &operator=(const Noncopyable &) = delete;
    };
}
#endif //NONCOPYABLE_H
