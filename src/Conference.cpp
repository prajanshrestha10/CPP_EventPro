#include "../include/Conference.h"
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

namespace {
const string RESET = "\033[0m";
const string CYAN = "\033[1;36m";
const string GREEN = "\033[1;32m";
const string YELLOW = "\033[1;33m";
const string RED = "\033[1;31m";
const string BLUE = "\033[1;34m";

void sectionTitle(const string& title) {
    cout << "\n" << CYAN << "  +----------------------------------------------------------------+\n"
         << "  |  " << left << setw(62) << title << "|\n"
         << "  +----------------------------------------------------------------+\n" << RESET;
}

void success(const string& message) { cout << GREEN << "\n  [OK] " << message << RESET << "\n"; }
void warning(const string& message) { cout << YELLOW << "\n  [!]  " << message << RESET << "\n"; }
void error(const string& message) { cout << RED << "\n  [X]  " << message << RESET << "\n"; }

int readInt(const string& prompt) {
    int value;
    while (true) {
        cout << "  " << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        error("Please enter a valid whole number.");
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int readNonNegativeInt(const string& prompt) {
    int value;
    do {
        value = readInt(prompt);
        if (value < 0) warning("This value cannot be negative. Please try again.");
    } while (value < 0);
    return value;
}

string readText(const string& prompt) {
    string value;
    do {
        cout << "  " << prompt;
        getline(cin, value);
        if (value.empty()) warning("This field cannot be empty.");
    } while (value.empty());
    return value;
}

void printSessionTableHeader() {
    cout << BLUE << "  " << left << setw(8) << "ID" << setw(34) << "SESSION TITLE"
         << setw(22) << "SPEAKER" << right << setw(10) << "ATTENDANCE" << RESET << "\n";
    cout << "  " << string(74, '-') << "\n";
}
}

Conference::Conference()
    : conferenceID(1001), conferenceName("EventPro Conference"), organizer(), sessions(), sessionCount(0) {}

Conference::Conference(int conferenceID, const string& conferenceName)
    : conferenceID(conferenceID), conferenceName(conferenceName), organizer(), sessions(), sessionCount(0) {}

int Conference::getConferenceID() const { return conferenceID; }
string Conference::getConferenceName() const { return conferenceName; }
int Conference::getSessionCount() const { return sessionCount; }

void Conference::enterOrganizerInformation() {
    sectionTitle("ORGANIZER INFORMATION");
    string name = readText("Organizer name : ");
    string organization = readText("Organization    : ");
    string email = readText("Email address   : ");
    organizer.setDetails(name, organization, email);
    success("Organizer information saved successfully.");
}

void Conference::addSession() {
    sectionTitle("ADD A CONFERENCE SESSION");
    if (sessionCount >= 8) { error("Session capacity reached (8 of 8). No more sessions can be added."); return; }
    cout << "  " << YELLOW << "Available session slots: " << (8 - sessionCount) << RESET << "\n\n";
    int id = readNonNegativeInt("Session ID (positive number): ");
    if (id == 0 || findSessionIndex(id) != -1) { error("Session ID must be positive and unique. Nothing was added."); return; }
    string title = readText("Session title              : ");
    string speaker = readText("Speaker name               : ");
    int attendance = readNonNegativeInt("Attendance                  : ");
    sessions[sessionCount].setDetails(id, title, speaker, attendance);
    ++sessionCount;
    success("'" + title + "' has been added to the conference.");
    cout << "  " << BLUE << "Sessions registered: " << sessionCount << "/8" << RESET << "\n";
}

void Conference::displayAllSessions() const {
    sectionTitle("CONFERENCE SESSION DIRECTORY");
    if (sessionCount == 0) { warning("No sessions have been added yet."); return; }
    printSessionTableHeader();
    for (int i = 0; i < sessionCount; ++i) {
        cout << "  " << left << setw(8) << sessions[i].getSessionID()
             << setw(34) << sessions[i].getTitle().substr(0, 33)
             << setw(22) << sessions[i].getSpeaker().substr(0, 21)
             << right << setw(10) << sessions[i].getAttendance() << "\n";
    }
    cout << "  " << string(74, '-') << "\n"
         << "  " << CYAN << "Showing " << sessionCount << " of 8 available sessions." << RESET << "\n";
}

int Conference::findSessionIndex(int sessionID) const {
    for (int i = 0; i < sessionCount; ++i)
        if (sessions[i].getSessionID() == sessionID) return i;
    return -1;
}

void Conference::searchSession() const {
    sectionTitle("SEARCH FOR A SESSION");
    if (sessionCount == 0) { warning("There are no sessions to search."); return; }
    int id = readNonNegativeInt("Enter session ID: ");
    int index = findSessionIndex(id);
    if (index == -1) { error("No session found with ID " + to_string(id) + "."); return; }
    success("Session found.");
    sessions[index].display();
}

void Conference::displayHighestAttendance() const {
    sectionTitle("HIGHEST SESSION ATTENDANCE");
    if (sessionCount == 0) { warning("No attendance data is available."); return; }
    int best = 0;
    for (int i = 1; i < sessionCount; ++i)
        if (sessions[i].getAttendance() > sessions[best].getAttendance()) best = i;
    cout << GREEN << "  TOP ATTENDED SESSION" << RESET << "\n";
    sessions[best].display();
}

void Conference::displayLowestAttendance() const {
    sectionTitle("LOWEST SESSION ATTENDANCE");
    if (sessionCount == 0) { warning("No attendance data is available."); return; }
    int lowest = 0;
    for (int i = 1; i < sessionCount; ++i)
        if (sessions[i].getAttendance() < sessions[lowest].getAttendance()) lowest = i;
    cout << YELLOW << "  LOWEST ATTENDED SESSION" << RESET << "\n";
    sessions[lowest].display();
}

double calculateAverageAttendance(const Session* ptr, int size) {
    if (size <= 0) return 0.0;
    int total = 0;
    for (int i = 0; i < size; ++i) total += (ptr + i)->getAttendance();
    return static_cast<double>(total) / size;
}

void Conference::displayAverageAttendance() const {
    sectionTitle("AVERAGE ATTENDANCE ANALYTICS");
    if (sessionCount == 0) { warning("Add sessions before calculating the average."); return; }
    cout << "\n  Number of sessions : " << sessionCount << "\n"
         << "  Average attendance: " << GREEN << fixed << setprecision(2)
         << calculateAverageAttendance(sessions, sessionCount) << RESET << " people per session\n";
}

void Conference::updateAttendance() {
    sectionTitle("UPDATE SESSION ATTENDANCE");
    if (sessionCount == 0) { warning("There are no sessions to update."); return; }
    int id = readNonNegativeInt("Enter session ID: ");
    int index = findSessionIndex(id);
    if (index == -1) { error("Session not found. Please check the ID."); return; }
    cout << "  Current attendance: " << sessions[index].getAttendance() << "\n";
    int newAttendance = readNonNegativeInt("Enter new attendance: ");
    Session* sessionPtr = &sessions[index];
    sessionPtr->setAttendance(newAttendance);
    success("Attendance updated successfully.");
    cout << "  New attendance: " << GREEN << sessionPtr->getAttendance() << RESET << "\n";
}

void Conference::displayTotalAttendance() const {
    sectionTitle("TOTAL CONFERENCE ATTENDANCE");
    int total = 0;
    for (int i = 0; i < sessionCount; ++i) total += sessions[i].getAttendance();
    cout << "\n  Registered sessions : " << sessionCount << "\n"
         << "  Total attendees     : " << GREEN << total << RESET << "\n";
}

void Conference::displayConferenceSummary() const {
    sectionTitle("CONFERENCE OVERVIEW & SUMMARY");
    cout << "  Conference ID   : " << conferenceID << "\n"
         << "  Conference name : " << conferenceName << "\n"
         << "  Sessions added  : " << sessionCount << "/8\n\n"
         << BLUE << "  ORGANIZER DETAILS" << RESET << "\n";
    organizer.display();
    cout << "\n" << BLUE << "  SESSION OVERVIEW" << RESET << "\n";
    if (sessionCount == 0) warning("No sessions have been registered yet.");
    else {
        printSessionTableHeader();
        for (int i = 0; i < sessionCount; ++i)
            cout << "  " << left << setw(8) << sessions[i].getSessionID()
                 << setw(34) << sessions[i].getTitle().substr(0, 33)
                 << setw(22) << sessions[i].getSpeaker().substr(0, 21)
                 << right << setw(10) << sessions[i].getAttendance() << "\n";
        int total = 0;
        for (int i = 0; i < sessionCount; ++i) total += sessions[i].getAttendance();
        cout << "\n  Total attendance   : " << GREEN << total << RESET << "\n"
             << "  Average attendance : " << GREEN << fixed << setprecision(2)
             << calculateAverageAttendance(sessions, sessionCount) << RESET << "\n";
    }
}

void Conference::displayEmergingTechnologyInformation() const {
    sectionTitle("EMERGING COMPUTING | FUTURE POSSIBILITIES");
    cout << "\n  " << BLUE << "[1] ARTIFICIAL INTELLIGENCE (AI)" << RESET << "\n"
         << "  AI could analyze previous EventPro attendance records to predict\n"
         << "  session turnout. These predictions could help organizers recommend\n"
         << "  sessions and choose appropriately sized rooms.\n\n"
         << "  " << BLUE << "[2] BLOCKCHAIN" << RESET << "\n"
         << "  Blockchain could provide tamper-resistant attendance records and\n"
         << "  help verify participation certificates, making attendance easier\n"
         << "  to audit and trust.\n\n"
         << "  " << BLUE << "[3] QUANTUM COMPUTING" << RESET << "\n"
         << "  Future quantum optimization methods could explore complex combinations\n"
         << "  of rooms, speakers, and session times to reduce scheduling conflicts.\n";
}
