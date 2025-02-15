add_library(logger STATIC
  logger.cpp include/logger.h
)
target_include_directories(logger PUBLIC include)
add_library(modules::logger ALIAS logger)

