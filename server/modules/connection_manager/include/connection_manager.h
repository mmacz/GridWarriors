#pragma once

#include <cstdint>
#include <memory>

namespace Modules
{
  constexpr size_t DEFAULT_BUFFER_SIZE = 1024;

  struct Config
  {
    uint16_t port;
    size_t msgSize;
    void* _logger;
  };

  class CMImpl;

  class ConnectionManager
  {
  public:
    ConnectionManager() = delete;
    ConnectionManager(const Config& cfg);
    ~ConnectionManager();
    void run();

  private:
    std::unique_ptr<CMImpl> _impl {nullptr};
  };
} // namespace Modules

