//
// Created by Nikolai on 10.11.2021.
//

#ifndef ARDUINOPROJECT_LIST_HPP
#define ARDUINOPROJECT_LIST_HPP

#include "IContainer.hpp"
#include "ListIterator.hpp"

template<class U>
class List : public IContainer<U, ListIterator<U>> {
private:
    void lazyInit() {
        if (this->root == nullptr)
            this->root = new ListIterator<U>();
    }

public:
    List() {
        lazyInit();
    }

    U &operator[](int index) override {
        ListIterator<U> *it = this->root;
        while (index--)
            it = it->_next;
        return **it;
    }

    ListIterator<U> insert(U value, int position = -1) override {
        lazyInit();
        if (position == -1)
            position = this->size();

        ListIterator<U> *it = this->root;
        if (position == 0) {
            this->root = new ListIterator<U>(value);
            this->root->_next = it;
            return *this->root;
        }

        while (--position)
            it = it->_next;
        ListIterator<U> *pNext = it->_next;
        it->_next = new ListIterator<U>(value);
        it->_next->_next = pNext;
        return *it->_next;
    }

    void remove(int position) override {
        ListIterator<U> *it;
        if (position == 0) {
            it = (ListIterator<U> *) this->root->_next;
            delete this->root;
            this->root = it;
        } else {
            ListIterator<U> *prev = this->root;
            int pos = position - 1;
            while (pos--) {
                prev = (ListIterator<U> *) prev->_next;
            }
            it = (ListIterator<U> *) prev->_next;
            prev->_next = prev->_next->_next;
            delete it;
        }
    }

    int size() override {
        ListIterator<U> *it = this->root;
        int size = 0;
        while (it->hasNext()) {
            size++;
            it = it->_next;
        }
        return size;
    }

    void clear() override {
        ListIterator<U> *it = this->root;
        while (this->root != nullptr) {
            remove(0);
        }
    }

    ListIterator<U> begin() override {
        ListIterator<U> it(*this->root);
        return it;
    }

    const ListIterator<U> end() override {
        ListIterator<U> *it = this->root;
        while (it->hasNext())
            it = it->_next;
        return *it;
    }
};


#endif //ARDUINOPROJECT_LIST_HPP
