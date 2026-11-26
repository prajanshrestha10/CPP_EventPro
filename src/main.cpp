#include "../include/Conference.h"
#include <iostream>
#include <limits>
#include <string>

using namespace std;

namespace {
const string RESET = "\033[0m";
const string CYAN = "\033[1;36m";
const string BLUE = "\033[1;34m";
const string GREEN = "\033[1;32m";
const string YELLOW = "\033[1;33m";
const string RED = "\033[1;31m";
const string DIM = "\033[2m";

void printMenu() {
    cout << "\n" << CYAN
         << "  +--------------------------------------------------------------+\n"
         << "  |                         E V E N T P R O                      |\n"
         << "  |             CONFERENCE & EVENT MANAGEMENT SYSTEM             |\n"
         << "  +--------------------------------------------------------------+\n" << RESET;
    cout << "  " << DIM << "Manage conference details, sessions, and attendance" << RESET << "\n\n";
    cout << "  " << BLUE << "CONFERENCE MANAGEMENT" << RESET << "\n"
         << "   " << YELLOW << "1" << RESET << "  Enter organizer information\n"
         << "   " << YELLOW << "2" << RESET << "  Add a conference session\n"
         << "   " << YELLOW << "3" << RESET << "  Display all sessions\n"
         << "   " << YELLOW << "4" << RESET << "  Search for a session\n\n";
    cout << "  " << BLUE << "ATTENDANCE ANALYTICS" << RESET << "\n"
         << "   " << YELLOW << "5" << RESET << "  Highest attendance\n"
         << "   " << YELLOW << "6" << RESET << "  Lowest attendance\n"
         << "   " << YELLOW << "7" << RESET << "  Average attendance\n"
         << "   " << YELLOW << "8" << RESET << "  Update attendance\n"
         << "   " << YELLOW << "9" << RESET << "  Total attendance\n\n";
    cout << "  " << BLUE << "REPORTS & INFORMATION" << RESET << "\n"
         << "  " << YELLOW << "10" << RESET << "  Complete conference summary\n"
         << "  " << YELLOW << "11" << RESET << "  Emerging computing / future technology\n\n"
         << "   " << RED << "0" << RESET << "  Exit\n"
         << "  --------------------------------------------------------------\n";
}
}

int main() {
    Conference conference(1001, "Technology Innovation Summit 2026");
    int choice = -1;

    do {
        printMenu();
        cout << "  " << CYAN << "Enter your choice > " << RESET;
        if (!(cin >> choice)) {
            cout << "\n  " << RED << "[!] Invalid input. Enter a menu number." << RESET << "\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << '\n';

        switch (choice) {
            case 1: conference.enterOrganizerInformation(); break;
            case 2: conference.addSession(); break;
            case 3: conference.displayAllSessions(); break;
            case 4: conference.searchSession(); break;
            case 5: conference.displayHighestAttendance(); break;
            case 6: conference.displayLowestAttendance(); break;
            case 7: conference.displayAverageAttendance(); break;
            case 8: conference.updateAttendance(); break;
            case 9: conference.displayTotalAttendance(); break;
            case 10: conference.displayConferenceSummary(); break;
            case 11: conference.displayEmergingTechnologyInformation(); break;
            case 0:
                cout << GREEN << "  +--------------------------------------------------------------+\n"
                     << "  |             Thank you for using EventPro!                    |\n"
                     << "  |                    Have a great day.                         |\n"
                     << "  +--------------------------------------------------------------+\n" << RESET;
                break;
            default:
                cout << RED << "  [!] Invalid selection. Choose a number from 0 to 11." << RESET << "\n";
        }
    } while (choice != 0);
    return 0;
}
