cmake_minimum_required(VERSION 3.20)

# set the project name
project(OrionEngine)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(OrionEngine)

target_include_directories(OrionEngine PUBLIC
    include
    src
)

target_link_libraries(OrionEngine)

add_subdirectory(src)

# Don't pull tests in to whoever uses our library
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    enable_testing()
    add_subdirectory(test)
endif()