#include <filesystem>

class OFStream {
public:
    OFStream(std::filesystem::path path);

    template <typename T>
    OFStream& operator<<(const T& value);

    OFStream& Write(const char* str, size_t count);

    void Flush();
};