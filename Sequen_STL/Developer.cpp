#include "Developer.h"

Developer::Developer() : fullName("Не указано"), position("Junior Dev"), experienceYears(0) {}

Developer::Developer(const string& name, const string& pos, int exp)
    : fullName(name), position(pos), experienceYears(exp) {
}

string Developer::getFullName() const
{
    return fullName; 
}
string Developer::getPosition() const
{ 
    return position; 
}
int Developer::getExperience() const 
{ 
    return experienceYears; 
}

void Developer::setFullName(const string& name) 
{
    fullName = name; 
}
void Developer::setPosition(const string& pos)
{ 
    position = pos;
}
void Developer::setExperience(int exp)
{ 
    experienceYears = exp;
}

void Developer::printTableRow(ostream& os) const {
    os << "| " << left << setw(25) << fullName
        << " | " << setw(20) << position
        << " | " << right << setw(12) << experienceYears << " |\n";
}

bool Developer::operator<(const Developer& other) const {
    return experienceYears < other.experienceYears;
}

bool Developer::operator==(const Developer& other) const {
    return fullName == other.fullName;
}

std::ostream& operator<<(std::ostream& os, const Developer& dev) {
    dev.printTableRow(os);
    return os;
}