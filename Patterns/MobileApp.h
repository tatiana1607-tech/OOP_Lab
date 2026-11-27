#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include<iomanip>
#include <memory>
#include "Modules.h"
#include "AppSpecs.h"

class MobileApp;


typedef MobileApp* (*AppFactoryFunc)();


class MobileApp {
protected:
    std::string name;
    double version;

public:
    MobileApp(std::string n = "Без названия", double v = 1.0) : name(n), version(v) {}
    virtual ~MobileApp() {}

    virtual void edit();
    virtual void print(std::ostream& out) const;
    virtual void saveToFile(std::ofstream& out) const = 0;
    virtual std::string getCategory() const = 0;

    
    virtual AppModule* createModule() const = 0;

    virtual MobileApp* clone() const = 0;
    std::unique_ptr<MobileApp> cloneUnique() const {
        return std::unique_ptr<MobileApp>(clone());
    }

    static std::vector<std::pair<int, AppFactoryFunc>> registry;
    static void registerType(AppFactoryFunc func);
    static std::unique_ptr<MobileApp> createFromRegistry(int id);
};


class GameApp : public MobileApp {
private:
    std::string genre;
public:
    GameApp(std::string n = "CyberRunner", double v = 1.0, std::string g = "Аркада")
        : MobileApp(n, v), genre(g) {
    }
    GameApp(const GameAppSpec* spec)
        : MobileApp(spec->name, spec->version), genre(spec->genre) {
    }

    std::string getCategory() const override { return "Игра"; }
    void edit() override;
    void print(std::ostream& out) const override;
    void saveToFile(std::ofstream& out) const override;

    GameEngineModule* createModule() const override { return new GameEngineModule(); }
    GameApp* clone() const override { return new GameApp(*this); }

    static MobileApp* makeApp() { return new GameApp(); }
    static void Register() { registerType(GameApp::makeApp); }
};

class SocialApp : public MobileApp {
private:
    int maxGroupSize;
public:
    SocialApp(std::string n = "QuickChat", double v = 2.1, int m = 500)
        : MobileApp(n, v), maxGroupSize(m) {
    }
    SocialApp(const SocialAppSpec* spec)
        : MobileApp(spec->name, spec->version), maxGroupSize(spec->maxGroupSize) {
    }

    std::string getCategory() const override { return "Соцсеть"; }
    void edit() override;
    void print(std::ostream& out) const override;
    void saveToFile(std::ofstream& out) const override;

    MessengerModule* createModule() const override { return new MessengerModule(); }
    SocialApp* clone() const override { return new SocialApp(*this); }

    static MobileApp* makeApp() { return new SocialApp(); }
    static void Register() { registerType(SocialApp::makeApp); }
};

class FinanceApp : public MobileApp {
private:
    std::string currency;
public:
    FinanceApp(std::string n = "EasyPay", double v = 3.0, std::string c = "BYN")
        : MobileApp(n, v), currency(c) {
    }
    FinanceApp(const FinanceAppSpec* spec)
        : MobileApp(spec->name, spec->version), currency(spec->currency) {
    }

    std::string getCategory() const override { return "Финансы"; }
    void edit() override;
    void print(std::ostream& out) const override;
    void saveToFile(std::ofstream& out) const override;

    PaymentGatewayModule* createModule() const override { return new PaymentGatewayModule(); }
    FinanceApp* clone() const override { return new FinanceApp(*this); }

    static MobileApp* makeApp() { return new FinanceApp(); }
    static void Register() { registerType(FinanceApp::makeApp); }
};

class EducationApp : public MobileApp {
private:
    std::string subject;
public:
    EducationApp(std::string n = "CodeLearn", double v = 1.5, std::string s = "C++")
        : MobileApp(n, v), subject(s) {
    }
    EducationApp(const EducationAppSpec* spec)
        : MobileApp(spec->name, spec->version), subject(spec->subject) {
    }

    std::string getCategory() const override { return "Образование"; }
    void edit() override;
    void print(std::ostream& out) const override;
    void saveToFile(std::ofstream& out) const override;

    TestingModule* createModule() const override { return new TestingModule(); }
    EducationApp* clone() const override { return new EducationApp(*this); }

    static MobileApp* makeApp() { return new EducationApp(); }
    static void Register() { registerType(EducationApp::makeApp); }
};

class UtilityApp : public MobileApp {
private:
    bool requiresRoot;
public:
    UtilityApp(std::string n = "FileCleaner", double v = 1.2, bool r = false)
        : MobileApp(n, v), requiresRoot(r) {
    }
    UtilityApp(const UtilityAppSpec* spec)
        : MobileApp(spec->name, spec->version), requiresRoot(spec->requiresRoot) {
    }

    std::string getCategory() const override { return "Утилита"; }
    void edit() override;
    void print(std::ostream& out) const override;
    void saveToFile(std::ofstream& out) const override;

    SystemApiModule* createModule() const override { return new SystemApiModule(); }
    UtilityApp* clone() const override { return new UtilityApp(*this); }

    static MobileApp* makeApp() { return new UtilityApp(); }
    static void Register() { registerType(UtilityApp::makeApp); }
};


std::unique_ptr<MobileApp> makeAppSimple(AppType type);

std::unique_ptr<MobileApp> makeAppWithArgs(const AppSpec* spec);
