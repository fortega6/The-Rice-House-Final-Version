#include "Stack.hpp"

/**
 * @brief Stack<T>::push
 * @param item
 */
template <typename T>
void Stack<T>::push(const T& item)
{
    List<T>::pushBack(item);
}

/**
 * @brief Stack<T>::top
 * @return
 */
template <typename T>
T Stack<T>::top()
{
    return List<T>::getEnt(List<T>::size() - 1);
}

/**
 * @brief Stack<T>::pop
 * @return
 */
template <typename T>
T Stack<T>::pop()
{
    T val = List<T>::getEnt(List<T>::size() - 1);
    List<T>::popBack();

    return val;
}
