#include "UtilityApp.h"
#include <iomanip>

using namespace std;

UtilityApp::UtilityApp()
    : MobileApp(), subscriptionRequired(false), targetOsVersion("Android 10+") {
}

UtilityApp::UtilityApp(const string& name, double rating, double price, Developer* leadDeveloper,
    bool subscriptionRequired, const string& targetOsVersion)
    : MobileApp(name, rating, price, leadDeveloper),
    subscriptionRequired(subscriptionRequired),
    targetOsVersion(targetOsVersion) {
}

bool UtilityApp::isSubscriptionRequired() const {
    return subscriptionRequired;
}

string UtilityApp::getTargetOsVersion() const {
    return targetOsVersion;
}

void UtilityApp::printTableRow(ostream& os) const {
    MobileApp::printTableRow(os);
    os << "   [B2C Утилита] ОС: " << targetOsVersion
        << ", Подписка: " << (subscriptionRequired ? "Да" : "Нет") << "\n";
}