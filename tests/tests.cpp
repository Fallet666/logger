#include "logger/logger.h"
#include <gtest/gtest.h>
#include <sstream>
#include <fstream>
#include <regex>
#include <unordered_set>

class LoggerTest : public ::testing::Test {
protected:
    std::ostringstream oss;
    Logger::Logger logger{"TestLogger", oss};

    static std::string buildExpectedLogString(Logger::LogLevel level, const std::string &loggerName,
                                              const std::string &message) {
        std::string level_str = Logger::toString(level, false);
        return level_str + ": \\d{2}:\\d{2}:\\d{2} \\[" + loggerName + "\\]: " + message + "\n?";
    }

    void checkLog(const std::string &expectedLog) {
        std::regex logRegex(expectedLog);
        bool match = std::regex_match(oss.str(), logRegex);
        if (!match) {
            std::cout << "Log does not match. Log: \"" << oss.str() << "\" Expected: \"" << expectedLog << "\"" <<
                    std::endl;
        }
        EXPECT_TRUE(match);
    }
};

TEST_F(LoggerTest, DebugMessage) {
    logger.logMessage(Logger::DEBUG, "Debug message");
    checkLog(buildExpectedLogString(Logger::DEBUG, "TestLogger", "Debug message"));
}

TEST_F(LoggerTest, InfoMessage) {
    logger.logMessage(Logger::INFO, "Info message");
    checkLog(buildExpectedLogString(Logger::INFO, "TestLogger", "Info message"));
}

TEST_F(LoggerTest, WarningMessage) {
    logger.logMessage(Logger::WARN, "Warning message");
    checkLog(buildExpectedLogString(Logger::WARN, "TestLogger", "Warning message"));
}

TEST_F(LoggerTest, ErrorMessage) {
    logger.logMessage(Logger::ERROR, "Error message");
    checkLog(buildExpectedLogString(Logger::ERROR, "TestLogger", "Error message"));
}

TEST_F(LoggerTest, MultiThreadedLogging) {
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([this, i] {
            logger.logMessage(Logger::INFO, "Message " + std::to_string(i));
        });
    }
    for (auto &t: threads) {
        t.join();
    }

    std::istringstream logStream(oss.str());
    std::string logEntry;
    int messageCount = 0;

    while (std::getline(logStream, logEntry)) {
        std::regex logRegex("INFO: \\d{2}:\\d{2}:\\d{2} \\[TestLogger\\]: Message \\d");
        bool match = std::regex_match(logEntry, logRegex);
        EXPECT_TRUE(match);
        if (match) {
            messageCount++;
        }
    }

    EXPECT_EQ(messageCount, 10);
}

TEST_F(LoggerTest, LogToFile) {
    std::ofstream file("test_log.txt");
    Logger::Logger fileLogger("FileLogger", file);

    fileLogger.logMessage(Logger::DEBUG, "File log message");

    file.close();

    std::ifstream fileRead("test_log.txt");
    std::stringstream buffer;
    buffer << fileRead.rdbuf();
    fileRead.close();

    std::regex logRegex(buildExpectedLogString(Logger::DEBUG, "FileLogger", "File log message"));
    bool match = std::regex_match(buffer.str(), logRegex);
    if (!match) {
        std::cout << "Log does not match. Log: \"" << buffer.str() << "\" Expected: \"" << buildExpectedLogString(
            Logger::DEBUG, "FileLogger", "File log message") << "\"" << std::endl;
    }
    EXPECT_TRUE(match);

    std::remove("test_log.txt");
}