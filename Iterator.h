#ifndef VECTOR_TEMPLATE_ITERATOR_H
#define VECTOR_TEMPLATE_ITERATOR_H

template<typename DT>
class Iterator {
private:
    DT * point;
public:
    typedef std::ptrdiff_t                    difference_type;
    typedef DT                                 value_type;
    typedef DT *                               pointer;
    typedef DT &                               reference;
    typedef std::random_access_iterator_tag   iterator_category	;

    Iterator(): point(nullptr){};
    Iterator(DT * item) : point(item){}

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
    return point == iter.point;
}

template<typename DT>
bool Iterator<DT>::operator!=(const Iterator<DT> & iter) const {
    return point != iter.point;
}

template<typename DT>
bool Iterator<DT>::operator<(const Iterator<DT> & iter) const{
    return point < iter.point;
}

template<typename DT>
bool Iterator<DT>::operator<=(const Iterator<DT> & iter) const{
    return point <= iter.point;
}

template<typename DT>
bool Iterator<DT>::operator>(const Iterator<DT> &iter) const {
    return point > iter.point;
}

template<typename DT>
bool Iterator<DT>::operator>=(const Iterator<DT> &iter) const {
    return point >= iter.point;
}

template<typename DT>
DT & Iterator<DT>::operator[](int n) {
    return *(point + n);
}

template<typename DT>
Iterator<DT> Iterator<DT>::operator+(int add) {
    Iterator<DT> temp(point + add);
    return temp;
}

template<typename DT>
Iterator<DT> Iterator<DT>::operator-(int sub){
    Iterator<DT> temp(point - sub);
    return temp;
}

template<typename DT>
Iterator<DT> operator+(int add, const Iterator<DT> & iter){
    return iter + add;
}

template<typename DT>
Iterator<DT> & Iterator<DT>::operator++(){
    point++;
    return *this;
}

template<typename DT>
Iterator<DT> Iterator<DT>::operator++(int){
    Iterator<DT> temp = *this;
    point++;
    return temp;
}

template<typename DT>
Iterator<DT> & Iterator<DT>::operator--(){
    point--;
    return *this;
}

template<typename DT>
Iterator<DT> Iterator<DT>::operator--(int){
    Iterator<DT> temp = *this;
    point--;
    return temp;
}

template<typename DT>
DT & Iterator<DT>::operator*(){
    return *point;
}
#endif //VECTOR_TEMPLATE_ITERATOR_H
