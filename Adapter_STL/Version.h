#pragma once


#include <string>
#include <iostream>

class Version {
private:
    std::string number;
    std::string releaseDate;
    double sizeMb;

public:
    Version();
    Version(const std::string& number, const std::string& releaseDate, double sizeMb);

    std::string getNumber() const;
    std::string getReleaseDate() const;
    double getSizeMb() const;

    void print(std::ostream& os) const;
};

