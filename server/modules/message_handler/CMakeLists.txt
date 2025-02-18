add_library(message_handler STATIC
  message_handler.cpp include/message_handler.h
)
target_include_directories(message_handler PUBLIC include)
target_link_libraries(message_handler
  PUBLIC
    Poco::Net
)
add_library(modules::message_handler ALIAS message_handler)

