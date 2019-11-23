//
// Created by srdczk on 2019/11/23.
//

#ifndef ZLSMART_NONCOPYABLE_H
#define ZLSMART_NONCOPYABLE_H
namespace zlsmart {
    // 不可复制类,
    // 复制构造函数 和 赋值都删除
    class Noncopyable {
    public:
        Noncopyable() = default;
        ~Noncopyable() = default;
        Noncopyable(const Noncopyable &noncopyable) = delete;
        Noncopyable &operator=(const Noncopyable &noncopyable) = delete;
    };
}
#endif //ZLSMART_NONCOPYABLE_H
