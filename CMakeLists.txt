cmake_minimum_required(VERSION 3.12)

project(SpaceDissident)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(WIN32 FALSE)

# Find vcpkg installed packages
if(WIN32)
    set(VCPKG_INSTALLED_DIR "C:/buildtools/vcpkg/packages/")
    set(CMAKE_TOOLCHAIN_FILE "C:/buildtools/vcpkg/scripts/buildsystems/vcpkg.cmake")
endif()

# Check if ccache is available
find_program(CCACHE_FOUND ccache)

# If ccache is found, use it as a wrapper for the compiler
if(CCACHE_FOUND)
    set(CMAKE_CXX_COMPILER_LAUNCHER "ccache")
    message(STATUS "ccache found, using it for the compiler")
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
    if(WIN32)
        set(INCLUDE_PATH "C:/buildtools/vcpkg/packages/${PARAMETER}_x64-windows/include/")
    endif()
    # message(STATUS "Constructed include path: ${INCLUDE_PATH}")
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
    ${allegro5_INCLUDE_PATH}
    ${fmt_INCLUDE_PATH}
    ${spdlog_INCLUDE_PATH}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/common
    ${CMAKE_SOURCE_DIR}/include/core
    ${CMAKE_SOURCE_DIR}/include/core/initializers
    ${CMAKE_SOURCE_DIR}/include/game
    ${CMAKE_SOURCE_DIR}/include/game/common
    ${CMAKE_SOURCE_DIR}/include/game/demo
    ${CMAKE_SOURCE_DIR}/include/game/simulation
    ${CMAKE_SOURCE_DIR}/include/input
    ${CMAKE_SOURCE_DIR}/include/math
    ${CMAKE_SOURCE_DIR}/include/render
    ${CMAKE_SOURCE_DIR}/include/render/operations
    ${CMAKE_SOURCE_DIR}/include/render/operations/debug
    ${CMAKE_SOURCE_DIR}/include/system
    ${CMAKE_SOURCE_DIR}/include/ui
    ${EXTERNAL_INCLUDES}
    # Add other necessary include directories here
)

# Add your source files here
set(CORE_ENGINE_SRC_FILES
    ${CMAKE_SOURCE_DIR}/src/common/INamedObject.cpp
    ${CMAKE_SOURCE_DIR}/src/common/IRenderable.cpp
    ${CMAKE_SOURCE_DIR}/src/core/initializers/AllegroManager.cpp
    ${CMAKE_SOURCE_DIR}/src/core/initializers/CoreManager.cpp
    ${CMAKE_SOURCE_DIR}/src/core/Core.cpp
    ${CMAKE_SOURCE_DIR}/src/core/RendererLayer.cpp
    ${CMAKE_SOURCE_DIR}/src/game/demo/DevScene.cpp
    ${CMAKE_SOURCE_DIR}/src/game/GObject.cpp
    ${CMAKE_SOURCE_DIR}/src/game/NamedLayer.cpp
    ${CMAKE_SOURCE_DIR}/src/game/TestShip.cpp
    ${CMAKE_SOURCE_DIR}/src/render/CoreRenderer.cpp
    ${CMAKE_SOURCE_DIR}/src/render/DebugRenderer.cpp
    ${CMAKE_SOURCE_DIR}/src/render/UiRenderer.cpp
    ${CMAKE_SOURCE_DIR}/src/ui/Button.cpp
    ${CMAKE_SOURCE_DIR}/src/ui/Panel.cpp
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

# Include the "ut" directory only if the build mode is Debug
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_subdirectory(ut)
endif()

# Create a custom target to ensure the copy command is executed
add_custom_target(copy_resources ALL DEPENDS SpaceDissident)
