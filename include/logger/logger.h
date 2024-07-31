#ifndef LOGGER_H
#define LOGGER_H
#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fmt/core.h>
#include <fmt/chrono.h>
#include <thread>
#include <mutex>

namespace LogLevel {
    enum LogLevel { DEBUG, INFO, WARN, ERROR };

    constexpr const char *toString(LogLevel level) {
        switch (level) {
            case DEBUG: return "DEBUG";
            case INFO: return "INFO";
            case WARN: return "WARN";
            case ERROR: return "ERROR";
            default: return "UNKNOWN";
        }
    }
}

class Logger {
    std::mutex log_mutex;
    const std::string name;
    std::ostream &out;

    std::string formatLog(LogLevel::LogLevel level, const std::string &message);

public:
    explicit Logger(std::string name, std::ostream &out = std::cout);

    void logMessage(LogLevel::LogLevel level, const std::string &message);
};


#endif //LOGGER_H
