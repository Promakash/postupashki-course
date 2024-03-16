#include <string>
#include <stdexcept>

class KeyValueStorage {
    void AddEntry(std::string_view key, std::string_view entry) {
        throw std::runtime_error("KeyValueStorage AddEntry not implemented!");
    }

    std::string GetValue(std::string_view key) {
        throw std::runtime_error("GetValue AddEntry not implemented!");
    }
};
