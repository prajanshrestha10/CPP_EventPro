#include "../include/Session.h"
#include <iostream>

Session::Session() : sessionID(0), title(""), speaker(""), attendance(0) {}

Session::Session(int sessionID, const string& title, const string& speaker, int attendance)
    : sessionID(sessionID), title(title), speaker(speaker), attendance(attendance) {}

void Session::setDetails(int sessionID, const string& title, const string& speaker, int attendance) {
    this->sessionID = sessionID;
    this->title = title;
    this->speaker = speaker;
    this->attendance = attendance;
}

void Session::setAttendance(int attendance) { this->attendance = attendance; }
int Session::getSessionID() const { return sessionID; }
string Session::getTitle() const { return title; }
string Session::getSpeaker() const { return speaker; }
int Session::getAttendance() const { return attendance; }

void Session::display() const {
    cout << "Session ID: " << sessionID << "\nTitle: " << title
         << "\nSpeaker: " << speaker << "\nAttendance: " << attendance << '\n';
}
