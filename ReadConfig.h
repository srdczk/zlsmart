//
// Created by srdczk on 2019/12/23.
//

#ifndef READCONFIG_H
#define READCONFIG_H

#include <memory>
#include <string>
#include <unordered_map>
#include "NotCopyable.h"

namespace zlsmart {
    // 单例
    class ReadConfig : public NotCopyable {
    public:
        using ReadConfigPtr = std::shared_ptr<ReadConfig>;
        static ReadConfigPtr &instance();
        const std::string &get(const std::string &key);
    private:
        explicit ReadConfig(const std::string &path);
        // 去除空格
        void trim(std::string &s);
        static ReadConfigPtr ptr_;
        std::unordered_map<std::string, std::string> map_;
    };
}


#endif //ZLSMART_READCONFIG_H
