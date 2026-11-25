#pragma once
#include "MobileApp.h"
#include <string>

class EnterpriseApp : public MobileApp {
private:
    std::string clientCompany;
    std::string securityProtocol;

public:
    EnterpriseApp();
    EnterpriseApp(const std::string& name, double rating, double price, Developer* leadDeveloper,
        const std::string& clientCompany, const std::string& securityProtocol);

    std::string getClientCompany() const;
    std::string getSecurityProtocol() const;

    void printTableRow(std::ostream& os) const override;
};