#include "Logger.h"

int main() {


    auto ptr = zlsmart::Logger::instance();

    for (int i = 0; i < 100; ++i) {

        std::string msg = "NIMA" + std::to_string(i);
        std::thread t([msg, ptr, i]() {
            if (i == 50) ptr->append(zlsmart::Level::ERROR, {msg});
            else ptr->append(zlsmart::Level::INFO, {msg});
        });
        t.join();
    }

    ptr->stop();

    return 0;

}