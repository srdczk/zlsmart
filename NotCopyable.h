//
// Created by chengzekun on 19-12-24.
//

#ifndef NOTCOPYABLE_H
#define NOTCOPYABLE_H


namespace zlsmart {
    class NotCopyable {
    public:
        NotCopyable() = default;
        ~NotCopyable() = default;
        NotCopyable(const NotCopyable &) = delete;
        NotCopyable(NotCopyable &&) = delete;
        NotCopyable &operator=(const NotCopyable &) = delete;
        NotCopyable &operator=(NotCopyable &&) = delete;
    };
}

#endif //ZLSMART_NOTCOPYABLE_H
