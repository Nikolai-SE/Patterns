//
// Created by Nikolai on 21.10.2021.
//

#ifndef ARDUINOPROJECT_ISERIALADAPTER_HPP
#define ARDUINOPROJECT_ISERIALADAPTER_HPP

template <class T>
class ISerialAdapter {
protected:
    String _name;
    T* device;
public:
    ISerialAdapter(String name, T* device)
    {
        this->device = device;
        _name = name;
    };
    virtual String get(String key) = 0;
    virtual void set(String key, String value) = 0;
    String getName(){
        return _name;
    }
};


#endif //ARDUINOPROJECT_ISERIALADAPTER_HPP
