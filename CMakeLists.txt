cmake_minimum_required(VERSION 3.12)

project(dataGen)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add your source files here
add_executable(dataGen ${CMAKE_SOURCE_DIR}/src/main.cpp)

# Include directories
target_include_directories(dataGen PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Set the output directory for the binary
set_target_properties(dataGen PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build
)

# Include the "ut" (unit test) directory
add_subdirectory(ut)
