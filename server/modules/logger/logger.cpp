#include "logger.h"

#include <iostream>

namespace Modules {
  std::mutex Logger::log_mutex;

  void Logger::log(LogLevel level, const std::string& message) {
      std::lock_guard<std::mutex> lock(log_mutex);

      std::string timestamp = getTimestamp();
      std::string log_entry = "[" + timestamp + "] [" + logLevelToString(level) + "] " + message;

      if (level == LogLevel::ERROR) {
          std::cerr << log_entry << std::endl;  // Print errors to stderr
      } else {
          std::cout << log_entry << std::endl;  // Print info/warnings to stdout
      }
  }

  std::string Logger::getTimestamp() {
      std::time_t now = std::time(nullptr);
      char buf[20];
      std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
      return std::string(buf);
  }

  std::string Logger::logLevelToString(LogLevel level) {
      switch (level) {
          case LogLevel::INFO: return "INFO";
          case LogLevel::WARNING: return "WARNING";
          case LogLevel::ERROR: return "ERROR";
          default: return "UNKNOWN";
      }
  }
} // namespace Modules

