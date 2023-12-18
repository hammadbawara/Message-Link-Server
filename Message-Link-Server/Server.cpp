#include <iostream>
#include <asio.hpp>

int main() {
    asio::io_context io_context;
    asio::ip::tcp::acceptor acceptor(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 8888));

    std::cout << "Server is listening on port 8888...\n";

    while (true) {
        asio::ip::tcp::socket socket(io_context);
        acceptor.accept(socket);

        std::cout << "Connection established with a client.\n";

        // Receive and print messages from the client in a loop
        while (true) {
            char buffer[1024];
            
            size_t bytesRead = socket.read_some(asio::buffer(buffer, sizeof(buffer)));
            if (bytesRead > 0) {
                int i = 0;
                for (int i = 0; i < 1024; i++) {
                    if (buffer[i] == -52) {
                        buffer[i] = '\0';
                        break;
                    }
                }
                std::cout << "Message from client: " << buffer << "\n";

                for (int i = 0; i < 1024; i++) {
                    buffer[i] = '\0';
                }

            }
        }
    }

    return 0;
}