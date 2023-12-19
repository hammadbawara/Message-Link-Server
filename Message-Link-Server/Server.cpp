#include <iostream>
#include <asio.hpp>
#include "LinkList.hpp"
#include "utils.hpp"
#include "HashMap.hpp"



int main() {
    asio::io_context io_context;
    asio::ip::tcp::acceptor acceptor(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 8888));

    std::cout << "Server is listening on port 8888...\n";

    while (true) {
        asio::ip::tcp::socket socket(io_context);
        acceptor.accept(socket);

        LinkedList chatList;

        // Hash Map to get command from client
        StringHashMap commandMap;

        commandMap.insert("1", "save");
        commandMap.insert("2", "delete");
        commandMap.insert("3", "display");
        commandMap.insert("4", "exit");

        std::cout << "Connection established with a client.\n";

        // Receive and print messages from the client in a loop
        while (true) {
            char buffer[1024];
            
            size_t bytesRead = socket.read_some(asio::buffer(buffer, sizeof(buffer)));
            if (bytesRead > 0) {
                int i = 0;
                for (i = 0; i < 1024; i++) {
                    if (buffer[i] == -52) {
                        buffer[i] = '\0';
                        break;
                    }
                }
                
                char command = buffer[0];
                string message = buffer;

                if (command == '=') {
                    
                    string command = message.substr(1, message.find(" ") - 1);

                    if (command.size() == 1) {
                        command = commandMap.get(command);
                    }

                    if (command == "save") {
                        string filename = message.substr(message.find(" ") + 1, message.length());
                        if (filename != "") {
                            chatList.saveToJsonFile(filename);
                        }
                        else {
                            std::cout << "Filename is not specified" << endl;
                        }
                        
                    }
                    else if (command == "delete") {
                        string filename = message.substr(message.find(" ") + 1, message.length());
                        if (filename != "") {
                            chatList.deleteChatFile(filename);
                        }
                        else {
                            std::cout << "Filename is not specified" << endl;
                        }
                    }
                    else if (command == "display") {
                        chatList.displayChats();
                    }
                    else if (command == "delete") {
                        break;
                    }
                    else {
                        std::cout << "Invalid command.\n";
                    }

                }else {
                    string time = getCurrentDate();

                    // ip address of client
                    string ip = socket.remote_endpoint().address().to_string();

                    Chat chat(time, ip, message);

                    std::cout << "Message from client: " << message << "\n";

                    chatList.addChat(chat);
                }

                for (int i = 0; i < 1024; i++) {
                    buffer[i] = '\0';
                }

            }
        }
    }

    return 0;
}
