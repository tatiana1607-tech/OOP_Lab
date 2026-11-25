#pragma once
#include "MobileApp.h"
using namespace std;
class EnterpriseApp : public MobileApp {
private:
    string clientCompanyName;
    string securityProtocol;

public:
    EnterpriseApp(const string& n = "Корп. Софт", double r = 0.0, double p = 0.0,
        Developer* dev = nullptr, const string& client = "Заказчик", const string& sec = "AES-256");

    string getClientCompanyName() const;
    string getSecurityProtocol() const;

    void setClientCompanyName(const string& client);
    void setSecurityProtocol(const string& sec);

    void printTableRow(ostream& os) const override;
};