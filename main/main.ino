#include <ESP8266WiFi.h>
#include <Switch.hpp>
#include <List.hpp>
#include <SwitchWebWrapper.hpp>
#include <WebController.hpp>
#include <WebWrapperTemplate.hpp>

#include <MakeConcreteSerialAdapters.hpp>
#include <SerialController.hpp>
#include <WebController.hpp>

#include <HardwareDeviceFactory.hpp>

const int LED_PIN = LED_BUILTIN; // пин для демонстрации работы устройства

ISwitchBase *pSwitch = 0; // переключатель
HardwareDeviceFactory* pHardwareDeviceFactory = 0;
WebWrapperTemplate *pWebWrapperTemplate = 0;
SwitchWebWrapper *pSwitchWebWrapper = 0;

SerialController *pSerialController = 0;
MakeConcreteSerialAdapters *pMakeConcreteSerialAdapters;
WebController *pWebController = 0;

int getRssi(String ssid) {
  int rssi = -200;
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  int n = WiFi.scanNetworks();
  while (n--)
    if (ssid.equals(WiFi.SSID(n))) {
      rssi = WiFi.RSSI(n);
      break;
    }
  return rssi;
}

bool apIsRun = 0;
int apRunTime = 0;
const int time_limit = 30000;
int wifi_connection() { // проверяет подключение к сети
  // и переводит модуль в режим клиента
  // или точки доступа, если при плохом подключении
  // проверяет раз в time_limit миллисекунд
  
  const char *ssid = "LocalWiFi";
  const char *password = "sdfbh342njsdf";
  const char *self_password = "password";
  const char *self_ssid = "test";

  if ((!apIsRun && WiFi.status() == WL_CONNECTED) || (apIsRun && (millis() - apRunTime) <= time_limit))
    return 0;
  WiFi.disconnect();
  delay(500);

  int rssi = getRssi(ssid);
  if ((!apIsRun || (millis() - apRunTime) > time_limit) && rssi > -100) {
    apIsRun = 0;
    apRunTime = 0;
    WiFi.mode(WIFI_STA);
    WiFi.begin ( ssid, password );
    while ( WiFi.status() != WL_CONNECTED ) {
      delay ( 500 );
      Serial.print ( "." );
    }
  }
  else {
    WiFi.mode(WIFI_AP_STA); //WIFI_AP (точка доступа), WIFI_STA (клиент), или WIFI_AP_STA (оба режима одновременно).
    WiFi.softAP(self_ssid, self_password);
    WiFi.begin ( ssid, password );
    apIsRun = 1;
    apRunTime = millis(); 
  }
  delay(100);
  
  WiFi.printDiag(Serial);
  Serial.print ( "IP = " );
  Serial.println ( WiFi.localIP() );
  delay(100);
  pWebController = WebController::GetInstance(80);
  return 1;
};

void initDevices()
{
  // создаем на фабрике переключатель и присваиваем ему команды для того, чтобы он переключал физическое состояние пина
  List<void*> args;
  args.insert(new int(LED_PIN));
  args.insert(new int(0));
  pHardwareDeviceFactory = new HardwareDeviceFactory();
  pSwitch = pHardwareDeviceFactory->makeSwitch("switch", args);
  delete pHardwareDeviceFactory;
  
  // добавляем переключателю возможность создавать web представление по шаблону
  // Использованы мателриалы с сайта https://codepen.io/himalayasingh/pen/EdVzNL
  pWebWrapperTemplate = new WebWrapperTemplate("<div class = 'device' id='%s'>\
<div class='device_header'>%s\
<div class='toggle-button-cover'>\
<div class='button r' id='nice_button'>\
<input type='checkbox' class='checkbox' id='%s_state' onchange=\"send_request_to_Arduino('%s', 'state=' + ((this.checked)?'on':'off'))\">\
<div class='knobs'></div>\
<div class='layer'></div>\
</div>\
</div>\
</div>\
</div> \n");
  SwitchWebWrapper* pSwitchWebWrapper = new SwitchWebWrapper(pSwitch, pWebWrapperTemplate);
  pSwitchWebWrapper->setWebName("Выключатель");
  pSwitch = pSwitchWebWrapper;
  
  // инициализируем контреллер последоватьельного порта ввода вывода для управления устройствами через консоль
  pSerialController = new SerialController(&Serial);

  // добавляем контролерам устройство
  pMakeConcreteSerialAdapters = new MakeConcreteSerialAdapters();
  ISerialAdapter<IDevice>* ssa = &(pMakeConcreteSerialAdapters->makeSerialAdapter((IDevice*)pSwitch));
  pSerialController->addSerialDevice(ssa);
  pWebController->addSerialDevice(ssa);
  
  delete pMakeConcreteSerialAdapters;
}

void setup () {
  Serial.begin ( 115200 );
  Serial.println("\n SETUP ");
  wifi_connection();
  initDevices();
  Serial.println(" START ");  
  delay(50);
}

void loop () {
  wifi_connection();
  pSerialController->process();
  pWebController->process();
  delay(5);
}
