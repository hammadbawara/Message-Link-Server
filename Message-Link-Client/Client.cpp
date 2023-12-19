#include <iostream>
#include <asio.hpp>

int main() {
    asio::io_context io_context;
    asio::ip::tcp::socket socket(io_context);

    // Connect to the server
    socket.connect(asio::ip::tcp::endpoint(asio::ip::address::from_string("127.0.0.1"), 8888));

    while (true) {
        // Get a message from the user
        std::cout << "Enter a message for the server (or 'exit' to quit): ";
        std::string message;
        std::getline(std::cin, message);

        // Send the message to the server
        asio::write(socket, asio::buffer(message.c_str(), message.size()));

        if (message == "exit") {
            break;
        }
    }

    return 0;
}
