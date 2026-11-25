#include "Developer.h"
#include <iomanip>

using namespace std;

Developer::Developer() : fullName("Не указан"), position("Developer"), experience(0) {}

Developer::Developer(const string& fullName, const string& position, int experience)
    : fullName(fullName), position(position), experience(experience) {
}

string Developer::getFullName() const {
    return fullName;
}

string Developer::getPosition() const {
    return position;
}

int Developer::getExperience() const {
    return experience;
}

void Developer::setPosition(const string& newPosition) {
    position = newPosition;
}

void Developer::setExperience(int newExperience) {
    experience = newExperience;
}

void Developer::printTableRow(ostream& os) const {
    os << left << setw(20) << fullName
        << " | " << setw(22) << position
        << " | Стаж: " << right << setw(2) << experience << " лет\n";
}