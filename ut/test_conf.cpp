#include "Configuration.h"
#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>

// Include the Configuration class here

class ConfigurationTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Remove existing config file before each test
        std::filesystem::remove(configFilePath);
    }

    void TearDown() override {
        // Remove the config file created during the test
        std::filesystem::remove(configFilePath);
    }

    ConfigurationTest() : configFilePath("test_config.ini") {}

    const std::string configFilePath;
};

TEST_F(ConfigurationTest, LoadAndSave) {
    ASSERT_TRUE(Configuration::load());

    // Check if the config file has been created
    ASSERT_TRUE(std::filesystem::exists(configFilePath));

    // Modify a value
    Configuration::setValue("test_key", "test_value");

    // Save the configuration
    ASSERT_TRUE(Configuration::save());

    // Load the configuration again
    ASSERT_TRUE(Configuration::load());

    // Check if the modified value is retrieved correctly
    ASSERT_EQ(Configuration::getValue("test_key"), "test_value");
}

TEST_F(ConfigurationTest, GetValueDefault) {
    ASSERT_TRUE(Configuration::load());

    // Try to get a non-existing key with a default value
    std::string value = Configuration::getValue("non_existing_key", "default_value");

    // Check if the default value is returned
    ASSERT_EQ(value, "default_value");
}

TEST_F(ConfigurationTest, SetValueAndGet) {
    ASSERT_TRUE(Configuration::load());

    // Set a value
    Configuration::setValue("test_key", "test_value");

    // Get the value and check if it matches what was set
    ASSERT_EQ(Configuration::getValue("test_key"), "test_value");
}

TEST_F(ConfigurationTest, GetNonExistingValue) {
    ASSERT_TRUE(Configuration::load());

    // Try to get a non-existing key
    std::string value = Configuration::getValue("non_existing_key");

    // Check if an empty string is returned
    ASSERT_EQ(value, "");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
