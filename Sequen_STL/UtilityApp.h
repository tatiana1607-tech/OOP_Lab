#pragma once
#include "MobileApp.h"

class UtilityApp : public MobileApp {
private:
    bool isSubscriptionRequired;
    string targetOSVersion;

public:
    UtilityApp(const string& n = "Утилита", double r = 0.0, double p = 0.0,
        Developer* dev = nullptr, bool sub = false, const string& osVer = "Android 10+");

    bool getIsSubscriptionRequired() const;
    string getTargetOSVersion() const;

    void setIsSubscriptionRequired(bool sub);
    void setTargetOSVersion(const string& osVer);

    void printTableRow(ostream& os) const override;
};