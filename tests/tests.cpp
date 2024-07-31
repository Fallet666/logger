#include "logger/logger.h"
#include <gtest/gtest.h>
#include <sstream>
#include <fstream>
#include <filesystem>


class LoggerTest : public ::testing::Test {
protected:
    std::ostringstream oss;
    Logger::Logger logger{"TestLogger", oss};

    void SetUp() override {
        oss.str("");
        oss.clear();
    }
};

TEST_F(LoggerTest, DebugMessage) {
    logger.logMessage(Logger::DEBUG, "Debug message");
    EXPECT_EQ(oss.str(), "DEBUG: " + fmt::format("{:%H:%M:%S}", fmt::localtime(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()))) + " [TestLogger]: Debug message\n");
}

TEST_F(LoggerTest, InfoMessage) {
    logger.logMessage(Logger::INFO, "Info message");
    EXPECT_EQ(oss.str(), "INFO: " + fmt::format("{:%H:%M:%S}", fmt::localtime(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()))) + " [TestLogger]: Info message\n");
}

TEST_F(LoggerTest, WarningMessage) {
    logger.logMessage(Logger::WARN, "Warning message");
    EXPECT_EQ(oss.str(), "WARN: " + fmt::format("{:%H:%M:%S}", fmt::localtime(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()))) + " [TestLogger]: Warning message\n");
}

TEST_F(LoggerTest, ErrorMessage) {
    logger.logMessage(Logger::ERROR, "Error message");
    EXPECT_EQ(oss.str(), "ERROR: " + fmt::format("{:%H:%M:%S}", fmt::localtime(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()))) + " [TestLogger]: Error message\n");
}

TEST_F(LoggerTest, MultiThreadedLogging) {
    auto log_function = [this](Logger::LogLevel level, const std::string& message) {
        logger.logMessage(level, message);
    };

    std::thread t1(log_function, Logger::DEBUG, "Debug message from thread 1");
    std::thread t2(log_function, Logger::INFO, "Info message from thread 2");
    std::thread t3(log_function, Logger::WARN, "Warning message from thread 3");
    std::thread t4(log_function, Logger::ERROR, "Error message from thread 4");

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    // Проверка того, что все сообщения были залогированы
    EXPECT_NE(oss.str().find("DEBUG: "), std::string::npos);
    EXPECT_NE(oss.str().find("INFO: "), std::string::npos);
    EXPECT_NE(oss.str().find("WARN: "), std::string::npos);
    EXPECT_NE(oss.str().find("ERROR: "), std::string::npos);
}

TEST_F(LoggerTest, FileLogging) {
    std::string log_filename = "test_log.txt";
    {
        std::ofstream file(log_filename);
        Logger::Logger file_logger("FileLogger", file);
        file_logger.logMessage(Logger::DEBUG, "Debug message");
        file_logger.logMessage(Logger::INFO, "Info message");
        file_logger.logMessage(Logger::WARN, "Warning message");
        file_logger.logMessage(Logger::ERROR, "Error message");
    }

    std::ifstream file(log_filename);
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    ASSERT_EQ(lines.size(), 4);
    EXPECT_NE(lines[0].find("DEBUG: "), std::string::npos);
    EXPECT_NE(lines[1].find("INFO: "), std::string::npos);
    EXPECT_NE(lines[2].find("WARN: "), std::string::npos);
    EXPECT_NE(lines[3].find("ERROR: "), std::string::npos);

    std::filesystem::remove(log_filename);
}