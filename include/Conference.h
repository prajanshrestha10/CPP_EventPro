#ifndef CONFERENCE_H
#define CONFERENCE_H

#include "Organizer.h"
#include "Session.h"
#include <string>
using namespace std;

class Conference {
private:
    const int conferenceID;
    string conferenceName;
    Organizer organizer;       // Conference HAS-A Organizer
    Session sessions[8];       // Conference HAS-A collection of Sessions
    int sessionCount;

    int findSessionIndex(int sessionID) const;

public:
    Conference();
    Conference(int conferenceID, const string& conferenceName);

    void enterOrganizerInformation();
    void addSession();
    void displayAllSessions() const;
    void searchSession() const;
    void displayHighestAttendance() const;
    void displayLowestAttendance() const;
    void displayAverageAttendance() const;
    void updateAttendance();
    void displayTotalAttendance() const;
    void displayConferenceSummary() const;
    void displayEmergingTechnologyInformation() const;

    int getConferenceID() const;
    string getConferenceName() const;
    int getSessionCount() const;
};

// Pointer parameter and pointer arithmetic are used to process the Session array.
double calculateAverageAttendance(const Session* ptr, int size);

#endif
