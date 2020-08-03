#include "Stack.hpp"

template <typename T>
Stack<T>::Stack() : List<T>()
{
}


template <typename T>
void Stack<T>::push(const T& item)
{
    List<T>::pushBack(item);
}


template <typename T>
T Stack<T>::pop()
{
    T popVal = List<T>::getEnt(List<T>::size_ - 1);
    List<T>::popBack();

    return popVal;
}
