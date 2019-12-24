//
// Created by srdczk on 2019/12/23.
//

#ifndef BUFFER_H
#define BUFFER_H

#include "NotCopyable.h"
#include <string>

namespace zlsmart {
    template <typename T>
    class Buffer : public NotCopyable {
    public:
        Buffer(): Buffer(0) {}

        explicit Buffer(unsigned size): size_(0), capacity_(size > INITTIAL_CAPACITY ? size : INITTIAL_CAPACITY), objs_(new T[capacity_]) {}

        ~Buffer() {
            if (objs_) delete[] objs_;
            objs_ = nullptr;
        }

        unsigned size() const { return size_; }

        unsigned capacity() const { return capacity_; }

        void append(const T *ts, unsigned len) {
            if (size_ + len > capacity_) assign(size_ + len);
            for (unsigned i = 0; i < len; ++i) {
                objs_[size_ + i] = ts[i];
            }
            size_ += len;
        }

        void append(const std::string &s) {
            if (size_ + s.length() > capacity_) assign(size_ + s.length());
            for (unsigned i = 0; i < s.length(); ++i) {
                objs_[size_ + i] = s[i];
            }
            size_ += s.length();
        }

    private:

        void assign(unsigned newCapacity) {
            if (newCapacity < capacity_) return;
            T *oldObj = objs_;
            objs_ = new T[newCapacity];
            for (unsigned i = 0; i < size_; ++i) objs_[i] - oldObj[i];
            capacity_ = newCapacity;
            delete[] oldObj;
            oldObj = nullptr;
        }

        static const int INITTIAL_CAPACITY = 32;
        unsigned capacity_;
        T *objs_;
        unsigned size_;
    };
}

// 内存池实现
#endif //BUFFER_HPP
