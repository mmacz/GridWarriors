cmake_minimum_required(VERSION 3.20)
project(gridwarriors_server VERSION 1.0.0 LANGUAGES C CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
enable_testing()

find_package(Poco REQUIRED)
find_package(GTest REQUIRED)

add_subdirectory(modules)
add_subdirectory(app)

