#ifndef ORGANIZER_H
#define ORGANIZER_H

#include <string>
using namespace std;

class Organizer {
private:
    string name;
    string organization;
    string email;

public:
    Organizer();
    Organizer(const string& name, const string& organization, const string& email);

    void setDetails(const string& name, const string& organization, const string& email);
    string getName() const;
    string getOrganization() const;
    string getEmail() const;
    void display() const;
};

#endif
