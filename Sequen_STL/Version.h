#pragma once
#include <iostream>
#include <string>
using namespace std;
class Version {
private:
    string versionNumber;
    string releaseDate;
    double sizeMB;

public:
    Version();
    Version(const string& ver, const string& date, double size);

    string getVersionNumber() const;
    string getReleaseDate() const;
    double getSizeMB() const;

    void display() const;
};