#include <iostream>
#include <limits>
#include "fileworking.h"
using namespace std;




int main() {
    while (true) {
        cout << "\n========================\n";
        cout << "        MAIN MENU         \n";
        cout << "========================\n";
        cout << "1. Run experiments\n";
        cout << "2. Demonstrate class functionality\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        // Input validation: handle non-numeric input
        if (!(cin >> choice)) {
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
            cout << "Error: please enter a number between 0 and 2.\n";
            continue;
        }

        switch (choice) {
        case 1:
            all_experiments();
            break;
        case 2:
            run_class_demo();
            break;
        case 0:
            cout << "Exiting program. Goodbye!\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
}