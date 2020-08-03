#ifndef STACK_H
#define STACK_H

#include "List.hpp"

template <typename T>
class Stack : public List<T>
{
public:
    void push(const T& item);
    T top();
    T pop();
};

#include "Stack.tpp"
#endif  //STACK_H
