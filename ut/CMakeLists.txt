project(dataGen-tests)

# Find GTest package
find_package(GTest REQUIRED)

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
)

# Include directories
target_include_directories(${PROJECT_NAME}_core PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${ALLEGRO_INCLUDE_DIR}
    ${ALLEGRO_TTF_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/3pp/Box2D/include/  # Include Box2D headers
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
)

# Include directories
target_include_directories(${PROJECT_NAME}_box2d PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${ALLEGRO_INCLUDE_DIR}
    ${ALLEGRO_TTF_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/3pp/Box2D/include/  # Include Box2D headers
)

add_custom_command(
    TARGET ${PROJECT_NAME}_box2d POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/res
    ${CMAKE_SOURCE_DIR}/build/ut/res
)
##                          BOX2D UT                        ##
##############################################################
include(CTest)
include(GoogleTest)

enable_testing()
gtest_discover_tests(${PROJECT_NAME}_core ${PROJECT_NAME}_box2d) 

# Add your GTest executable to the tests
add_test(NAME ${PROJECT_NAME}_core COMMAND ${PROJECT_NAME}_core)
add_test(NAME ${PROJECT_NAME}_box2d COMMAND ${PROJECT_NAME}_box2d)