#include <ESP8266WiFi.h>

#include <Switch.hpp>
#include <SetDigitalPinValue.hpp>

#include <SetDigitalPinValueFlyweight.hpp>

#include <SwitchLogger.hpp>
#include <SwitchWebWrapper.hpp>
#include <SwitchBlynkWrapper.hpp>
#include <SwitchComposite.hpp>
#include <SwitchSerialAdapter.hpp>
#include <SerialController.hpp>

const int LED_PIN = LED_BUILTIN; 

SetDigitalPinValue *pSwitchSetPin;
SetDigitalPinValueFlyweight *pSetDigitalPinValueFlyweight;

Switch *pSwitch;
SwitchLogger *pSwitchLogger;
SwitchWebWrapper *pSwitchWebWrapper;
SwitchBlynkWrapper *pSwitchBlynkWrapper;
SwitchComposite *pSwitchComposite;

SerialController *pSerialController;

SwitchSerialAdapter * pSwitchSerialAdapter;

void setup () {
  Serial.begin ( 115200 );
  Serial.println("\n SETUP ");
 
  pSwitchSetPin = new SetDigitalPinValue(LED_PIN); 
  pSetDigitalPinValueFlyweight = new SetDigitalPinValueFlyweight(LED_PIN, pSwitchSetPin);
  
  pSwitch = new Switch("originalSwitch");
  pSwitch->setISetValue( pSetDigitalPinValueFlyweight );
  
  
  pSwitchWebWrapper = new SwitchWebWrapper(pSwitch);
  
  pSwitchLogger = new SwitchLogger("switchLogger1", pSwitchWebWrapper);
  pSwitchLogger->setSerial(&Serial);

  pSwitchBlynkWrapper = new SwitchBlynkWrapper(pSwitchLogger);
  
  pSwitchComposite = new SwitchComposite("switchComposite");
  pSwitchComposite->addSwitch(pSwitch);
  pSwitchComposite->addSwitch(pSwitchLogger);
  pSwitchComposite->addSwitch(pSwitchWebWrapper);
  pSwitchComposite->addSwitch(pSwitchBlynkWrapper);
  
  pSwitchSerialAdapter = new SwitchSerialAdapter("adapter", pSwitch);

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
  delay(50);
}
