#include <iostream>
#include <fstream>
#include "logger/logger.h"

int main() {
    Logger::Logger log("abobis");
    log.logMessage(Logger::DEBUG, "I'm DEBUG");
    log.logMessage(Logger::INFO, "I'm INFO");
    log.logMessage(Logger::WARN, "I'm WARNING");
    log.logMessage(Logger::ERROR, "I'm ERROR");
}
