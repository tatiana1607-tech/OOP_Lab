#include "EnterpriseApp.h"
#include <iomanip>

using namespace std;

EnterpriseApp::EnterpriseApp()
    : MobileApp(), clientCompany("Не указан"), securityProtocol("TLS 1.3") {
}

EnterpriseApp::EnterpriseApp(const string& name, double rating, double price, Developer* leadDeveloper,
    const string& clientCompany, const string& securityProtocol)
    : MobileApp(name, rating, price, leadDeveloper),
    clientCompany(clientCompany),
    securityProtocol(securityProtocol) {
}

string EnterpriseApp::getClientCompany() const {
    return clientCompany;
}

string EnterpriseApp::getSecurityProtocol() const {
    return securityProtocol;
}

void EnterpriseApp::printTableRow(ostream& os) const {
    MobileApp::printTableRow(os);
    os << "   [B2B Корпор.] Заказчик: " << clientCompany
        << ", Безопасность: " << securityProtocol << "\n";
}