#include <memory>

#include <Poco/Net/HTTPServerParams.h>
#include <Poco/Types.h>
#include <stdexcept>
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/NetException.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/WebSocket.h"

#include "connection_manager.h"
#include "message_handler.h"
#include "logger.h"

namespace Modules
{
  class WebSocketRequestHandler
  : public Poco::Net::HTTPRequestHandler
  {
  public:
    WebSocketRequestHandler(std::size_t size = DEFAULT_BUFFER_SIZE) : _bufSize(size) {};

    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)
    {
      try {
        Poco::Net::WebSocket ws(request, response);
        Poco::Buffer<char> buffer(_bufSize);
        int flags;
        int n;
        do {
            n = ws.receiveFrame(buffer.begin(), static_cast<int>(buffer.size()), flags);
        } while(n > 0 || (flags & Poco::Net::WebSocket::FRAME_OP_BITMASK) != Poco::Net::WebSocket::FRAME_OP_CLOSE);
        // MessageHandler
        Message msg = MessageHandler::get_message(buffer);
        // ws.sendFrame(buffer.begin(), n, flags);
        auto msgSize = MessageHandler::set_message(msg, buffer);
      }
      catch(Poco::Net::WebSocketException& exc) {
        switch(exc.code()) {
          case Poco::Net::WebSocket::WS_ERR_HANDSHAKE_UNSUPPORTED_VERSION:
            response.set("Sec-WebSocket-Version", Poco::Net::WebSocket::WEBSOCKET_VERSION);
            // fallthrough
          case Poco::Net::WebSocket::WS_ERR_NO_HANDSHAKE:
          case Poco::Net::WebSocket::WS_ERR_HANDSHAKE_NO_VERSION:
          case Poco::Net::WebSocket::WS_ERR_HANDSHAKE_NO_KEY:
            response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            response.setContentLength(0);
            response.send();
            break;
        }
      }
    }

  private:
    std::size_t _bufSize;
  };

  class WebSocketRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory
  {
    public:
      WebSocketRequestHandlerFactory(std::size_t bufSize = 1024)
      : _bufSize(bufSize)
      {
      }

      Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request)
      {
        return new WebSocketRequestHandler(_bufSize);
      }

    private:
      std::size_t _bufSize;
  };

  class CMImpl
  {
    public:
      CMImpl() = delete;
      CMImpl(const Config& cfg);
      ~CMImpl();
      void run();

    private:
      Poco::Net::ServerSocket _ss;
      Poco::Net::HTTPServer _server;
      Modules::Logger*_logger;
  };


  CMImpl::CMImpl(const Config& cfg)
  : _ss{static_cast<Poco::UInt16>(cfg.port)}
  , _server{new WebSocketRequestHandlerFactory(cfg.msgSize), _ss, new Poco::Net::HTTPServerParams}
  , _logger{reinterpret_cast<Modules::Logger*>(cfg._logger)}
  {
  }

  void CMImpl::run()
  {
    INFO_1(_logger, "Starting the server at port: ", _server.port());
    _server.start();
  }

  CMImpl::~CMImpl()
  {
    INFO_0(_logger, "Stopping the server...");
    _server.stop();
  }

  ConnectionManager::ConnectionManager(const Config& cfg)
  : _impl{std::make_unique<CMImpl>(cfg)}
  {
  }

  ConnectionManager::~ConnectionManager()
  {
  }

  void ConnectionManager::run()
  {
    if (!_impl) {
      throw std::runtime_error("Connection manager not started...");
    }
    _impl->run();
  }
} // namespace Modules
