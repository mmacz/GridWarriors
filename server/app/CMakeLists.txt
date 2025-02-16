add_executable(gridwarriors
  gridwarriors.cpp include/gridwarriors.h
)
target_include_directories(gridwarriors PRIVATE include)
target_link_libraries(gridwarriors
  PRIVATE
    modules::connection_manager
    modules::logger
)

