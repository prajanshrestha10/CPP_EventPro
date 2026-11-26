#ifndef SESSION_H
#define SESSION_H

#include <string>
using namespace std;

class Session {
private:
    int sessionID;
    string title;
    string speaker;
    int attendance;

public:
    Session();
    Session(int sessionID, const string& title, const string& speaker, int attendance);

    void setDetails(int sessionID, const string& title, const string& speaker, int attendance);
    void setAttendance(int attendance);
    int getSessionID() const;
    string getTitle() const;
    string getSpeaker() const;
    int getAttendance() const;
    void display() const;
};

#endif
