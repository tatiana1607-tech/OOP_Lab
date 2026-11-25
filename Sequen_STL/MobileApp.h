#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "Version.h"
#include "SystemRequirements.h"
#include "Developer.h"
using namespace std;
class MobileApp {
protected:
    string name;
    double rating;
    double price;

    vector<Version> versions;
    SystemRequirements requirements;
    Developer* leadDeveloper;

public:
    MobileApp(const string& n = "Без названия", double r = 0.0, double p = 0.0,
        Developer* dev = nullptr, const SystemRequirements& req = SystemRequirements());

    virtual ~MobileApp();

    string getName() const;
    double getRating() const;
    double getPrice() const;
    Developer* getLeadDeveloper() const;

    void setName(const string& n);
    void setRating(double r);
    void setPrice(double p);
    void setLeadDeveloper(Developer* dev);

    void addVersion(const Version& ver);

    virtual void printTableRow(ostream& os) const;

    bool operator<(const MobileApp& other) const;
    bool operator==(const MobileApp& other) const;
};