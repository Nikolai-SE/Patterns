//
// Created by Nikolai on 11.11.2021.
//

#ifndef ARDUINOPROJECT_WEBCONTROLLER_HPP
#define ARDUINOPROJECT_WEBCONTROLLER_HPP


#include <IController.hpp>
#include <ESP8266WebServer.h>
//#define DEBUG
#ifdef DEBUG
#include "../SmartHomeMaintain/ISerialDevice.hpp"
#include "../SmartHomeMaintain/IDevice.hpp"
#include "IController.hpp"
#endif

class WebController : public IController {
protected:
    static WebController* webController;
    ESP8266WebServer* server = nullptr;
    int serverPort = 0;

    WebController(int serverPort) : serverPort(serverPort)
    {
        if(server != nullptr)
            delete server;
        server = new ESP8266WebServer(serverPort);
    }
public:
    WebController(WebController &other) = delete;
    void operator=(const WebController &) = delete;
    static WebController *GetInstance(const int serverPort);
    ~WebController()
    {
        delete server;
        webController = nullptr;
    }
    int process() override {
        server->handleClient();
        return 0;
    }
    ESP8266WebServer* getServer()
    {
        return server;
    }
    int getPort()
    {
        return webController->serverPort;
    };
};

WebController* WebController::webController= nullptr;

WebController* WebController::GetInstance(const int serverPort)
{
    if(webController == nullptr){
        webController = new WebController(serverPort);
    }
    return webController;
};

#endif //ARDUINOPROJECT_WEBCONTROLLER_HPP
