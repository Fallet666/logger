#include "logger/logger.h"

namespace Logger {
    Logger::Logger(std::string name, std::ostream &out) : name{std::move(name)}, out{out} {
    }

    std::string Logger::formatLog(LogLevel level, const std::string &message) {
        std::string level_str = toString(level),
                current_time = fmt::format(
                    "{:%H:%M:%S}",
                    fmt::localtime(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())));

        /*уровень: Системное время [имя логгера]: message*/
        std::string formatted_message = fmt::format("{}: {} [{}]: {}\n", level_str, current_time, this->name, message);
        return formatted_message;
    }

    void Logger::logMessage(LogLevel level, const std::string &message) {
        std::lock_guard lock(this->log_mutex);
        this->out << this->formatLog(level, message);
    }
}