#include <iostream>
#include <fstream>
#include "logger/logger.h"

int main() {
    Logger::Logger log("abobis");
    log.logMessage(Logger::DEBUG, "I'm not here");
    log.logMessage(Logger::INFO, "I'm here");
}
