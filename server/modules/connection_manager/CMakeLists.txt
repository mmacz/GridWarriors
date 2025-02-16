add_library(connection_manager STATIC
  connection_manager.cpp include/connection_manager.h
)
target_include_directories(connection_manager PUBLIC include)
target_link_libraries(connection_manager
  PUBLIC
    Poco::Net
  PRIVATE
    modules::logger
)

add_library(modules::connection_manager ALIAS connection_manager)

