cmake_minimum_required(VERSION 3.12)

project(SpaceDissident)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find vcpkg installed packages
if(WIN32)
    set(VCPKG_INSTALLED_DIR "C:/buildtools/vcpkg/packages/")
    set(CMAKE_TOOLCHAIN_FILE "C:/buildtools/vcpkg/scripts/buildsystems/vcpkg.cmake")
endif()

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    # Disable deprecated warnings for GCC
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    # Disable deprecated warnings for Clang
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
elseif(MSVC)
    add_compile_options(/D_CRT_SECURE_NO_WARNINGS)
endif()

find_package(Allegro REQUIRED)
find_package(fmt REQUIRED)
find_package(spdlog REQUIRED)
find_package(GTest REQUIRED)
find_package(box2d REQUIRED)

# Define a function to construct the path
function(CONSTRUCT_INCLUDE_PATH PARAMETER)
    set(INCLUDE_PATH "C:/buildtools/vcpkg/packages/${PARAMETER}_x64-windows/include/")
    message(STATUS "Constructed include path: ${INCLUDE_PATH}")
    # Return the constructed path
    set(${PARAMETER}_INCLUDE_PATH ${INCLUDE_PATH} PARENT_SCOPE)
    # Return the constructed path directly for use in the list
    list(APPEND EXTERNAL_INCLUDES ${INCLUDE_PATH})
endfunction()

# Call the function to populate EXTERNAL_INCLUDES
CONSTRUCT_INCLUDE_PATH("allegro5")
CONSTRUCT_INCLUDE_PATH("fmt")
CONSTRUCT_INCLUDE_PATH("spdlog")

# Set include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/common
    ${CMAKE_SOURCE_DIR}/include/core
    ${CMAKE_SOURCE_DIR}/include/core/initializers
    ${CMAKE_SOURCE_DIR}/include/game
    ${CMAKE_SOURCE_DIR}/include/input
    ${CMAKE_SOURCE_DIR}/include/math
    ${CMAKE_SOURCE_DIR}/include/render
    ${CMAKE_SOURCE_DIR}/include/render/operations
    ${CMAKE_SOURCE_DIR}/include/system
    ${CMAKE_SOURCE_DIR}/include/ui
    ${allegro5_INCLUDE_PATH}
    ${spdlog_INCLUDE_PATH}
    ${fmt_INCLUDE_PATH}
    ${EXTERNAL_INCLUDES}
    # Add other necessary include directories here
)

# Add your source files here
set(CORE_ENGINE_SRC_FILES
    ${CMAKE_SOURCE_DIR}/src/render/CoreRenderer.cpp
    ${CMAKE_SOURCE_DIR}/src/render/DebugRenderer.cpp
    ${CMAKE_SOURCE_DIR}/src/game/GObject.cpp
)

# Create the executable
add_executable(SpaceDissident
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CORE_ENGINE_SRC_FILES}
)

get_target_property(TARGET_INCLUDE_DIRS SpaceDissident INCLUDE_DIRECTORIES)
message(STATUS "Include directories for SpaceDissident: ${TARGET_INCLUDE_DIRS}")


# Link libraries
target_link_libraries(SpaceDissident
    Allegro::allegro
    Allegro::allegro_primitives
    Allegro::allegro_font
    Allegro::allegro_ttf
    Allegro::allegro_image
    box2d::box2d
    fmt::fmt
)

# Set the output directory for the binary
set_target_properties(SpaceDissident PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build
)

# Enable the generation of compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Custom command to copy files after a successful build
add_custom_command(
    TARGET SpaceDissident POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/res
    ${CMAKE_SOURCE_DIR}/build/res
)

# Create a custom target to ensure the copy command is executed
add_custom_target(copy_resources ALL DEPENDS SpaceDissident)
