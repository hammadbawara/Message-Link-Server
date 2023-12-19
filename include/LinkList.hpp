#include <iostream>
#include <fstream>
#include <json.hpp>
using json = nlohmann::json;
using namespace std;

struct Chat {
    string message;
    string time;
    string ipAddress;

    Chat(const string& msg, const string& t, const string& ip)
        : message(msg), time(t), ipAddress(ip) {}
};

struct Node {
    Chat data;
    Node* next;

    Node(const Chat& chat) : data(chat), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    // Function to add a new node to the list
    void addChat(const Chat& chat) {
        Node* newNode = new Node(chat);
        newNode->next = head;
        head = newNode;
    }

    // Function to display all chats in the list
    void displayChats() {
        Node* current = head;
        while (current != nullptr) {
            cout << "Message: " << current->data.message << "\n";
            cout << "Time: " << current->data.time << "\n";
            cout << "IP Address: " << current->data.ipAddress << "\n\n";
            current = current->next;
        }
    }

     //Function to save the linked list data to a file in JSON format
    void saveToJsonFile(const string& filename) {
        json jsonData;

        Node* current = head;
        while (current != nullptr) {
            json chatEntry;
            chatEntry["message"] = current->data.message;
            chatEntry["time"] = current->data.time;
            chatEntry["ipAddress"] = current->data.ipAddress;
            jsonData.push_back(chatEntry);

            current = current->next;
        }

        // Save JSON data to a file
        ofstream file(filename);
        if (file.is_open()) {
            file << jsonData.dump(4);
            file.close();
            cout << "Data saved to " << filename << " successfully.\n";
        }
        else {
            cerr << "Unable to open file " << filename << " for writing.\n";
        }
    }

    //Function to delete a file
    void deleteChatFile(string filename) {
        if (remove(filename.c_str()) != 0) {
            cerr << "Unable to delete file " << filename << "\n";
        }
        else {
            cout << "File " << filename << " deleted successfully.\n";
        }
    }

     //Destructor to free memory when the list is destroyed
    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }
};

