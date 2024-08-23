#include <iostream>
#include <fstream>
#include "logger/logger.h"

int main() {
    Logger::Logger log("bebris");
    log.setFormatString("%L: %T [%N]: %M (%S: %#)\n");
    logDebug(log, "I'm DEBUG");
    logDebugGlobal("I'm global DEBUG");
}
