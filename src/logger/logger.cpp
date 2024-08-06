#include "logger/logger.h"

namespace Logger {
    Logger::Logger(std::string name, std::ostream &out, LogLevel level) : name{std::move(name)},
                                                                          out{&out},
                                                                          log_level{level} {
        use_colors = &out == &std::cout;
    }

    std::string toString(LogLevel level, bool use_colors) {
        if (!use_colors) {
            switch (level) {
                case DEBUG: return "DEBUG";
                case INFO: return "INFO";
                case WARN: return "WARN";
                case ERROR: return "ERROR";
                default: return "UNKNOWN";
            }
        }
        switch (level) {
            case DEBUG: return WHITE + "DEBUG";
            case INFO: return GREEN + "INFO";
            case WARN: return YELLOW + "WARN";
            case ERROR: return RED + "ERROR";
            default: return "UNKNOWN";
        }
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
        if (level < log_level) return;

        std::lock_guard lock(this->log_mutex);
        *this->out << this->formatLog(level, message);
        if (use_colors)
            *this->out << RESET;
    }

    void Logger::setLogLevel(LogLevel log_level) {
        std::lock_guard lock(this->log_mutex);
        this->log_level = log_level;
    }

    void Logger::setName(const std::string &name) {
        std::lock_guard lock(this->log_mutex);
        this->name = name;
    }

    void Logger::setOut(std::ostream &out) {
        std::lock_guard lock(this->log_mutex);
        this->out = &out;
        use_colors = &out == &std::cout;
    }
}
