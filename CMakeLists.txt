cmake_minimum_required(VERSION 3.12)

project(SpaceDissident)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find_package(fmt CONFIG REQUIRED)
# find_package(spdlog CONFIG REQUIRED)

# Add allegro and allegro_ttf library paths
if(EXISTS "/etc/wsl")
    set(ALLEGRO_LIBRARY_PATH "/usr/lib/x86_64-linux-gnu")
    set(ALLEGRO_TTF_LIBRARY_PATH "/usr/lib/x86_64-linux-gnu/")
else()
    set(ALLEGRO_LIBRARY_PATH "/usr/lib/")
    set(ALLEGRO_TTF_LIBRARY_PATH "/usr/lib/")
endif()

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    # Disable deprecated warnings for GCC
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    # Disable deprecated warnings for Clang
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
endif()


set(ALLEGRO_INCLUDE_DIR "/usr/include/allegro5")
set(ALLEGRO_TTF_INCLUDE_DIR "/usr/include/allegro5")

set(FMT_INCLUDE_DIR "/usr/include/fmt")
set(SPDLOG_INCLUDE_DIR "/usr/include/spdlog")
set(SPDLOG_LIB_PATH "/usr/lib/cmake/spdlog")

set(CORE_INCLUDES
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/common
    ${CMAKE_SOURCE_DIR}/include/core
    ${CMAKE_SOURCE_DIR}/include/core/initializers
    ${CMAKE_SOURCE_DIR}/include/game
    ${CMAKE_SOURCE_DIR}/include/input
    ${CMAKE_SOURCE_DIR}/include/logs
    ${CMAKE_SOURCE_DIR}/include/math
    ${CMAKE_SOURCE_DIR}/include/render
    ${CMAKE_SOURCE_DIR}/include/render/operations
    ${CMAKE_SOURCE_DIR}/include/sound
    ${CMAKE_SOURCE_DIR}/include/system
    ${CMAKE_SOURCE_DIR}/include/ui
    ${CMAKE_SOURCE_DIR}/include/util
)

set(CORE_ENGINE_SRC_FILES
    ${CMAKE_SOURCE_DIR}/src/render/CoreRenderer.cpp
    ${CMAKE_SOURCE_DIR}/src/render/DebugRenderer.cpp
)

# Link to allegro and allegro_ttf libraries
link_directories("${ALLEGRO_LIBRARY_PATH}" "${ALLEGRO_TTF_LIBRARY_PATH}")

# Add your source files here
add_executable(SpaceDissident
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CORE_ENGINE_SRC_FILES}
)

#TODO! PLEASE FIX TO THE NEW MAIN
# # Add your source files here
# add_executable(SpaceDissident
#     ${CMAKE_SOURCE_DIR}/src/newMain.cpp
#     ${CORE_ENGINE_SRC_FILES}
# )


# Include allegro and allegro_ttf libraries
target_link_libraries(SpaceDissident
    ${ALLEGRO_LIBRARY_PATH}/liballegro.so
    ${ALLEGRO_LIBRARY_PATH}/liballegro_primitives.so
    ${ALLEGRO_LIBRARY_PATH}/liballegro_font.so
    ${ALLEGRO_TTF_LIBRARY_PATH}/liballegro_ttf.so
    ${ALLEGRO_TTF_LIBRARY_PATH}/liballegro_image.so
    ${CMAKE_SOURCE_DIR}/lib/bin/libbox2d.a
    fmt
)

# Include directories
target_include_directories(SpaceDissident PRIVATE
    ${CORE_INCLUDES}
    ${ALLEGRO_INCLUDE_DIR}
    ${ALLEGRO_TTF_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/3pp/Box2D/include/  # Include Box2D headers
    ${SPDLOG_INCLUDE_DIR}
    ${FMT_INCLUDE_DIR}
)

# # Add Box2D as a submodule
# add_subdirectory(${CMAKE_SOURCE_DIR}/3pp/Box2D)

# # Link against the Box2D library
# target_link_libraries(SpaceDissident Box2D)

# Set the output directory for the binary
set_target_properties(SpaceDissident PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build
)

# Include the "ut" (unit test) directory
add_subdirectory(ut)

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