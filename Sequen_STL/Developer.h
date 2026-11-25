#pragma once
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
class Developer {
private:
    string fullName;
    string position;
    int experienceYears;

public:
    Developer();
    Developer(const string& name, const string& pos, int exp);

    string getFullName() const;
    string getPosition() const;
    int getExperience() const;

    void setFullName(const string& name);
    void setPosition(const string& pos);
    void setExperience(int exp);

    void printTableRow(ostream& os) const;

    bool operator<(const Developer& other) const;
    bool operator==(const Developer& other) const;

    friend ostream& operator<<(ostream& os, const Developer& dev);
};