#pragma once

#include <iostream>
#include <mutex>
#include <string>
#include <ctime>

enum class LogLevel {
    INFO,
    WARNING,
    ERROR
};

class Logger {
public:
    static void Log(LogLevel level, const std::string& message);

private:
    static std::mutex log_mutex;
    static std::string GetTimestamp();
    static std::string LogLevelToString(LogLevel level);
};

