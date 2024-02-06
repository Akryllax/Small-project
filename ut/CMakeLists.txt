cmake_minimum_required(VERSION 3.12)

project(SpaceDissident-tests)


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


# Find GTest package
find_package(GTest REQUIRED)

set(CORE_INCLUDES
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/common
    ${CMAKE_SOURCE_DIR}/include/core
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

##############################################################
##                           CORE UT                        ##
# Add your test source files here
add_executable(${PROJECT_NAME}_core
    ${CMAKE_SOURCE_DIR}/ut/test_main.cpp
)

# Include allegro and allegro_ttf libraries
target_link_libraries(${PROJECT_NAME}_core
    GTest::GTest
    GTest::Main
    ${ALLEGRO_LIBRARY_PATH}/liballegro.so
    ${ALLEGRO_LIBRARY_PATH}/liballegro_primitives.so
    ${ALLEGRO_LIBRARY_PATH}/liballegro_font.so
    ${ALLEGRO_TTF_LIBRARY_PATH}/liballegro_ttf.so
    ${ALLEGRO_TTF_LIBRARY_PATH}/liballegro_image.so
    ${CMAKE_SOURCE_DIR}/lib/bin/libbox2d.a
    fmt
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
)

# Include allegro and allegro_ttf libraries
target_link_libraries(${PROJECT_NAME}_box2d
    GTest::GTest
    GTest::Main
    ${ALLEGRO_LIBRARY_PATH}/liballegro.so
    ${ALLEGRO_LIBRARY_PATH}/liballegro_primitives.so
    ${ALLEGRO_LIBRARY_PATH}/liballegro_font.so
    ${ALLEGRO_TTF_LIBRARY_PATH}/liballegro_ttf.so
    ${ALLEGRO_TTF_LIBRARY_PATH}/liballegro_image.so
    ${CMAKE_SOURCE_DIR}/lib/bin/libbox2d.a
    fmt
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
)

# Include allegro and allegro_ttf libraries
target_link_libraries(${PROJECT_NAME}_conf
    GTest::GTest
    GTest::Main
    ${ALLEGRO_LIBRARY_PATH}/liballegro.so
    ${ALLEGRO_LIBRARY_PATH}/liballegro_primitives.so
    ${ALLEGRO_LIBRARY_PATH}/liballegro_font.so
    ${ALLEGRO_TTF_LIBRARY_PATH}/liballegro_ttf.so
    ${ALLEGRO_TTF_LIBRARY_PATH}/liballegro_image.so
    ${CMAKE_SOURCE_DIR}/lib/bin/libbox2d.a
    fmt
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
include(CTest)
include(GoogleTest)

enable_testing()
gtest_discover_tests(${PROJECT_NAME}_core ${PROJECT_NAME}_box2d)

# Add your GTest executable to the tests
add_test(NAME ${PROJECT_NAME}_core COMMAND ${PROJECT_NAME}_core)
add_test(NAME ${PROJECT_NAME}_box2d COMMAND ${PROJECT_NAME}_box2d)