#include <iostream>
#include "logger.h"

int main() {
    logger log("abobis");
    log.logMessage(INFO, "Hello word!");
}
