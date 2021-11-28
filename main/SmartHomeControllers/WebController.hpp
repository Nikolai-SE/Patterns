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
#include "../SmartHomeTools/ListIterator.hpp"
#include "IController.hpp"
#endif

void fun_handleRoot();
void fun_handleLogs();
void fun_handleData();
void fun_handleNotFound();

class WebController : public IController {
protected:
    static WebController* webController;
    ESP8266WebServer* server = nullptr;
    int serverPort = 0;
    static char* javaScript;
    static char* style;
    static char* homePageStart;
    static char* bodyStart;
    static char* bodyEnd;
    static char* homePageEnd;

    void _handleRoot()
    {
        String webpage;
        webpage += homePageStart; webpage += style; webpage += bodyStart;
        int l = listOfSerialDevices.size();
        for(int i = 0; i < l; i++)
        {
            webpage += listOfSerialDevices[i]->get("webpage");
        }
        webpage += bodyEnd; webpage += javaScript; webpage += homePageEnd;
        server->send ( 200, "text/html", webpage );
    }

    void _handleData()
    {
        noInterrupts();
        if (server->argName(0) == "device") {
            int deviceIndex = findDeviceIndex(server->arg(0));
            if (deviceIndex == -1) {
                interrupts();
                server->send(404, "text/html", "\'\"result\"=\"device '" + server->arg(0) + "' didn't found\"");
                return;
            }
            ISerialDevice *serialDevice = listOfSerialDevices[deviceIndex];

            String json = "{";
            for (int i = 1; i < server->args() - 1; i++) {
                if (server->argName(i) == "get") {
                    json += '"' + server->arg(i) + '"' + ':' + '"' + serialDevice->get(server->arg(i))  + '"';
                }
                else
                {
                    serialDevice->set(server->argName(i), server->arg(i));
                    json += '"' + server->argName(i) + '"' + ':' + '"' + serialDevice->get(server->argName(i)) + '"';
                }
                if(i < server->args() - 2)
                    json += ',';
            }
            json += "}";
            server->send(200, "text/html", json);
        }
        else
        {
            server->send(200, "text/html", "not identified");
        }
        interrupts();
    }

    void _sendLogs()
    {
        server->send ( 200, "text/plain", " logs \0" );
    }

    void _handleNotFound()
    {
        String message = "File Not Found\n\n";
        message += "URI: ";
        message += server->uri();
        message += "\nMethod: ";
        message += ( server->method() == HTTP_GET ) ? "GET" : "POST";
        message += "\nArguments: ";
        message += server->args();
        message += "\n";
        for ( uint8_t i = 0; i < server->args(); i++ ) {
            message += " " + server->argName ( i ) + ": " + server->arg ( i ) + "\n";
        }
        webController->server->send ( 404, "text/plain", message );
    }

    WebController(int serverPort) : serverPort(serverPort) {
        if (server != nullptr)
            delete server;
        server = new ESP8266WebServer(serverPort);
        this->begin();
    }

    void begin()
    {
        server->on("/", fun_handleRoot );
        server->on ( "/data/", fun_handleData);
        server->on ( "/logs/", fun_handleLogs);
        server->onNotFound( fun_handleNotFound );
        server->begin();
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
    static int getPort()
    {
        return webController->serverPort;
    };

    static void handleRoot()
    {
        webController->_handleRoot();
    }
    static void handleData()
    {
        webController->_handleData();
    }
    static void handleLogs()
    {
        webController->_sendLogs();
    }
    static void handleNotFound()
    {
        webController->_handleNotFound();
    }
};

WebController* WebController::webController= nullptr;

WebController* WebController::GetInstance(const int serverPort)
{
    if(webController == nullptr){
        webController = new WebController(serverPort);
    }
    return webController;
};


void fun_handleRoot()
{
    WebController::handleRoot();
};
void fun_handleData()
{
    WebController::handleData();
};
void fun_handleLogs()
{
    WebController::handleLogs();
};
void fun_handleNotFound()
{
    WebController::handleNotFound();
};

char* WebController::homePageStart = "<!DOCTYPE html> <html> <head> <title>Умный дом</title> <meta charset='utf-8'>\0";

// Использованы мателриалы с сайта https://codepen.io/himalayasingh/pen/EdVzNL
char* WebController::style = "<style> *{ user-select: none; -webkit-tap-highlight-color:transparent; } div.device { display: block; position: relative; background: #559BC0 ; width: 23%; min-width: 200pt; border-width: 30pt; border-color: #84290E; border-radius: 5pt; margin: 20pt; padding: 10pt; align-content: right; }"
                           " @media screen and (max-width: 150em) { header{font-size: 300%;} div.device {width: 80%; font-size: 180%;} input{font-size: 80%;}} html { background: #72A4C0; text-decoration-color: #0B3A54; color: black; font-size: 140%; font-family: monospace; font-style: oblique; }"
                           " header{ font-size: 210%; text-align: center; font-style: bold; } .toggle-button-cover { display: table-cell; position: absolute; right: 10px; top: 18px; width: 74px; height: 16px; box-sizing: border-box; } .button-cover, .knobs, .layer { position: absolute; top: 0; right: 0; bottom: 0; left: 0; }"
                           " .button { position: relative; top: 50%; width: 74px; height: 36px; margin: -20px auto 0 auto; overflow: hidden; } .button.r, .button.r .layer { border-radius: 100px; } .button.b2 { border-radius: 2px; } .checkbox { position: relative; width: 100%; height: 100%; padding: 0; margin: 0; opacity: 0; cursor: pointer; z-index: 3; } .knobs { z-index: 2; } .layer { width: 100%; background-color: #ebf7fc; transition: 0.3s ease all; z-index: 1; } #nice_button .knobs:before { content: 'OFF'; position: absolute; top: 4px; left: 4px; width: 20px; height: 10px; color: #fff; font-size: 10px; font-weight: bold; text-align: center; line-height: 1; padding: 9px 4px; background-color: #03A9F4; border-radius: 50%; transition: 0.3s cubic-bezier(0.18, 0.89, 0.35, 1.15) all; } #nice_button .checkbox:checked + .knobs:before { content: 'ON'; left: 42px; background-color: #f44336; } #nice_button .checkbox:checked ~ .layer { background-color: #fcebeb; } #nice_button .knobs, #nice_button .knobs:before, #nice_button .layer { transition: 0.3s ease all; } </style>\0";
char* WebController::javaScript = "<script type='text/javascript'> function $(x) {return document.getElementById(x);}"
                                  " var url = document.location.href;url += 'data/';console.log(url);"
                                  " function send_request_to_Arduino(name, param)"
                                  "{ var request = new XMLHttpRequest();"
                                      " var params = 'device=' + name + '&' + param; "
                                      " request.timeout = 1500; request.responseType = 'text';"
                                      " request.open('POST', url , true);"
                                      " request.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');"
                                      " request.addEventListener('readystatechange',"
                                          " () => { if (request.readyState == 4 && request.status == 200)"
                                          " { var obj = request.response;"
                                          " console.log(url, params, ' result = ', obj);"
                                          " var res = JSON.parse(obj);"
                                          " try{ $(name + '_value').value = res.value;}"
                                          "     catch(e){console.log(e);};"
                                          " try{ $(name + '_state').checked = (res.state == '1');}"
                                          "     catch(e){console.log(e);};"
                                          " return res; } }"
                                          ");"
                                  " request.send(params);"
                                  " console.log(params, ' sended to server -- ', request.statusText);"
                                  " }"
                                  " function update(){ "
                                  "     send_request_to_Arduino('switch', 'get=state');"
                                  " }"
                                  " setInterval(update, 5000); update(); </script>\0";
char* WebController::bodyStart = "</head> <body> <header>Умный дом</header> <main>\0";
char* WebController::bodyEnd = "</main> </body>\0";
char* WebController::homePageEnd = "</html>\0";

#endif //ARDUINOPROJECT_WEBCONTROLLER_HPP
