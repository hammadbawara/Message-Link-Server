#include <iostream>
#include <ctime>
using namespace std;

string getCurrentDate() {
    // Get the current time
    time_t currentTime = time(nullptr);

    // Initialize a tm structure
    tm timeInfo = {};

    // Use localtime_s to populate the tm structure
    if (localtime_s(&timeInfo, &currentTime) != 0) {
        // Handle error, for simplicity, let's just return an empty string
        return "";
    }

    // Format the date as dd-mm-yyyy
    char buffer[20];
    if (strftime(buffer, sizeof(buffer), "%d-%m-%Y", &timeInfo) == 0) {
        // Handle error, for simplicity, let's just return an empty string
        return "";
    }

    return string(buffer);
}