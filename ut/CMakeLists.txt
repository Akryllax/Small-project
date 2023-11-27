project(dataGen-tests)

include(CTest)
enable_testing()

# Find GTest package
find_package(GTest REQUIRED)

# Add your test source files here
add_executable(${PROJECT_NAME}
    ${CMAKE_SOURCE_DIR}/ut/test_main.cpp
)

# Include allegro and allegro_ttf libraries
target_link_libraries(${PROJECT_NAME}
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
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${ALLEGRO_INCLUDE_DIR}
    ${ALLEGRO_TTF_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/3pp/Box2D/include/  # Include Box2D headers
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

# Add your GTest executable to the tests
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})