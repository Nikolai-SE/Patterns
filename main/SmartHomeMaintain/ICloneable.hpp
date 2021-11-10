//
// Created by Nikolai on 10.11.2021.
//

#ifndef ARDUINOPROJECT_ICLONEABLE_HPP
#define ARDUINOPROJECT_ICLONEABLE_HPP


class ICloneable {
public:
    virtual ICloneable* clone() = 0;
};


#endif //ARDUINOPROJECT_ICLONEABLE_HPP
