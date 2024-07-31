#include <iostream>
#include "logger/logger.h"

int main() {
    Logger::Logger log("abobis");
    log.logMessage(Logger::INFO, "Hello word!");
}