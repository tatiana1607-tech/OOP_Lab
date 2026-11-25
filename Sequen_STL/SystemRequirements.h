#pragma once
#include <iostream>
#include <string>
using namespace std;
class SystemRequirements {
private:
    string osVersion;
    int minRAM_GB;
    double storageMB;

public:
    SystemRequirements();
    SystemRequirements(const string& os, int ram, double storage);

    string getOSVersion() const;
    int getMinRAM() const;
    double getStorageMB() const;

    void setOSVersion(const string& os);
    void setMinRAM(int ram);
    void setStorageMB(double storage);

    void display() const;
};