#include "server.h"

#include <thread>

#include <catch2/catch_test_macros.hpp>

#include <sys/types.h>
#include <sys/wait.h>

#include <unistd.h>
#include "unix_utils.h"

pid_t CreateClient(uint16_t server_port) {
    pid_t pid = fork();

    if (pid == 0) {
        std::string port_str = std::to_string(port);
        chdir("../tasks/filesystem/server-socket");
        execlp("python3", "python3", "client.py", port_str.c_str(), nullptr);
    }

    return pid;
}

TEST_CASE("client connections") {
    FDBalanceChecker fd_checker;

    uint16_t port = 2228;

    EchoServer server(port);

    std::thread server_thread([&server](){
        server.Run();
    });

    size_t fail_wait_count = 0;
    while(!Utils::IsPortListening(port)) {
        REQUIRE(fail_wait_count++ < 10);
        sleep(1);
    }

    size_t connection_count = 15;
    for (size_t i = 0; i < connection_count; ++i) {
        auto client_pid = CreateClient(port);

        int status = 0;
        waitpid(client_pid, &status, 0);

        REQUIRE(WIFEXITED(status) != 0);
        REQUIRE(WEXITSTATUS(status) == 0);
    }

    server.Stop();
    server_thread.join();
}