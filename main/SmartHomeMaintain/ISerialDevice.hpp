//
// Created by Nikolai on 26.10.2021.
//

#ifndef ARDUINOPROJECT_ISERIALDEVICE_HPP
#define ARDUINOPROJECT_ISERIALDEVICE_HPP


class ISerialDevice {
protected:
    String _name;
public:
    ISerialDevice(String name)
    {
        _name = name;
    };
    String getName(){
        return _name;
    }
    virtual String get(String key) = 0;
    virtual void set(String key, String value) = 0;
};


#endif //ARDUINOPROJECT_ISERIALDEVICE_HPP
