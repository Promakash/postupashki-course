#include "client.h"

#include <iostream>

#include <sys/types.h>
#include <signal.h>

#include "random_utils.h"
#include "utils.h"

#include <catch2/catch_test_macros.hpp>

pid_t CreateServer(std::string ip, uint16_t port, std::string server_answer) {
    pid_t pid = fork();

    if (pid == 0) {
        std::string port_str = std::to_string(port);
        chdir("../tasks/filesystem/client-socket");
        execlp("python3", "python3", "server.py", ip.c_str(), port_str.c_str(), server_answer.c_str(), nullptr);
    }

    while(!Utils::IsPortListening(port)) {
        sleep(1);
    }

    return pid;
}

TEST_CASE("base connection") {
    size_t connection_count = 15;

    int64_t fd_before_test = Utils::GetFDCount(getpid());

    for (size_t i = 0; i < connection_count; ++i) {
        printf("run connection test %ld / %ld\n", i, connection_count);
        std::string ip = "127.0.0.1";
        
        uint16_t port = 2228;
        
        std::string expected_server_answer = Utils::GenerateRandomString(4096);
        CreateServer(ip, port, expected_server_answer);
        Client client(ip, port);

        std::string client_msg = Utils::GenerateRandomString(4096);

        auto send_res = client.Send(client_msg);

        if (auto* response = std::get_if<ResponseSuccess>(&send_res)) {
            std::string server_answer = response->msg;
            expected_server_answer.append(client_msg);
            REQUIRE(expected_server_answer == server_answer);
        } else {
            REQUIRE(false);
        }

        printf("test success\n");
    }

    int64_t fd_after_test = Utils::GetFDCount(getpid());

    REQUIRE(fd_after_test - fd_before_test <= 0);
}

TEST_CASE("fail check") {

    int64_t fd_before_test = Utils::GetFDCount(getpid());

    try {
        Client client(Utils::GenerateRandomString(10), 22228);
        REQUIRE(false);
    } catch(const std::runtime_error& e) {
    }

    try {
        Client client("127.0.0.1", static_cast<uint16_t>(1));
        REQUIRE(false);
    } catch(const std::runtime_error& e) {
    }


    {
        std::string ip = "127.0.0.1";
        uint16_t port = 14888;
        pid_t server_pid = CreateServer(ip, port, "");
        kill(server_pid, SIGKILL);
        Client client(ip, port);
        auto send_res = client.Send("must be response error");

        if (auto* response = std::get_if<ResponseFailure>(&send_res)) {
            REQUIRE(!response->err_msg.empty());
        } else {
            REQUIRE(false);
        }
    }

    int64_t fd_after_test = Utils::GetFDCount(getpid());

    REQUIRE(fd_after_test - fd_before_test <= 0);
}