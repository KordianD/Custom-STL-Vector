#ifndef VECTOR_TEMPLATE_VECTOR_H
#define VECTOR_TEMPLATE_VECTOR_H

#include "Iterator.h"

template<typename DT>
class Vector {
private:
    DT *tab;
    int sizeVector;
    int capacityVector;
public:
    Vector() : tab(nullptr), sizeVector(), capacityVector() {}
    explicit Vector(int size);
    Vector(const std::initializer_list<DT> &v);
    Vector(const Vector<DT> &v);
    Vector(Vector<DT> &&v);

    Vector &operator=(const Vector<DT> &v);
    Vector &operator=(Vector<DT> &&v);

    ~Vector();

    bool operator==(const Vector<DT> &v);
    bool operator!=(const Vector<DT> &v);

    int capacity();
    int size();

    void push_back(DT &v);

    void pop_back();

    void swap(Vector &other);

    DT & front();
    const DT & front() const;

    const DT & back() const;
    DT & back();

    DT &operator[](int size);
    const DT &operator[](int size) const;

    void assign(int count, const DT &value);

    void resize(int count);

    friend class Iterator<DT>;
    typedef class Iterator<DT> iterator;

    // iterator erase(iterator pos );
    // iterator erase(const_iterator pos);
    // iterator erase(iterator first, iterator last);
    // iterator erase(const_iterator first, const_iterator last);

    // iterator insert( iterator pos, const T& value );
    // iterator insert( const_iterator pos, const T& value );
    // iterator insert( const_iterator pos, T&& value );
    // void insert( iterator pos, size_type count, const T& value );
    // iterator insert( const_iterator pos, size_type count, const T& value );


     iterator end();
     iterator begin();

};

template<typename DT>
Vector<DT>::Vector(int size) : sizeVector(size), capacityVector(size) {
    tab = new DT[sizeVector];
}

template<typename DT>
Vector<DT>::Vector(const std::initializer_list<DT> &v) : sizeVector(v.size()), capacityVector(v.size()) {
    tab = new DT[v.size()];

    for (int i = 0; i < v.size(); i++)
        tab[i] = *(v.begin() + i);
}

template<typename DT>
Vector<DT>::Vector(const Vector<DT> &v) : sizeVector(v.sizeVector), capacityVector(v.capacityVector) {
    tab = new DT[capacityVector];

    for (int i = 0; i < sizeVector; i++)
        tab[i] = v.tab[i];
}

template<typename DT>
Vector<DT>::Vector(Vector<DT> &&v) : sizeVector(v.sizeVector), capacityVector(v.capacityVector) {
    tab = v.tab;
    v.tab = nullptr;
    v.sizeVector = 0;
    v.capacityVector = 0;
}

template<typename DT>
Vector<DT> &Vector<DT>::operator=(const Vector<DT> &v) {
    if (this == &v)
        return *this;

    delete[] tab;
    sizeVector = v.sizeVector;
    capacityVector = v.capacityVector;
    tab = new DT[capacityVector];

    for (int i = 0; i < capacityVector; i++)
        tab[i] = v.tab[i];
}

template<typename DT>
Vector<DT> &Vector<DT>::operator=(Vector<DT> &&v) {
    if (this == &v)
        return *this;

    delete[] tab;
    sizeVector = v.sizeVector;
    capacityVector = v.capacityVector;
    tab = v.tab;
    v.sizeVector = 0;
    v.capacity = 0;
    v.tab = nullptr;

    return *this;
}

template<typename DT>
Vector<DT>::~Vector() {
    delete[] tab;
}

template<typename DT>
bool Vector<DT>::operator==(const Vector<DT> &v) {
    if (sizeVector == v.sizeVector && capacityVector == v.capacityVector) {
        for (int i = 0; i < sizeVector; i++)
            if (tab[i] != v.tab[i])
                return false;
        return true;
    }
    return false;

}

template<typename DT>
bool Vector<DT>::operator!=(const Vector<DT> &v) {
    return !operator==(v);
}

template<typename DT>
int Vector<DT>::capacity() {
    return capacityVector;
}

template<typename DT>
int Vector<DT>::size() {
    return sizeVector;
}

template<typename DT>
void Vector<DT>::push_back(DT &v) {
    if (sizeVector == capacityVector) {
        capacityVector += 5;
        DT *temp = new DT[capacityVector];
        for (int i = 0; i < sizeVector; i++)
            temp[i] = tab[i];

        temp[sizeVector] = v;
        delete[] tab;
        tab = temp;
        size++;
    } else {
        tab[sizeVector] = v;
        size++;
    }
}

template<typename DT>
void Vector<DT>::pop_back() {
    if (sizeVector > 0)
        sizeVector--;
}

template<typename DT>
void Vector<DT>::swap(Vector &other) {
    int tempSize, tempCapacity;
    DT *tempTab;

    tempTab = other.tab;
    tempSize = other.sizeVector;
    tempCapacity = other.capacityVector;

    other.tab = tab;
    other.sizeVector = sizeVector;
    other.capacity = capacityVector;

    sizeVector = tempSize;
    capacityVector = tempCapacity;
    tab = tempTab;
}

template<typename DT>
DT &Vector<DT>::front() {
    if (sizeVector > 0)
        return tab[0];
    else
        throw std::logic_error("Empty container");
}

template<typename DT>
const DT &Vector<DT>::front() const {
    if (sizeVector > 0)
        return tab[0];
    else
        throw std::logic_error("Empty container");
}

template<typename DT>
void Vector<DT>::resize(int count) {
    if (count < 0)
        throw std::length_error();
    else if (count < sizeVector)
        size = count;
    else if (count > capacityVector) {
        DT *tempTab = new DT[count];
        for (int i = 0; i < sizeVector; i++)
            tempTab[i] = tab[i];
        delete[] tab;
        tab = tempTab;
    }
}

template<typename DT>
const DT &Vector<DT>::back() const {
    if (sizeVector == 0)
        throw std::logic_error("Empty");

    return tab[sizeVector - 1];
}

template<typename DT>
DT &Vector<DT>::back() {
    if (sizeVector == 0)
        throw std::logic_error("Empty");

    return tab[sizeVector - 1];
}

template<typename DT>
DT &Vector<DT>::operator[](int size) {
    if (size > sizeVector - 1 || size < 0)
        throw std::out_of_range("Out of scope");
    else
        return tab[size];
}

template<typename DT>
const DT &Vector<DT>::operator[](int size) const {
    if (size > sizeVector - 1 || size < 0)
        throw std::out_of_range("Out of scope");
    else
        return tab[size];
}

template<typename DT>
void Vector<DT>::assign(int count, const DT &value) {
    if (count < 0)
        throw std::out_of_range("Out of scope");

    if (count < capacityVector)
        for (int i = 0; i < count; i++)
            tab[i] = value;
    else if (count >= capacityVector) {
        delete[] tab;
        tab = new DT[count + 5];
        capacityVector = count + 5;
        sizeVector = count;
        for (int i = 0; i < count; i++)
            tab[i] = value;
    }
}

template<typename DT>
Iterator<DT> Vector<DT>::end(){
     Iterator<DT> temp(tab + sizeVector);
    return temp;
}

template<typename DT>
Iterator<DT> Vector<DT>::begin(){
    Iterator<DT> temp(tab);
    return temp;
}

#endif //VECTOR_TEMPLATE_VECTOR_H
