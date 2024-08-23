### [Документация на русском](ru/README.md)
# Logger Library

This project is a simple and flexible logging library in C++. The library supports different logging levels, message formatting and the ability to write logs to different streams.

## Table of contents
- [Main features](#main-features)
- [Installation](#installation)
- [Basic Concepts](#basic-concepts)
- [Logging Functions](#logging-functions)
    - [Basic Functions](#basic-functions)
    - [Simplified Functions for Each Level](#simplified-functions-for-each-level)
    - [Global Logging Functions](#global-logging-functions)
    - [Logging Level](#logging-level)
- [Log Formatting](#log-formatting)
    - [Default Formatting](#default-formatting)
    - [Advanced Formatting](#advanced-formatting)
    - [Using Colors in Logs](#using-colors-in-logs)
- [Logging in Multithreaded Applications](#logging-in-multithreaded-applications)
    - [An example of Multithreaded Logging](#an-example-of-multithreaded-logging)
    - [Features of Multi-threaded Logging](#features-of-multi-threaded-logging)
- [Logging to Different Output Streams](#logging-to-different-output-streams)
    - [Setting the Output Stream](#setting-the-output-stream)
    - [Changing the Output Stream](#changing-the-output-stream)
    - [Example of Using Different Streams](#example-of-using-different-streams)

## Main features

- Support for different logging levels: `DEBUG`, `INFO`, `WARN`, `ERROR`.
- Customizable log formatting.
- Ability to log to multiple streams with data race protection.
- Logging to different output streams (`std::cout`, files, etc.).
- Ability to use a global logger.

## Installation

1. Clone the repository:
```bash
git clone <https://github.com/Fallet666/logger.git>
```
2. Go to the project directory and build it using CMake:
```bash
cd logger
mkdir build
cd build
cmake ..
make
```

## Basic concepts

- **Logger**: The main class for logging. Create an instance of this class to log to a specific stream.
- **Global logger**: A singleton instance of `Logger` that can be used by default throughout the project.

## Logging functions

The project provides several functions for writing logs with different levels of importance. These functions allow you to flexibly control the output of messages depending on their severity. Logs are divided into four levels:

- `DEBUG` — For debugging information.
- `INFO` — For general informational messages.
- `WARN` — For warnings.
- `ERROR` — For errors that require attention.

### Basic functions

#### `LOG_MESSAGE(Logger& logger, LogLevel level, const std::string& message)`

Logs a message with the specified level. This function is universal and can be used to log messages of any level.

#### Example of use:

```c++
Logger::Logger log("Logger");
LOG_MESSAGE(log, Logger::DEBUG, "I'm MESSAGE");
```

### Simplified functions for each level
These functions are intended to simplify the call to logging at a specific level:
#### 1. `logDebug(Logger& logger, const std::string& message)`
Logs a message with the `DEBUG` level.

#### Usage example:
```c++
logDebug(log, "This is a debug message");
```

#### 2. `logInfo(Logger& logger, const std::string& message)`
Logs a message with level `INFO`.

#### Usage example:
```c++
logInfo(log, "This is an info message");
```
#### 3. `logWarn(Logger& logger, const std::string& message)`
Logs a message with level `WARN`.

#### Usage example:
```c++
logWarn(log, "This is a warning message");
```
#### 4. `logError(Logger& logger, const std::string& message)`
Logs a message with level `ERROR`.

#### Usage example:
```c++
logError(log, "This is an error message");
```

### Global logging functions
The project also provides global logging functions that use the global logger. These functions allow you to log messages without having to create and manage your own logger instances.

Similar to the basic functions, there are the following global logging functions:

- `logMessageGlobal(LogLevel level, const std::string& message)`
- `logDebugGlobal(const std::string& message)`
- `logInfoGlobal(const std::string& message)`
- `logWarnGlobal(const std::string& message)`
- `logErrorGlobal(const std::string& message)`

### Logging level
You can set the logging level via `Cmake`, then logs of levels not lower than the specified level will be displayed. For example, if you set the level `Warn`, then logs of levels `Warn` and `Error` will be displayed. #### Usage in Cmake:
```cmake
set(DEFAULT_LOG_LEVEL DEBUG)
add_compile_definitions(GLOBAL_LOG_LEVEL=${DEFAULT_LOG_LEVEL})
```

### Note
Each of the logging functions automatically adds information about the file and line from which the log was called, using the __FILE__ and __LINE__ macros. This makes it easier to track the source of logs in your code.

## Log formatting

### Default formatting:

Format string: "%L: %T [%N]: %M\n"

Example output:

DEBUG: 12:34:56 [MyLogger]: This is a debug message

### Advanced formatting
Logs can be customized using a format string. By default, the format string can contain the following components:
- **%L** — Log level (DEBUG, INFO, WARN, ERROR).
- **%T** — Log recording time in HH:MM:SS format.
- **%N** — Logger name.
- **%M** — Log message.
- **%t** — Thread identifier that wrote the log.
- **%S** — File name from which the log was called.
- **%#** — Line number in the file from which the log was called.

These specifiers can be combined and placed in any order to customize the log format to the needs of the project.

The format string is specified as follows:

```c++
Logger::Logger log("custom formatting");
log.setFormatString("%L: %T [%N]: %M (%S: %#)\n");
```
### Using colors in logs
The project provides the ability to colorize log output to the console to easily distinguish messages of different levels. Colors are automatically applied if the logger output stream is set to `std::cout`.

#### Color scheme:
- `DEBUG` — <span style="color:white">White</span> (\033[37m).
- `INFO` — <span style="color:green">Green</span> (\033[32m).
- `WARN` — <span style="color:yellow">Yellow</span> (\033[33m).
- `ERROR` — <span style="color:red">Red</span> (\033[31m).

Colors can be seen in the terminal when logging, which makes it much easier to identify the importance of messages.

#### Disabling color
Colors are automatically disabled if you use a different output stream (for example, writing logs to a file).

## Logging in multithreaded applications
The project provides support for multithreaded logging. This means that several threads can simultaneously write logs without the risk of data corruption or race conditions.

Thread synchronization
To ensure thread safety, the Logger class uses a mutex (`std::mutex`). Each time the logging function is called or the logger fields are changed, the thread is blocked until the operation is completed. This prevents simultaneous access to shared resources (for example, the output stream or logger settings), which guarantees the correctness and integrity of the data in the logs.
### An example of multithreaded logging
```c++
Logger::Logger log("MultiThreadLogger");

std::vector<std::thread> threads;
for (int i = 0; i < 10; ++i) {
threads.emplace_back([&log, i] {
logInfo(log, "Message from thread " + std::to_string(i));
});
}

for (auto &t : threads) {
t.join();
}
```

This example creates 10 threads, each of which writes a log message with information about its number. Due to the use of a mutex, all messages will be written correctly and without mixing.

### Features of multi-threaded logging
- **Thread safety:** Using a mutex inside the logger ensures that only one operation will be performed at a time - either writing a message or changing the logger fields (for example, changing the output stream or log format).
- **Performance:** Despite the lock, the logger is designed to minimize the impact on performance. However, with a large number of logs or high system load, delays are possible.
- **Output to different streams:** The logger allows you to use different output streams for different instances, which can be useful for separating logs by category or source.

## Logging to different output streams

The project provides a flexible way to configure the output stream for the logger. This means that you can direct logs to any stream that supports the `std::ostream` interface, be it standard output (`std::cout`), files, string streams (`std::ostringstream`) or even custom streams.

### Setting the output stream
When creating a logger instance, you can specify where the logs will be written. By default, logs are directed to `std::cout`, but this behavior can be changed:
```c++
Logger::Logger log("FileLogger", std::ofstream("log.txt"));
```
In this example, logs will be written to the log.txt file.

### Changing the output stream
You can also change the logger output stream while the program is running using the `setOutStream` method:
```c++
Logger::Logger log("Logger");
log.setOutStream(std::cerr);
```

### Example of using different streams

```c++
std::ofstream file("output.log");
std::ostringstream oss;

Logger::Logger logToFile("FileLogger", file);
Logger::Logger logToStringStream("StringStreamLogger", oss);
Logger::Logger logToConsole("ConsoleLogger");

logInfo(logToFile, "This log goes to a file");
logWarn(logToStringStream, "This log goes to a string stream");
logError(logToConsole, "This log goes to the console");

file.close();
```

---
*If you have any suggestions for improvement or found any bugs, feel free to create an `issue` in the project repository. I always welcome help from the community and would appreciate your contribution to the project.*