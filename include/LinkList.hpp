#include <iostream>
using namespace std;

// Define the Chat structure
struct Chat {
    string message;
    string time;
    string ipAddress;

    // Constructor for convenient initialization
    Chat(const string& msg, const string& t, const string& ip)
        : message(msg), time(t), ipAddress(ip) {}
};

// Define the Node structure for the linked list
struct Node {
    Chat data;
    Node* next;

    // Constructor for convenient initialization
    Node(const Chat& chat) : data(chat), next(nullptr) {}
};

// Define the LinkedList class
class LinkedList {
private:
    Node* head;

public:
    // Constructor to initialize an empty list
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

    // Destructor to free memory when the list is destroyed
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
