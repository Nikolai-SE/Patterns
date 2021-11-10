//
// Created by Nikolai on 06.11.2021.
//

#ifndef ARDUINOPROJECT_IITERATOR_HPP
#define ARDUINOPROJECT_IITERATOR_HPP

template<class T>
class IIterator {
public:
    virtual bool hasNext() = 0;
    virtual T& operator*() = 0;
};

#endif //ARDUINOPROJECT_IITERATOR_HPP
