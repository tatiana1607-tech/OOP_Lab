#pragma once
#include <string>
#include <iostream>

class Developer {
private:
    std::string fullName;
    std::string position;
    int experience;

public:
    Developer();
    Developer(const std::string& fullName, const std::string& position, int experience);

    std::string getFullName() const;
    std::string getPosition() const;
    int getExperience() const;

    void setPosition(const std::string& newPosition);
    void setExperience(int newExperience);

    void printTableRow(std::ostream& os) const;
};
