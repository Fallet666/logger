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

    const std::string levels[] = {"DEBUG", "INFO", "WARN", "ERROR"};
    const std::string color_levels[] = {
        WHITE + "DEBUG" + RESET, GREEN + "INFO" + RESET, YELLOW + "WARN" + RESET, RED + "ERROR" + RESET
    };


#ifdef GLOBAL_LOG_LEVEL
    const LogLevel globalLogLevel = GLOBAL_LOG_LEVEL;
#else
    const LogLevel globalLogLevel = DEBUG;
#endif

    std::string toString(LogLevel level, bool use_colors);

    class Logger {
    public:
        explicit Logger(std::string name, std::ostream &out = std::cout, LogLevel level = DEBUG);
        void logMessage(LogLevel level, const std::string &message);
        void resetName(const std::string &name);
        void resetName(const std::string &&name);
        void setOutStream(std::ostream &out);
        void setFormatString(const std::string &format_string);

    private:
        std::string formatLog(LogLevel level, const std::string &message);

    private:
        bool use_colors = true;
        std::mutex log_mutex;
        std::string name;
        std::ostream *out;
        std::string format_string = "%L: %T [%N]: %M\n"; // Default format

    };
}

#endif //LOGGER_H