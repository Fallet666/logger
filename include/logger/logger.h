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

namespace Logger {
    const std::string RESET = "\033[0m";
    const std::string WHITE = "\033[37m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string RED = "\033[31m";

    enum LogLevel { DEBUG, INFO, WARN, ERROR };

    std::string toString(LogLevel level, bool use_colors);

    class Logger {
        bool use_colors = true;
        std::mutex log_mutex;
        std::string name;
        std::ostream *out;
        LogLevel log_level;

        std::string formatLog(LogLevel level, const std::string &message);

    public:
        explicit Logger(std::string name, std::ostream &out = std::cout, LogLevel level = DEBUG);

        void logMessage(LogLevel level, const std::string &message);

        void setLogLevel(LogLevel log_level);

        void setName(const std::string &name);

        void setOut(std::ostream &out);
    };
}

#endif //LOGGER_H
