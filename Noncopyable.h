//
// Created by admin on 2019/12/23.
//

#ifndef NONCOPYABLE_H
#define NONCOPYABLE_H

namespace zlsmart {
    class Noncopyable {
    public:
        Noncopyable() = default;
        ~Noncopyable() = default;
        Noncopyable(const Noncopyable &) = delete;
        Noncopyable &operator=(const Noncopyable &) = delete;
    };
}

#endif //ZLSMART_NONCOPYABLE_H
