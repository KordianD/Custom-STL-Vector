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
    Vector(int size, int value);
    Vector(const std::initializer_list<DT> &v);
    Vector(const Vector<DT> &v);
    Vector(Vector<DT> &&v);

    Vector &operator=(const Vector<DT> &v);
    Vector &operator=(Vector<DT> &&v);

    ~Vector();

    bool operator==(const Vector<DT> &v) const;
    bool operator!=(const Vector<DT> &v) const;

    int capacity() const;
    int size() const;

    void push_back(DT & v);

    void pop_back();

    void swap(Vector & other) noexcept;

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

     Iterator<DT> erase(Iterator<DT> pos);
     Iterator<DT> erase(Iterator<DT> first, Iterator<DT> last);
     Iterator<DT> insert(Iterator<DT> pos, const DT & value);
     void insert(iterator pos, int count, const DT & value);

     Iterator<DT> end();
     Iterator<DT> begin();

};

template<typename DT>
Vector<DT>::Vector(int size) : sizeVector(size), capacityVector(size) {
    tab = new DT[sizeVector];
}

template<typename DT>
Vector<DT>::Vector(int size, int value) : sizeVector(size), capacityVector(size){
    tab = new DT[sizeVector];

    for (int i = 0; i < sizeVector; i++)
        tab[i] = value;
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
Vector<DT>::Vector(Vector<DT> &&v): sizeVector(0), capacityVector(0), tab(nullptr)
{
    v.swap(*this);
}

template<typename DT>
Vector<DT> &Vector<DT>::operator=(const Vector<DT> &v) {

    Vector<DT> copy(v);
    copy.swap(*this);
    return *this;
}

template<typename DT>
Vector<DT> &Vector<DT>::operator=(Vector<DT> &&v) {
    v.swap(*this);
    return *this;
}

template<typename DT>
Vector<DT>::~Vector() {
    delete[] tab;
}

template<typename DT>
bool Vector<DT>::operator==(const Vector<DT> &v) const {
    if (sizeVector == v.sizeVector && capacityVector == v.capacityVector) {
        for (int i = 0; i < sizeVector; i++)
            if (tab[i] != v.tab[i])
                return false;
        return true;
    }
    return false;

}

template<typename DT>
bool Vector<DT>::operator!=(const Vector<DT> &v) const{
    return !operator==(v);
}

template<typename DT>
int Vector<DT>::capacity() const{
    return capacityVector;
}

template<typename DT>
int Vector<DT>::size() const{
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
void Vector<DT>::swap(Vector &other) noexcept {
    std::swap(tab,           other.tab);
    std::swap(sizeVector,    other.sizeVector);
    std::swap(capacityVector,other.capacityVector);
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

template<typename DT>
Iterator<DT> Vector<DT>::erase(Iterator<DT> pos) {
    int i = 0;
    auto it = (*this).begin();

    for (it; it != pos; it++, i++);

    for (auto it = pos + 1; it != (*this).end(); it++, i++)
        tab[i] = tab[i + 1];

    sizeVector--;
    return pos;
}

template<typename DT>
Iterator<DT> Vector<DT>::erase(Iterator<DT> first, Iterator<DT> last){
    int i = 0;
    int temp = 0;
    auto it = (*this).begin();

    for (it; it != first; it++, i++);
    for (it = first; it != last; it++, temp++, i++);

    for (auto it = last; it != (*this).end(); it++, i++)
        tab[i - temp] = tab[i];

    sizeVector -=  temp;
    return last;
}

template<typename DT>
Iterator<DT> Vector<DT>::insert(Iterator<DT> pos, const DT & value){
    int i = 0;

    if (capacityVector > sizeVector){
        for(Iterator<DT> it = tab + sizeVector; it != pos; it--, i++)
            tab[sizeVector - i] = tab[sizeVector - i - 1];
        *pos = value;
        sizeVector++;
    } else{
        DT * temp = new DT[sizeVector + 1];
            for (Iterator<DT> it = tab; it != pos; it++, i++)
             temp[i] = tab[i];
        temp[i] = value;
        i++;
            for (Iterator<DT> it = tab + i + 1; it != tab + sizeVector + 2; it++, i++)
            temp[i] = tab[i-1];
        delete [] tab;
        tab = temp;
        sizeVector++;
        capacityVector = sizeVector;
    }
}

template<typename DT>
void Vector<DT>::insert(Iterator<DT> pos, int count, const DT & value){
    DT * temp = new DT[sizeVector + count];
    int i = 0, j = 0;

    for (Iterator<DT> it = tab; it != pos; it++, i++)
        temp[i] = tab[i];

    for (j; j < count; j++)
        temp[i+j] = value;

    for (Iterator<DT> it = tab + i; it != tab + sizeVector; it++, i++)
        temp[i+j] = tab[i];

    sizeVector += count;
    capacityVector = sizeVector;
    delete [] tab;
    tab = temp;
}

#endif //VECTOR_TEMPLATE_VECTOR_H
