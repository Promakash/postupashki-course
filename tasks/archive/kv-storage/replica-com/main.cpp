#include "http.h"
#include "grpc.h"
#include "kv_storage.h"

#include <argparse/argparse.hpp>

int main(int argc, char** argv) {
    argparse::ArgumentParser parser("KV");

    parser
        .add_argument("http-port", "hp")
        .scan<'i', uint16_t>()
        .required();

    parser
        .add_argument("grpc-port", "gp")
        .scan<'i', uint16_t>()
        .required();

    parser
        .add_argument("join-replica-addr", "j");

    parser.parse_args(argc, argv);

    uint16_t httpPort = parser.get<uint16_t>("http-port");
    uint16_t grpcPort = parser.get<uint16_t>("grpc-port");

    std::string joinReplicaAddr = parser.get<std::string>("join-replica-addr");

    KeyValueStorage storage;

    auto runHTTP = [&](){
        KeyValueHTTPServer server(httpPort, joinReplicaAddr, storage);
        server.Start();
    };

    auto runGRPC = [&](){
        KeyValueServiceImpl grpc(storage);
        /* grpc start here */
    };

    std::thread http(runHTTP);
    std::thread grpc(runGRPC);

    grpc.join();
    http.join();
}
