#include "Version.h"
#include <iomanip>

using namespace std;

Version::Version() : number("1.0.0"), releaseDate("01.01.2026"), sizeMb(0.0) {}

Version::Version(const string& number, const string& releaseDate, double sizeMb)
    : number(number), releaseDate(releaseDate), sizeMb(sizeMb) {
}

string Version::getNumber() const {
    return number;
}

string Version::getReleaseDate() const {
    return releaseDate;
}

double Version::getSizeMb() const {
    return sizeMb;
}

void Version::print(ostream& os) const {
    os << "v" << number << " (" << releaseDate << ", " << fixed << setprecision(1) << sizeMb << " MB)";
}