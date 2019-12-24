//
// Created by srdczk on 2019/12/23.
//

#include <cstring>
#include <fstream>
#include "ReadConfig.h"

namespace zlsmart {

    ReadConfig::ReadConfigPtr ReadConfig::ptr_ = nullptr;

    ReadConfig::ReadConfigPtr &ReadConfig::instance() {
        if (!ptr_) ptr_ = std::shared_ptr<ReadConfig>(new ReadConfig("./conf/zlsmart.conf"));
        return ptr_;
    }

    const std::string &ReadConfig::get(const std::string &key) {
        if (!map_.count(key)) map_[key] = "NotExist";
        return map_[key];
    }

    ReadConfig::ReadConfig(const std::string &path) {
        // read ;
        std::ifstream fis(path);
        if (fis && fis.is_open()) {
            std::string line;
            while (getline(fis, line)) {
                trim(line);
                uint64_t pos = line.find('=');
                if (pos != std::string::npos) map_[line.substr(0, pos)] = line.substr(pos + 1);
            }
        }
    }

    void ReadConfig::trim(std::string &s) {
        auto it = s.begin();
        while (it != s.end()) {
            if (*it == ' ') it = s.erase(it);
            else ++it;
        }
    }

}
