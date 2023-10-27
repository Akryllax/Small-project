project(dataGen-tests)

# Find GTest package
find_package(GTest REQUIRED)

# Add your test source files here
add_executable(${PROJECT_NAME}
    ${CMAKE_SOURCE_DIR}/ut/test_main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    GTest::GTest
    GTest::Main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
