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

  class Logger {
  public:
      static void log(LogLevel level, const std::string& message);

  private:
      static std::mutex log_mutex;
      static std::string getTimestamp();
      static std::string logLevelToString(LogLevel level);
  };
} // namespace Modules

