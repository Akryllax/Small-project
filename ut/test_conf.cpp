#include "Configuration.h"
#include "spdlog/spdlog.h"
#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>
#include "Logger.h"

// Include the Configuration class here

class ConfigurationTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Remove existing config file before each test
        std::filesystem::remove(configFilePath);
        Akr::Logger::init("ConfigurationTest.log");
    }

    void TearDown() override {
        // Remove the config file created during the test
        std::filesystem::remove(configFilePath);
    }

    ConfigurationTest() {}

    const std::string configFilePath = Akr::Configuration::getConfigFilePath();
};

TEST_F(ConfigurationTest, LoadAndSave) {
    ASSERT_TRUE(Akr::Configuration::load());
    ASSERT_TRUE(Akr::Configuration::save());

    // Check if the config file has been created
    ASSERT_TRUE(std::filesystem::exists(configFilePath));

    // Modify a value
    Akr::Configuration::setValue("test_key", "test_value");

    // Save the configuration
    ASSERT_TRUE(Akr::Configuration::save());

    // Load the configuration again
    ASSERT_TRUE(Akr::Configuration::load());

    // Check if the modified value is retrieved correctly
    ASSERT_EQ(Akr::Configuration::getValue("test_key"), "test_value");
}

TEST_F(ConfigurationTest, GetValueDefault) {
    ASSERT_TRUE(Akr::Configuration::load());

    // Try to get a non-existing key with a default value
    std::string value = Akr::Configuration::getValue("non_existing_key", "default_value");

    // Check if the default value is returned
    ASSERT_EQ(value, "default_value");
}

TEST_F(ConfigurationTest, SetValueAndGet) {
    ASSERT_TRUE(Akr::Configuration::load());

    // Set a value
    Akr::Configuration::setValue("test_key", "test_value");

    // Get the value and check if it matches what was set
    ASSERT_EQ(Akr::Configuration::getValue("test_key"), "test_value");
}

TEST_F(ConfigurationTest, GetNonExistingValue) {
    ASSERT_TRUE(Akr::Configuration::load());

    // Try to get a non-existing key
    std::string value = Akr::Configuration::getValue("non_existing_key");

    // Check if an empty string is returned
    ASSERT_EQ(value, "");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
