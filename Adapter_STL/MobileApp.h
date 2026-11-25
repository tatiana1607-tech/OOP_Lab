#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Developer.h"
#include "Version.h"

class MobileApp {
protected:
    std::string name;
    double rating;
    double price;
    Developer* leadDeveloper;
    std::vector<Version> versions;

public:
    MobileApp();
    MobileApp(const std::string& name, double rating, double price, Developer* leadDeveloper);
    virtual ~MobileApp();

    std::string getName() const;
    double getRating() const;
    double getPrice() const;
    Developer* getLeadDeveloper() const;

    void setRating(double newRating);
    void setPrice(double newPrice);
    void setLeadDeveloper(Developer* dev);

    void addVersion(const Version& ver);

    virtual void printTableRow(std::ostream& os) const;
};
