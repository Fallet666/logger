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


enum LogLevel { DEBUG, INFO, WARN, ERROR };
class logger {
    std::mutex logMutex;
    const std::string name;
    std::ostream &out;
    std::string formatLog(LogLevel level, const std::string &message);
public:
    logger(std::string  name, std::ostream &out = std::cout) : out(out), name(std::move(name)){};
    static std::string getCurrentTime();
    void logMessage(LogLevel level, const std::string &message);
};



#endif //LOGGER_H
