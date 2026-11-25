#include "MobileApp.h"

MobileApp::MobileApp(const string& n, double r, double p, Developer* dev, const SystemRequirements& req)
    : name(n), rating(r), price(p), leadDeveloper(dev), requirements(req) {
}

MobileApp::~MobileApp() {}

string MobileApp::getName() const { return name; }
double MobileApp::getRating() const { return rating; }
double MobileApp::getPrice() const { return price; }
Developer* MobileApp::getLeadDeveloper() const { return leadDeveloper; }

void MobileApp::setName(const string& n) { name = n; }
void MobileApp::setRating(double r) { rating = r; }
void MobileApp::setPrice(double p) { price = p; }
void MobileApp::setLeadDeveloper(Developer* dev) { leadDeveloper = dev; }

void MobileApp::addVersion(const Version& ver) {
    versions.push_back(ver);
}

void MobileApp::printTableRow(ostream& os) const {
    os << "| " << left << setw(20) << name
        << " | " << right << setw(7) << fixed << setprecision(1) << rating
        << " | " << setw(15) << fixed << setprecision(2) << price << " руб."
        << " | " << left << setw(20) << (leadDeveloper ? leadDeveloper->getFullName() : "Не назначен")
        << " | " << left << setw(8) << (versions.empty() ? "N/A" : versions.back().getVersionNumber());
}

bool MobileApp::operator<(const MobileApp& other) const {
    return rating < other.rating;
}

bool MobileApp::operator==(const MobileApp& other) const {
    return name == other.name;
}