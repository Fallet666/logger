#include "logger/logger.h"

namespace Logger {
    Logger::Logger(std::string name, std::ostream &out, LogLevel level)
    : name{std::move(name)}
    , out{&out} {
        use_colors = &out == &std::cout;
    }

    std::string toString(LogLevel level, bool use_colors) {
        return use_colors ? color_levels[level] : levels[level];
    }


    std::string Logger::formatLog(LogLevel level, const std::string &message) {
        std::string level_str = toString(level, use_colors),
                current_time = fmt::format(
                    "{:%H:%M:%S}",
                    fmt::localtime(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())));

        /*уровень: Системное время [имя логгера]: message*/
        std::string formatted_message = fmt::format("{}: {} [{}]: {}\n", level_str, current_time, this->name, message);
        return formatted_message;
    }

    void Logger::logMessage(LogLevel level, const std::string &message) {
        if (level < globalLogLevel) return;

        std::lock_guard lock(this->log_mutex);
        *this->out << this->formatLog(level, message);
        if (use_colors)
            *this->out << RESET;
        //чтобы потом в cout оставался стоковый цвет
    }

    void Logger::resetName(const std::string &name) {
        std::lock_guard lock(this->log_mutex);
        this->name = name;
    }

    void Logger::resetName(std::string &&name) {
        std::lock_guard lock(this->log_mutex);
        this->name = std::move(name);
    }

    void Logger::setOutStream(std::ostream &out) {
        std::lock_guard lock(this->log_mutex);
        this->out = &out;
        use_colors = &out == &std::cout;
    }
}
