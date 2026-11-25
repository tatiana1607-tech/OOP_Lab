#include "Version.h"

Version::Version() : versionNumber("1.0.0"), releaseDate("01.01.2026"), sizeMB(50.0) {}

Version::Version(const string& ver, const string& date, double size)
    : versionNumber(ver), releaseDate(date), sizeMB(size) {
}

string Version::getVersionNumber() const { return versionNumber; }
string Version::getReleaseDate() const { return releaseDate; }
double Version::getSizeMB() const { return sizeMB; }

void Version::display() const {
    cout << "v" << versionNumber << " (" << releaseDate << ", " << sizeMB << " ла)";
}