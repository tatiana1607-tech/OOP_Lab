
#include "MobileApp.h"
#include <iomanip>

using namespace std;

MobileApp::MobileApp()
    : name("Без названия"), rating(0.0), price(0.0), leadDeveloper(nullptr) {
}

MobileApp::MobileApp(const string& name, double rating, double price, Developer* leadDeveloper)
    : name(name), rating(rating), price(price), leadDeveloper(leadDeveloper) {
}

MobileApp::~MobileApp() {}

string MobileApp::getName() const {
    return name;
}

double MobileApp::getRating() const {
    return rating;
}

double MobileApp::getPrice() const {
    return price;
}

Developer* MobileApp::getLeadDeveloper() const {
    return leadDeveloper;
}

void MobileApp::setRating(double newRating) {
    rating = newRating;
}

void MobileApp::setPrice(double newPrice) {
    price = newPrice;
}

void MobileApp::setLeadDeveloper(Developer* dev) {
    leadDeveloper = dev;
}

void MobileApp::addVersion(const Version& ver) {
    versions.push_back(ver);
}

void MobileApp::printTableRow(ostream& os) const {
    os << "| " << left << setw(20) << name
        << " | " << right << setw(7) << fixed << setprecision(1) << rating
        << " | " << right << setw(11) << fixed << setprecision(2) << price << " руб."
        << " | " << left << setw(31) << (leadDeveloper ? leadDeveloper->getFullName() : "Не назначен");
}
