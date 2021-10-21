#include "IGetValue.hpp"

template<class T>
T IGetValue<T>::getLastValue() {
    return _value;
}
