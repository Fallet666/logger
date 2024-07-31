#include <iostream>
#include "logger.h"

int main() {
    Logger log("abobis");
    log.logMessage(INFO, "Hello word!");
}
