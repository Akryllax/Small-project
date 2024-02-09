cmake_minimum_required(VERSION 3.12)

project(SpaceDissident-tests)

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
CONSTRUCT_INCLUDE_PATH("gtest")
CONSTRUCT_INCLUDE_PATH("gmonk")
CONSTRUCT_INCLUDE_PATH("allegro5")
CONSTRUCT_INCLUDE_PATH("fmt")
CONSTRUCT_INCLUDE_PATH("spdlog")


# Add your source files here
set(CORE_ENGINE_SRC_FILES
    ${CMAKE_SOURCE_DIR}/src/core/initializers/AllegroManager.cpp
    ${CMAKE_SOURCE_DIR}/src/core/initializers/CoreManager.cpp
    ${CMAKE_SOURCE_DIR}/src/game/GObject.cpp
    ${CMAKE_SOURCE_DIR}/src/game/TestShip.cpp
    ${CMAKE_SOURCE_DIR}/src/render/CoreRenderer.cpp
    ${CMAKE_SOURCE_DIR}/src/render/DebugRenderer.cpp
    ${CMAKE_SOURCE_DIR}/src/ui/Button.cpp
)

# Set include directories
include_directories(
    ${allegro5_INCLUDE_PATH}
    ${fmt_INCLUDE_PATH}
    ${spdlog_INCLUDE_PATH}
    ${gtest_INCLUDE_PATH}
    ${gmock_INCLUDE_PATH}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/common
    ${CMAKE_SOURCE_DIR}/include/core
    ${CMAKE_SOURCE_DIR}/include/core/initializers
    ${CMAKE_SOURCE_DIR}/include/game
    ${CMAKE_SOURCE_DIR}/include/game/common
    ${CMAKE_SOURCE_DIR}/include/input
    ${CMAKE_SOURCE_DIR}/include/math
    ${CMAKE_SOURCE_DIR}/include/render
    ${CMAKE_SOURCE_DIR}/include/render/operations
    ${CMAKE_SOURCE_DIR}/include/system
    ${CMAKE_SOURCE_DIR}/include/ui
    ${EXTERNAL_INCLUDES}
    # Add other necessary include directories here
)


##############################################################
##                           CORE UT                        ##
# Add your test source files here
add_executable(${PROJECT_NAME}_core
    ${CMAKE_SOURCE_DIR}/ut/test_main.cpp
    ${CORE_ENGINE_SRC_FILES}
)

# Include allegro and allegro_ttf libraries
target_link_libraries(${PROJECT_NAME}_core
    GTest::GTest
    GTest::Main
    Allegro::allegro
    Allegro::allegro_primitives
    Allegro::allegro_font
    Allegro::allegro_ttf
    Allegro::allegro_image
    box2d::box2d
    fmt::fmt
)

# Include directories
target_include_directories(${PROJECT_NAME}_core PRIVATE
    ${CORE_INCLUDES}
    ${ALLEGRO_INCLUDE_DIR}
    ${ALLEGRO_TTF_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/3pp/Box2D/include/  # Include Box2D headers
    ${SPDLOG_INCLUDE_DIR}
    ${FMT_INCLUDE_DIR}
)

add_custom_command(
    TARGET ${PROJECT_NAME}_core POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/res
    ${CMAKE_SOURCE_DIR}/build/ut/res
)
##                           CORE UT                        ##
##############################################################

##############################################################
##                          BOX2D UT                        ##
# Add your test source files here
add_executable(${PROJECT_NAME}_box2d
    ${CMAKE_SOURCE_DIR}/ut/test_box2d.cpp
    ${CORE_ENGINE_SRC_FILES}
)

# Include allegro and allegro_ttf libraries
target_link_libraries(${PROJECT_NAME}_box2d
    GTest::GTest
    GTest::Main
    Allegro::allegro
    Allegro::allegro_primitives
    Allegro::allegro_font
    Allegro::allegro_ttf
    Allegro::allegro_image
    box2d::box2d
    fmt::fmt
)

# Include directories
target_include_directories(${PROJECT_NAME}_box2d PRIVATE
    ${CORE_INCLUDES}
    ${ALLEGRO_INCLUDE_DIR}
    ${ALLEGRO_TTF_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/3pp/Box2D/include/  # Include Box2D headers
    ${SPDLOG_INCLUDE_DIR}
    ${FMT_INCLUDE_DIR}
)

add_custom_command(
    TARGET ${PROJECT_NAME}_box2d POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/res
    ${CMAKE_SOURCE_DIR}/build/ut/res
)
##                          BOX2D UT                        ##
##############################################################

##############################################################
##                          CONFG UT                        ##
# Add your test source files here
add_executable(${PROJECT_NAME}_conf
    ${CMAKE_SOURCE_DIR}/ut/test_conf.cpp
    ${CORE_ENGINE_SRC_FILES}
)

# Include allegro and allegro_ttf libraries
target_link_libraries(${PROJECT_NAME}_conf
    GTest::GTest
    GTest::Main
    Allegro::allegro
    Allegro::allegro_primitives
    Allegro::allegro_font
    Allegro::allegro_ttf
    Allegro::allegro_image
    box2d::box2d
    fmt::fmt
)

# Include directories
target_include_directories(${PROJECT_NAME}_conf PRIVATE
    ${CORE_INCLUDES}
    ${ALLEGRO_INCLUDE_DIR}
    ${ALLEGRO_TTF_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/3pp/Box2D/include/  # Include Box2D headers
    ${SPDLOG_INCLUDE_DIR}
    ${FMT_INCLUDE_DIR}
)

add_custom_command(
    TARGET ${PROJECT_NAME}_conf POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/res
    ${CMAKE_SOURCE_DIR}/build/ut/res
)
##                          CONFG UT                        ##
##############################################################


##############################################################
##                     AKR COMMON GAME UT                   ##
# Add your test source files here
add_executable(${PROJECT_NAME}_game_common
    ${CMAKE_SOURCE_DIR}/ut/game/common/test_game_common.cpp
    ${CORE_ENGINE_SRC_FILES}
)

# Include allegro and allegro_ttf libraries
target_link_libraries(${PROJECT_NAME}_game_common
    GTest::GTest
    GTest::Main
    Allegro::allegro
    Allegro::allegro_primitives
    Allegro::allegro_font
    Allegro::allegro_ttf
    Allegro::allegro_image
    box2d::box2d
    fmt::fmt
)

# Include directories
target_include_directories(${PROJECT_NAME}_game_common PRIVATE
    ${CORE_INCLUDES}
    ${ALLEGRO_INCLUDE_DIR}
    ${ALLEGRO_TTF_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/3pp/Box2D/include/  # Include Box2D headers
    ${SPDLOG_INCLUDE_DIR}
    ${FMT_INCLUDE_DIR}
)

add_custom_command(
    TARGET ${PROJECT_NAME}_game_common POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/res
    ${CMAKE_SOURCE_DIR}/build/ut/res
)
##                     AKR COMMON GAME UT                   ##
##############################################################

include(CTest)
include(GoogleTest)

enable_testing()
gtest_discover_tests(${PROJECT_NAME}_core ${PROJECT_NAME}_box2d)

# Add your GTest executable to the tests
add_test(NAME ${PROJECT_NAME}_core COMMAND ${PROJECT_NAME}_core)
add_test(NAME ${PROJECT_NAME}_box2d COMMAND ${PROJECT_NAME}_box2d)