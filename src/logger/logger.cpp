#include "logger.h"


std::string Logger::formatLog(LogLevel::LogLevel level, const std::string &message) {
    std::string level_str = LogLevel::toString(level), current_time = fmt::format(
        "{:%H:%M:%S}",
        fmt::localtime(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())));

    /*уровень: Системное время [имя логгера]: message*/
    std::string formatted_message = fmt::format("{}: {} [{}]: {}", level_str, current_time, this->name, message);
    return formatted_message;
}

void Logger::logMessage(LogLevel::LogLevel level, const std::string &message) {
    std::lock_guard<std::mutex> lock(this->log_mutex);
    this->out << this->formatLog(level, message);
}

Logger::Logger(std::string name, std::ostream &out) : name(move(name)), out(out) {
}
