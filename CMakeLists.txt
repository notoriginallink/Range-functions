CMAKE_MINIMUM_REQUIRED(VERSION 3.24)
project(labwork-11-notoriginallink VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)

add_subdirectory(lib/Algo)
add_executable(Algorithms main.cpp)

target_link_libraries(Algorithms PRIVATE Algo)

#for tests
enable_testing()
add_subdirectory(tests)