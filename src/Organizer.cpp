#include "../include/Organizer.h"
#include <iostream>

Organizer::Organizer() : name("Not provided"), organization("Not provided"), email("Not provided") {}

Organizer::Organizer(const string& name, const string& organization, const string& email)
    : name(name), organization(organization), email(email) {}

void Organizer::setDetails(const string& name, const string& organization, const string& email) {
    this->name = name;
    this->organization = organization;
    this->email = email;
}

string Organizer::getName() const { return name; }
string Organizer::getOrganization() const { return organization; }
string Organizer::getEmail() const { return email; }

void Organizer::display() const {
    cout << "Organizer: " << name << "\nOrganization: " << organization
         << "\nEmail: " << email << '\n';
}
