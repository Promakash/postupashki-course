#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string>
#include <iostream>

#include <variant>

struct ResponseFailure {
    std::string err_msg;
};

struct ResponseSuccess {
    std::string msg;
};

class Client {
public:
    using Response = std::variant<ResponseSuccess, ResponseFailure>;

    Client(const std::string& ip_address, uint16_t port);

    Response Send(const std::string& message);
};
