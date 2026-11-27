#pragma once
#include <string>


enum AppType {
    GAME_APP = 0,
    SOCIAL_APP = 1,
    FINANCE_APP = 2,
    EDUCATION_APP = 3,
    UTILITY_APP = 4
};

class AppSpec {
public:
    std::string name;
    double version;
    AppSpec(std::string n, double v) : name(n), version(v) {}
    virtual ~AppSpec() {}
    virtual AppType getType() const = 0;
};

class GameAppSpec : public AppSpec {
public:
    std::string genre;
    GameAppSpec(std::string n, double v, std::string g) : AppSpec(n, v), genre(g) {}
    AppType getType() const override { return GAME_APP; }
};

class SocialAppSpec : public AppSpec {
public:
    int maxGroupSize;
    SocialAppSpec(std::string n, double v, int m) : AppSpec(n, v), maxGroupSize(m) {}
    AppType getType() const override { return SOCIAL_APP; }
};

class FinanceAppSpec : public AppSpec {
public:
    std::string currency;
    FinanceAppSpec(std::string n, double v, std::string c) : AppSpec(n, v), currency(c) {}
    AppType getType() const override { return FINANCE_APP; }
};

class EducationAppSpec : public AppSpec {
public:
    std::string subject;
    EducationAppSpec(std::string n, double v, std::string s) : AppSpec(n, v), subject(s) {}
    AppType getType() const override { return EDUCATION_APP; }
};

class UtilityAppSpec : public AppSpec {
public:
    bool requiresRoot;
    UtilityAppSpec(std::string n, double v, bool r) : AppSpec(n, v), requiresRoot(r) {}
    AppType getType() const override { return UTILITY_APP; }
};
