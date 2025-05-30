cmake_minimum_required(VERSION 3.10)
project(FHEAsync)

set(CMAKE_CXX_STANDARD 17)
find_package(SEAL 4.1.2 REQUIRED)

add_executable(client client.cpp)
target_link_libraries(client SEAL::seal)

add_executable(server server.cpp)
target_link_libraries(server SEAL::seal)

