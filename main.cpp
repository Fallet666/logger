#include <iostream>
#include <fstream>
#include "logger/logger.h"

int main() {
    Logger::Logger log("abobis");
    log.setLogLevel(Logger::INFO);
    log.logMessage(Logger::DEBUG, "I'm not here");
    log.logMessage(Logger::INFO, "I'm here");
}
