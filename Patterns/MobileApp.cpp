#include "MobileApp.h"

std::vector<std::pair<int, AppFactoryFunc>> MobileApp::registry;

void MobileApp::registerType(AppFactoryFunc func) {
    int id = static_cast<int>(registry.size());
    registry.push_back(std::make_pair(id, func));
}

std::unique_ptr<MobileApp> MobileApp::createFromRegistry(int id) {
    if (id < 0 || id >= static_cast<int>(registry.size())) {
        return nullptr;
    }
   
    return std::unique_ptr<MobileApp>(registry[id].second());
}


void MobileApp::edit() {
    std::cout << "Введите новое название приложения: ";
    std::getline(std::cin >> std::ws, name);
    std::cout << "Введите новую версию (например, 1.2): ";
    std::cin >> version;
}

void MobileApp::print(std::ostream& out) const {
    std::unique_ptr<AppModule> mod(createModule()); 
    out << std::left
        << "| " << std::setw(12) << getCategory()
        << "| " << std::setw(18) << name
        << "| " << std::setw(7) << version
        << "| " << std::setw(46) << mod->getModuleInfo()
        << "| ";
}


void GameApp::print(std::ostream& out) const {
    MobileApp::print(out);
    out << std::left << std::setw(24) << ("Жанр: " + genre) << "|\n";
}

void SocialApp::print(std::ostream& out) const {
    MobileApp::print(out);
    out << std::left << std::setw(24) << ("Макс. группа: " + std::to_string(maxGroupSize)) << "|\n";
}

void FinanceApp::print(std::ostream& out) const {
    MobileApp::print(out);
    out << std::left << std::setw(24) << ("Валюта: " + currency) << "|\n";
}

void EducationApp::print(std::ostream& out) const {
    MobileApp::print(out);
    out << std::left << std::setw(24) << ("Предмет: " + subject) << "|\n";
}

void UtilityApp::print(std::ostream& out) const {
    MobileApp::print(out);
    std::string rootText = requiresRoot ? "Да" : "Нет";
    out << std::left << std::setw(24) << ("Root-права: " + rootText) << "|\n";
}


void GameApp::edit() {
    MobileApp::edit();
    std::cout << "Введите жанр игры: ";
    std::getline(std::cin >> std::ws, genre);
}

void GameApp::saveToFile(std::ofstream& out) const {
    out << GAME_APP << ";" << name << ";" << version << ";" << genre << "\n";
}


void SocialApp::edit() {
    MobileApp::edit();
    std::cout << "Введите макс. размер группы: ";
    std::cin >> maxGroupSize;
}

void SocialApp::saveToFile(std::ofstream& out) const {
    out << SOCIAL_APP << ";" << name << ";" << version << ";" << maxGroupSize << "\n";
}


void FinanceApp::edit() {
    MobileApp::edit();
    std::cout << "Введите основную валюту (BYN, USD, EUR): ";
    std::cin >> currency;
}

void FinanceApp::saveToFile(std::ofstream& out) const {
    out << FINANCE_APP << ";" << name << ";" << version << ";" << currency << "\n";
}

void EducationApp::edit() {
    MobileApp::edit();
    std::cout << "Введите предмет обучения: ";
    std::getline(std::cin >> std::ws, subject);
}

void EducationApp::saveToFile(std::ofstream& out) const {
    out << EDUCATION_APP << ";" << name << ";" << version << ";" << subject << "\n";
}


void UtilityApp::edit() {
    MobileApp::edit();
    std::cout << "Требуются ли Root-права (1 - да, 0 - нет): ";
    std::cin >> requiresRoot;
}

void UtilityApp::saveToFile(std::ofstream& out) const {
    out << UTILITY_APP << ";" << name << ";" << version << ";" << requiresRoot << "\n";
}


std::unique_ptr<MobileApp> makeAppSimple(AppType type) {
    switch (type) {
    case GAME_APP:      return std::make_unique<GameApp>();
    case SOCIAL_APP:    return std::make_unique<SocialApp>();
    case FINANCE_APP:   return std::make_unique<FinanceApp>();
    case EDUCATION_APP: return std::make_unique<EducationApp>();
    case UTILITY_APP:   return std::make_unique<UtilityApp>();
    default:            return nullptr;
    }
}


std::unique_ptr<MobileApp> makeAppWithArgs(const AppSpec* spec) {
    if (!spec) return nullptr;
    switch (spec->getType()) {
    case GAME_APP:      return std::make_unique<GameApp>(static_cast<const GameAppSpec*>(spec));
    case SOCIAL_APP:    return std::make_unique<SocialApp>(static_cast<const SocialAppSpec*>(spec));
    case FINANCE_APP:   return std::make_unique<FinanceApp>(static_cast<const FinanceAppSpec*>(spec));
    case EDUCATION_APP: return std::make_unique<EducationApp>(static_cast<const EducationAppSpec*>(spec));
    case UTILITY_APP:   return std::make_unique<UtilityApp>(static_cast<const UtilityAppSpec*>(spec));
    default:            return nullptr;
    }
}
