//
// Created by user on 28.07.2024.
//

#include "logger.h"

std::string logger::getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    return fmt::format(
        //"{:%Y-%m-%d %H:%M:%S}",
        "{:%H:%M:%S}",
        fmt::localtime(std::chrono::system_clock::to_time_t(now))
        );
}

std::string logger::formatLog(LogLevel level, const std::string &message) {
    std::string levelStr;
    switch (level) {
        case DEBUG: levelStr = "DEBUG"; break;
        case INFO:  levelStr = "INFO"; break;
        case WARN:  levelStr = "WARN"; break;
        case ERROR: levelStr = "ERROR"; break;
    }
    /*уровень: Системное время [имя логгера]: message*/
    std::string formattedMessage = fmt::format("{}: {} [{}]: {}", levelStr, getCurrentTime(), name, message);
    return formattedMessage;
}

void logger::logMessage(LogLevel level, const std::string &message) {
    out<<formatLog(level, message);
}



