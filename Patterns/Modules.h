#pragma once
#include <string>


class AppModule {
public:
    virtual ~AppModule() {}
    virtual std::string getModuleInfo() const = 0;
};


class GameEngineModule : public AppModule {
public:
    std::string getModuleInfo() const override { return "3D-движок и физика (Unity/Unreal)"; }
};

class MessengerModule : public AppModule {
public:
    std::string getModuleInfo() const override { return "Модуль чатов и push-уведомлений (WebSocket)"; }
};

class PaymentGatewayModule : public AppModule {
public:
    std::string getModuleInfo() const override { return "Шлюз эквайринга и шифрования транзакций"; }
};

class TestingModule : public AppModule {
public:
    std::string getModuleInfo() const override { return "Модуль интерактивных тестов и прогресса"; }
};

class SystemApiModule : public AppModule {
public:
    std::string getModuleInfo() const override { return "Модуль доступа к датчикам и файловой системе"; }
};

