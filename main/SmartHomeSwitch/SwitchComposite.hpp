//
// Created by Nikolai on 21.10.2021.
//

#ifndef ARDUINOPROJECT_SWITCHCOMPOSITE_HPP
#define ARDUINOPROJECT_SWITCHCOMPOSITE_HPP

//#include "../SmartHomeMaintain/ISwitchBase.hpp"
#include "ISwitchBase.hpp"

class SwitchComposite : public ISwitchBase {
protected:
    const static int maxSize = 20;
    int size = 0;
    ISwitchBase* listOfSwitches[maxSize];
public:
    SwitchComposite(String name) : ISwitchBase(name){
    };
    int addSwitch(ISwitchBase *switchBase)
    {
        if(size < maxSize){
            listOfSwitches[size++] = switchBase;
            return 0;
        }
        return 1;
    }
    int delSwitch(int number)
    {
        if(number < size){
            for(int i = number; i < size - 1; i++)
            {
                listOfSwitches[i] = listOfSwitches[i+1];
            }
            listOfSwitches[size--] = 0;
            return 0;
        }
        return 1;
    }
    ISwitchBase* getSwitch(int number)
    {
        if(number < size){
            return listOfSwitches[number];
        }
        return 0;
    }
    bool state() override
    {
        int c = 0;
        for(int i = 0; i < size; i++)
        {
            if(listOfSwitches[i]->state())
                c++;
            else
                c--;
        }
        return c > 0;
    };
    void turnOn() override
    {
        for(int i = 0; i < size; i++) {
            listOfSwitches[i]->turnOn();
        }
    };
    void turnOff() override
    {
        for(int i = 0; i < size; i++) {
            listOfSwitches[i]->turnOff();
        }
    };
    String makeWebPage() override
    {
        String webPage = "<div id = '";
        webPage += _name + "'>";
        for(int i = 0; i < size; i++) {
            webPage += "\n*********";
            webPage += listOfSwitches[i]->makeWebPage();
        }
        webPage += "</div>";
        return webPage;
    };
};


#endif //ARDUINOPROJECT_SWITCHCOMPOSITE_HPP
