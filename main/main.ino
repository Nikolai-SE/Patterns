#include <ESP8266WiFi.h>

#include <Switch.hpp>
#include <SetDigitalPinValue.hpp>

#include <SwitchLogger.hpp>
#include <SwitchWebWrapper.hpp>
#include <SwitchBlynkWrapper.hpp>
#include <SwitchComposite.hpp>
#include <SwitchSerialAdapter.hpp>
#include <SerialController.hpp>
#include <WebWrapperTemplate.hpp>

const int LED_PIN = LED_BUILTIN; 

SetDigitalPinValue *pSwitchSetPin;

Switch *pSwitch;
SwitchLogger *pSwitchLogger;

WebWrapperTemplate *pWebWrapperTemplate;
SwitchWebWrapper *pSwitchWebWrapper;

SwitchBlynkWrapper *pSwitchBlynkWrapper;
SwitchComposite *pSwitchComposite;

SerialController *pSerialController;

SwitchSerialAdapter * pSwitchSerialAdapter;

void setup () {
  Serial.begin ( 115200 );
  Serial.println("\n SETUP ");
 
  pSwitchSetPin = new SetDigitalPinValue(LED_PIN); 
  
  pSwitch = new Switch("originalSwitch");
  pSwitch->setISetValue( pSwitchSetPin );

  pWebWrapperTemplate = new WebWrapperTemplate("<div class = 'switch' id='%s'>\
<div class='device_header'>%s\
<div class='toggle-button-cover'>\
<div class='button r' id='nice_button'>\
<input type='checkbox' class='checkbox' id='%s_checkbox' onchange=\"send_request_to_Arduino('%s', 'state=' + ((this.checked)?'on':'off'))\">\
<div class='knobs'></div>\
<div class='layer'></div>\
</div>\
</div>\
</div>\
</div> \n");
  pSwitchWebWrapper = new SwitchWebWrapper(pSwitch, pWebWrapperTemplate);
  pSwitchWebWrapper->setWebName("WebName");
  
  
  pSwitchLogger = new SwitchLogger("switchLogger1", pSwitchWebWrapper);
  pSwitchLogger->setSerial(&Serial);

  pSwitchBlynkWrapper = new SwitchBlynkWrapper(pSwitchLogger);
  
  pSwitchComposite = new SwitchComposite("switchComposite");
  pSwitchComposite->addSwitch(pSwitch);
  pSwitchComposite->addSwitch(pSwitchLogger);
  pSwitchComposite->addSwitch(pSwitchWebWrapper);
  pSwitchComposite->addSwitch(pSwitchBlynkWrapper);
  
  pSwitchSerialAdapter = new SwitchSerialAdapter("adapter", pSwitchWebWrapper);
  
  pSerialController = new SerialController(&Serial);
  pSerialController->addSerialDevice(pSwitchSerialAdapter);

  Serial.println(" START ");
  delay(50);
}

void serialEvent() {

    if (Serial && Serial.available()) {
    // Чтение данных из порта Serial3
    char in_char = Serial.read();
    if(in_char == '0')
    {
        pSwitchComposite->turnOff();
    }
    else
    if(in_char == '1')
    {
        pSwitchComposite->turnOn();
    }
    else
    if(in_char == 'w')
    {
        Serial.println(pSwitchComposite->makeWebPage());
    }
    else
    if(in_char == 'a')
    {
        in_char = Serial.read();
        String inp = Serial.readStringUntil('\n');
        Serial.println("The whole input: " + inp);
        if (in_char == '?')
        {
          Serial.println(pSwitchSerialAdapter->get(inp));
        }
        else if (in_char == ':')
        {
          String inpVal = inp.substring(inp.indexOf('=') + 1);
          inp = inp.substring(0, inp.indexOf('='));
          pSwitchSerialAdapter->set(inp, inpVal);
        }
        else
        {
          Serial.println("ERROR input mode char: "); 
          Serial.println( "\\" + int(in_char)); 
        }
    }    
  }
}

void loop () {
  //serialEvent();
  pSerialController->process();
  //Serial.println(pSwitchWebWrapper->make
  delay(50);
}
