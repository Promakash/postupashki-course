class EchoServer {
public:
    EchoServer(uint16_t port);

    void Run() {
        while (!stop) {
            
        }
    }

    void Stop() {
        stop = true;
    }

private:
    std::atomic<bool> stop = false;
}