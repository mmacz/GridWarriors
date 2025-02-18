#pragma once

#include <string>
#include <unordered_map>
#include "Poco/Buffer.h"

namespace Modules
{
  using Message = std::unordered_map<std::string, std::string>;

  class MessageHandler
  {
    public:
      MessageHandler() = delete;
      ~MessageHandler() = delete;
      static Message get_message(const Poco::Buffer<char>& data);
      static std::size_t set_message(const Message& msg, Poco::Buffer<char>& buffer);
    private:
  };
} // namespace Modules

