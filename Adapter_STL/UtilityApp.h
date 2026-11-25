#pragma once
#include "MobileApp.h"
#include <string>

class UtilityApp : public MobileApp {
private:
    bool subscriptionRequired;
    std::string targetOsVersion;

public:
    UtilityApp();
    UtilityApp(const std::string& name, double rating, double price, Developer* leadDeveloper,
        bool subscriptionRequired, const std::string& targetOsVersion);

    bool isSubscriptionRequired() const;
    std::string getTargetOsVersion() const;

    void printTableRow(std::ostream& os) const override;
};
