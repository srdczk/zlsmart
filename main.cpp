#include "Logger.h"
//#include <bits/stdc++.h>

int main() {

    auto ptr = zlsmart::Logger::instance();

    for (int i = 0; i < 100; ++i) {
        std::string msg = "NIM" + std::to_string(i);
        std::thread t([msg]() {
            zlsmart::Logger::instance()->append(zlsmart::Level::WARN, {msg});
        });
        t.join();
    }
    ptr->stop();
    return 0;
}