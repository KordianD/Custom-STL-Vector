#ifndef VECTOR_TEMPLATE_VECTOR_H
#define VECTOR_TEMPLATE_VECTOR_H

#include "Iterator.h"

template<typename DT>
class Vector {
private:
    DT *storage;
    int _size;
    int _capacity;
public:
    Vector() : storage(nullptr), _size(0), _capacity(0) {}
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
Vector<DT>::Vector(int size) : _size(size), _capacity(size) {
    storage = new DT[_size];
}

template<typename DT>
Vector<DT>::Vector(int size, int value) : _size(size), _capacity(size){
    storage = new DT[_size];

    for (int i = 0; i < _size; i++)
        storage[i] = value;
}

template<typename DT>
Vector<DT>::Vector(const std::initializer_list<DT> &v) : _size(v.size()), _capacity(v.size()) {
    storage = new DT[v.size()];

    for (int i = 0; i < v.size(); i++)
        storage[i] = *(v.begin() + i);
}

template<typename DT>
Vector<DT>::Vector(const Vector<DT> &v) : _size(v._size), _capacity(v._capacity) {
    storage = new DT[_capacity];

    for (int i = 0; i < _size; i++)
        storage[i] = v.storage[i];
}

template<typename DT>
Vector<DT>::Vector(Vector<DT> &&v): _size(0), _capacity(0), storage(nullptr)
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
    delete[] storage;
}

template<typename DT>
bool Vector<DT>::operator==(const Vector<DT> &v) const {
    if (_size != v._size || _capacity != v._capacity)
        return false;

    for (int i = 0; i < _size; i++)
        if (storage[i] != v.storage[i])
            return false;

    return true;
}

template<typename DT>
bool Vector<DT>::operator!=(const Vector<DT> &v) const{
    return !operator==(v);
}

template<typename DT>
int Vector<DT>::capacity() const{
    return _capacity;
}

template<typename DT>
int Vector<DT>::size() const{
    return _size;
}

template<typename DT>
void Vector<DT>::push_back(DT &v) {
    if (_size == _capacity) {
        _capacity += 5;
        DT *temp = new DT[_capacity];
        for (int i = 0; i < _size; i++)
            temp[i] = storage[i];

        temp[_size] = v;
        delete[] storage;
        storage = temp;
        _size++;
    } else {
        storage[_size] = v;
        _size++;
    }
}

template<typename DT>
void Vector<DT>::pop_back() {
    if (_size > 0)
        _size--;
}

template<typename DT>
void Vector<DT>::swap(Vector &other) noexcept {
    std::swap(storage,           other.storage);
    std::swap(_size,             other._size);
    std::swap(_capacity,         other._capacity);
}

template<typename DT>
DT &Vector<DT>::front() {
    if (_size > 0)
        return storage[0];
    else
        throw std::logic_error("Empty container");
}

template<typename DT>
const DT &Vector<DT>::front() const {
    if (_size > 0)
        return storage[0];
    else
        throw std::logic_error("Empty container");
}

template<typename DT>
void Vector<DT>::resize(int count) {
    if (count < 0)
        throw std::length_error();
    else if (count < _size)
        _size = count;
    else if (count > _capacity) {
        DT *tempStorage = new DT[count];
        for (int i = 0; i < _size; i++)
            tempStorage[i] = storage[i];
        delete[] storage;
        storage = tempStorage;
    }
}

template<typename DT>
const DT &Vector<DT>::back() const {
    if (_size == 0)
        throw std::logic_error("Empty");

    return storage[_size - 1];
}

template<typename DT>
DT &Vector<DT>::back() {
    if (_size == 0)
        throw std::logic_error("Empty");

    return storage[_size - 1];
}

template<typename DT>
DT &Vector<DT>::operator[](int size) {
    if (size > _size - 1 || _size < 0)
        throw std::out_of_range("Out of scope");
    else
        return storage[size];
}

template<typename DT>
const DT &Vector<DT>::operator[](int size) const {
    if (size > _size - 1 || size < 0)
        throw std::out_of_range("Out of scope");
    else
        return storage[size];
}

template<typename DT>
void Vector<DT>::assign(int count, const DT &value) {
    if (count < 0)
        throw std::out_of_range("Out of scope");

    if (count < _capacity)
        for (int i = 0; i < count; i++)
            storage[i] = value;
    else if (count >= _capacity) {
        delete[] storage;
        storage = new DT[count + 5];
        _capacity = count + 5;
        _size = count;
        for (int i = 0; i < count; i++)
            storage[i] = value;
    }
}

template<typename DT>
Iterator<DT> Vector<DT>::end(){
     Iterator<DT> temp(storage + _size);
    return temp;
}

template<typename DT>
Iterator<DT> Vector<DT>::begin(){
    Iterator<DT> temp(storage);
    return temp;
}

template<typename DT>
Iterator<DT> Vector<DT>::erase(Iterator<DT> pos) {
    int i = 0;
    auto it = (*this).begin();

    for (it; it != pos; it++, i++);

    for (auto it = pos + 1; it != (*this).end(); it++, i++)
        storage[i] = storage[i + 1];

    _size--;
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
        storage[i - temp] = storage[i];

    _size -=  temp;
    return last;
}

template<typename DT>
Iterator<DT> Vector<DT>::insert(Iterator<DT> pos, const DT & value){
    int i = 0;

    if (_capacity > _size){
        for(Iterator<DT> it = storage + _size; it != pos; it--, i++)
            storage[_size - i] = storage[_size - i - 1];
        *pos = value;
        _size++;
    } else{
        DT * temp = new DT[_size + 1];
            for (Iterator<DT> it = storage; it != pos; it++, i++)
             temp[i] = storage[i];
        temp[i] = value;
        i++;
            for (Iterator<DT> it = storage + i + 1; it != storage + _size + 2; it++, i++)
            temp[i] = storage[i-1];
        delete [] storage;
        storage = temp;
        _size++;
        _capacity = _size;
    }
}

template<typename DT>
void Vector<DT>::insert(Iterator<DT> pos, int count, const DT & value){
    DT * temp = new DT[_size + count];
    int i = 0, j = 0;

    for (Iterator<DT> it = storage; it != pos; it++, i++)
        temp[i] = storage[i];

    for (j; j < count; j++)
        temp[i+j] = value;

    for (Iterator<DT> it = storage + i; it != storage + _size; it++, i++)
        temp[i+j] = storage[i];

    _size += count;
    _capacity = _size;
    delete [] storage;
    storage = temp;
}

#endif //VECTOR_TEMPLATE_VECTOR_H
