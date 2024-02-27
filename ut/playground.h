#include <string>
#include <variant>
#include <cstdint>
#include <string_view>
#include <array>

// Define a struct for 3-byte integer
struct uint24_t {
    uint8_t data[3];
};

// Define the template class
/*
    Permutations
        4 x uint8_t
        2 x uint16_t
        1 x uint24_t + 1 x uint8_t
        1 x unint32_y
 */

template<typename T>
class J1939MsgBuffer {
public:
    using PayloadVariant = std::variant<uint32_t, std::pair<uint24_t, uint8_t>, std::pair<uint16_t, uint16_t>, std::array<uint8_t, 4>>;

    static J1939MsgBuffer LoadFromString(std::string_view input) {
        J1939MsgBuffer ac;
        // Initialize ac based on input
        // Example: ac.J1939MsgBufferPayload = some_value;
        return ac;
    }

    std::string const& ToString()
    {
        return std::to_string(payload_);
    };

    std::array<uint8_t, 4> GetByteArray() const
    {

    };

    T const& GetPayload() const {
        // Extract and return the payload
        return payload_;
    };

private:
    J1939MsgBuffer(J1939MsgBuffer const&) = delete;
    T payload_;
};
