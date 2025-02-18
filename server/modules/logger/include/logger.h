#pragma once

#include <mutex>
#include <string>
#include <ctime>

namespace Modules {
  enum class LogLevel {
      INFO,
      WARNING,
      ERROR
  };

#define INFO_0(logger, msg) \
  { \
    if (_logger) { \
      _logger->log(LogLevel::INFO, msg); \
    } \
  }

#define INFO_1(logger, msg, param) \
  { \
    if (_logger) { \
      std::string log_msg = msg + std::to_string(param); \
      _logger->log(LogLevel::INFO, log_msg); \
    } \
  }

#define ERROR(logger, msg) \
  { \
    if (_logger) { \
      std::string log_msg = msg + std::to_string(param); \
      _logger->log(LogLevel::ERROR, log_msg); \
    } \
  }

  class Logger {
  public:
      static void log(LogLevel level, const std::string& message);

  private:
      static std::mutex log_mutex;
      static std::string getTimestamp();
      static std::string logLevelToString(LogLevel level);
  };
} // namespace Modules

