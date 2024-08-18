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

    std::string Logger::formatLog(LogLevel level, const std::string &message, const char* file, int line_number) {
        std::string result;
        for (size_t i = 0; i < this->format_string.size(); ++i) {
            if (this->format_string[i] == '%' && i + 1 < this->format_string.size()) {
                switch (this->format_string[++i]) {
                    case 'L': result += toString(level, use_colors); break;
                    case 'T': result += fmt::format("{:%H:%M:%S}", fmt::localtime(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()))); break;
                    case 'N': result += this->name; break;
                    case 'M': result += message; break;
                    case 't': result += std::to_string(std::hash<std::thread::id>{}(std::this_thread::get_id())); break;
                    case 'S': result += file; break;
                    case '#': result += std::to_string(line_number); break;
                    default: result += '%'; result += this->format_string[i]; break;
                }
            } else {
                result += this->format_string[i];
            }
        }
        return result;
    }

    void Logger::logMessage(LogLevel level, const std::string &message, const char* file, int line_number) {
        if (level < globalLogLevel) return;

        std::lock_guard lock(this->log_mutex);
        *this->out << this->formatLog(level, message, file, line_number);
        if (use_colors)
            //because of stock color in cout
            *this->out << RESET;
    }


    void Logger::resetName(const std::string &name) {
        std::lock_guard lock(this->log_mutex);
        this->name = name;
    }

    void Logger::resetName(const std::string &&name) {
        std::lock_guard lock(this->log_mutex);
        this->name = name;
    }

    void Logger::setOutStream(std::ostream &out) {
        std::lock_guard lock(this->log_mutex);
        this->out = &out;
        use_colors = &out == &std::cout;
    }

    void Logger::setFormatString(const std::string &format_string) {
        std::lock_guard lock(this->log_mutex);
        this->format_string = format_string;
    }

}