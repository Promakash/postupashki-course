#pragma once

#include <crow.h>
#include <cstdint>

#include "kv_storage.h"

class KeyValueHTTPServer {
public:
    KeyValueHTTPServer(uint16_t port, std::string joinReplicaAddr, KeyValueStorage& storage)
            : storage_(storage)
    {
        InitHandlers();
    }

    void Start();

private:
    void InitHandlers() {
        CROW_ROUTE(app_, "/entry").methods("POST"_method)/* (function handler here) */;
        CROW_ROUTE(app_, "/entry").methods("GET"_method)/* (function handler here) */;
        /* for tests */
        CROW_ROUTE(app_, "/readiness").methods("GET"_method)([](){ return "OK"; });
    }

private:
    crow::SimpleApp app_;
    KeyValueStorage& storage_;
};
