//
// Created by Nikolai on 10.11.2021.
//

#ifndef ARDUINOPROJECT_ICONTAINER_HPP
#define ARDUINOPROJECT_ICONTAINER_HPP

template<class T, class U>
class IContainer{
protected:
    U* root = nullptr;
public:
    virtual T& operator[](int index) = 0;
    virtual U insert(T value, int position = -1) = 0;
    virtual void remove(int position) = 0;
    virtual int size() = 0;
    virtual void clear() = 0;
    virtual const U begin() = 0;
    virtual const U end() = 0;
};

#endif //ARDUINOPROJECT_ICONTAINER_HPP
