#ifndef VECTOR_TEMPLATE_ITERATOR_H
#define VECTOR_TEMPLATE_ITERATOR_H

template<typename DT>
class Iterator {
private:
    DT * pointer;
public:
    Iterator(): pointer(nullptr){};
    Iterator(DT * item) : pointer(item){}

    Iterator<DT> & operator=(const Iterator<DT> & iter) = default;
    ~Iterator() = default;

    Iterator operator+(int add);
    Iterator operator-(int sub);

    bool operator!=(const Iterator<DT> & iter) const;
    bool operator==(const Iterator<DT> & iter) const;
    bool operator<(const Iterator<DT> & iter) const;
    bool operator<=(const Iterator<DT> & iter) const;
    bool operator>(const Iterator<DT> & iter) const;
    bool operator>=(const Iterator<DT> & iter) const;

    Iterator & operator++();
    Iterator operator++(int);
    Iterator & operator--();
    Iterator operator--(int);

    DT & operator[](int n);
    DT & operator*();
};

template<typename DT>
bool Iterator<DT>::operator==(const Iterator<DT> & iter) const {
    return pointer == iter.pointer;
}

template<typename DT>
bool Iterator<DT>::operator!=(const Iterator<DT> & iter) const {
    return pointer != iter.pointer;
}

template<typename DT>
bool Iterator<DT>::operator<(const Iterator<DT> & iter) const{
    return pointer < iter.pointer;
}

template<typename DT>
bool Iterator<DT>::operator<=(const Iterator<DT> & iter) const{
    return pointer <= iter.pointer;
}

template<typename DT>
bool Iterator<DT>::operator>(const Iterator<DT> &iter) const {
    return pointer > iter.pointer;
}

template<typename DT>
bool Iterator<DT>::operator>=(const Iterator<DT> &iter) const {
    return pointer >= iter.pointer;
}

template<typename DT>
DT & Iterator<DT>::operator[](int n) {
    return *(pointer + n);
}

template<typename DT>
Iterator<DT> Iterator<DT>::operator+(int add) {
    Iterator<DT> temp(pointer + add);
    return temp;
}

template<typename DT>
Iterator<DT> Iterator<DT>::operator-(int sub){
    Iterator<DT> temp(pointer - sub);
    return temp;
}

template<typename DT>
Iterator<DT> operator+(int add, const Iterator<DT> & iter){
    return iter + add;
}

template<typename DT>
Iterator<DT> & Iterator<DT>::operator++(){
    pointer++;
    return *this;
}

template<typename DT>
Iterator<DT> Iterator<DT>::operator++(int){
    Iterator<DT> temp = *this;
    pointer++;
    return temp;
}

template<typename DT>
Iterator<DT> & Iterator<DT>::operator--(){
    pointer--;
    return *this;
}

template<typename DT>
Iterator<DT> Iterator<DT>::operator--(int){
    Iterator<DT> temp = *this;
    pointer--;
    return temp;
}

template<typename DT>
DT & Iterator<DT>::operator*(){
    return *pointer;
}
#endif //VECTOR_TEMPLATE_ITERATOR_H
