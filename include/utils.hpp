#include <iostream>
#include <ctime>
using namespace std;

string getCurrentDate() {
    // Get the current time
    time_t currentTime = time(nullptr);

    // Initialize a tm structure
    tm timeInfo = {};

    if (localtime_s(&timeInfo, &currentTime) != 0) {
        return "";
    }

    // Format the date as dd-mm-yyyy
    char buffer[20];
    if (strftime(buffer, sizeof(buffer), "%d-%m-%Y", &timeInfo) == 0) {
        return "";
    }

    return string(buffer);
}