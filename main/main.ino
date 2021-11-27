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

const int LED_PIN = LED_BUILTIN; 

ISwitchBase *pSwitch;
HardwareDeviceFactory* pHardwareDeviceFactory;
WebWrapperTemplate *pWebWrapperTemplate;
SwitchWebWrapper *pSwitchWebWrapper;

SerialController *pSerialController;
MakeConcreteSerialAdapters *pMakeConcreteSerialAdapters;
WebController *pWebController = 0;

int get_rssi(String ssid) {
  int ret = -150;
  // set wifi mode
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  while (n) {
    if (ssid.equals(WiFi.SSID(--n))) {
      ret = WiFi.RSSI(n);
      break;
    }
  }
  return ret;
}

bool ap_run = 0;
int ap_run_time = 0;
const int time_limit = 30000;
int wifi_connection() {
  const char *ssid = "LocalWiFi";
  const char *password = "sdfbh342njsdf";
  const char *self_password = "password";
  const char *self_ssid = "test";

  if ((!ap_run && WiFi.status() == WL_CONNECTED) || (ap_run && (millis() - ap_run_time) <= time_limit))
    return 0;
  WiFi.disconnect();
  delay(500);

  int rssi = 0;
  rssi = get_rssi(ssid);
  if ((!ap_run || (millis() - ap_run_time) > time_limit) && rssi > -100) {
    ap_run = 0;
    ap_run_time = 0;
    WiFi.mode(WIFI_STA);
    WiFi.begin ( ssid, password );
    while ( WiFi.status() != WL_CONNECTED ) {
      delay ( 500 );
      Serial.print ( "." );
    }
  }
  else {
    WiFi.mode(WIFI_AP); //WIFI_AP (точка доступа), WIFI_STA (клиент), или WIFI_AP_STA (оба режима одновременно).
    //WiFi.mode(WIFI_AP_STA); 
    //WiFi.softAP(self_ssid, self_password);
    WiFi.begin ( ssid, password );
    ap_run = 1;
    ap_run_time = millis(); 
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
