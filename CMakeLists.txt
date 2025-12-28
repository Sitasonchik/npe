cmake_minimum_required(VERSION 3.10.0)
project(crypto VERSION 0.1.0 LANGUAGES C CXX)



find_package(OpenSSL REQUIRED)

add_executable(crypto src/main.cpp)
set(CMAKE_CXX_STANDARD 17)
target_link_libraries(crypto OpenSSL::SSL OpenSSL::Crypto)

