#include "message_handler.h"

namespace Modules {
  Message MessageHandler::get_message(const Poco::Buffer<char>& data)
  {
    Message msg;
    return msg;
  }

  std::size_t MessageHandler::set_message(const Message& msg, Poco::Buffer<char>& buffer)
  {
    return 0;
  }
}

