#include "List.hpp"
#include <stdexcept>

template <typename T>
List<T>::List()
{
    front_ = nullptr;
    back_ = nullptr;
    size_ = 0;
}

template <typename T>
List<T>::List(const List<T>& oth)
{
    //traverse and copy right side list
    front_ = nullptr;

    Node* othPtr = oth.front_;
    Node* cpyPtr = nullptr;

    while (othPtr)
    {
        Node* node = new Node(othPtr->data_);
        if (!cpyPtr)
            front_ = cpyPtr = node;
        else
            cpyPtr = cpyPtr->next_ = node;

        othPtr = othPtr->next_;
    }

    back_ = cpyPtr;
    size_ = oth.size_;
}

template <typename T>
List<T>::~List()
{
    clear();
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& rhs)
{
    clear();    //release current allocated mem.

    //traverse and copy right side list
    Node* rhsPtr = rhs.front_;
    Node* cpyPtr = nullptr;

    while (rhsPtr)
    {
        Node* node = new Node(rhsPtr->data_);
        if (!cpyPtr)
            front_ = cpyPtr = node;
        else
            cpyPtr = cpyPtr->next_ = node;

        rhsPtr = rhsPtr->next_;
    }

    back_ = cpyPtr;
    size_ = rhs.size_;
    return *this;
}

template <typename T>
void  List<T>::pushFront(const T& item)
{
    insert(0, item);
}

template <typename T>
void  List<T>::pushBack(const T& item)
{
    insert(size_, item);
}

template <typename T>
void  List<T>::popFront()
{
    remove(0);
}

template <typename T>
void  List<T>::popBack()
{
    remove(size_ - 1);
}

// determine if a list is empty
template <typename T>
bool List<T>::empty() const noexcept
{
    return (size_ == 0);
}

// return current size_ of the list
template <typename T>
std::size_t List<T>::size() const noexcept
{
    return size_;
}

// insert item at position in the list using 0-based indexing
// throws std::range_error if position is invalid
template <typename T>
void List<T>::insert(std::size_t pos, const T& item)
{
    if (pos < 0 || pos > size_)
        throw std::range_error("Range error: position is invalid!");

    //traverse the list to position
    Node* curr = front_;
    Node* prev = nullptr;
    int count = 0;

    while (count < pos)
    {
        prev = curr;
        curr = curr->next_;
        ++count;
    }

    //create and insert new node
    Node* node = new Node(item, curr);

    if (!prev)          //insert in the beginning!
        front_ = node;
    else                //insert after the beginning!
        prev->next_ = node;

    if (prev == back_)  //inserted at last!
        back_ = node;

    ++size_;
}

// remove item at position in the list using 0-based indexing
// throws std::range_error if position is invalid
template <typename T>
void List<T>::remove(std::size_t pos)
{
    if (pos < 0 || pos >= size_)
        throw std::range_error("Range error: position is invalid!");

    //traverse the list to position
    Node* curr = front_;
    Node* prev = nullptr;
    int count = 0;

    while (count < pos)
    {
        prev = curr;
        curr = curr->next_;
        ++count;
    }

    //remove the node
    if (prev)
        prev->next_ = curr->next_;
    else
        front_ = curr->next_;

    if (curr == back_)
        back_ = prev;

    --size_;
    delete curr;
}

// remove all items from the list
template <typename T>
void List<T>::clear() noexcept
{
    //release nodes allocated mem.
    Node* ptr = front_;
    while (ptr)
    {
        Node* tmp = ptr;
        ptr = ptr->next_;
        delete tmp;
    }

    front_ = nullptr;
    back_ = nullptr;
    size_ = 0;
}

// get a copy of the item at position using 0-based indexing
// throws std::range_error if position is invalid
template <typename T>
T List<T>::getEnt(std::size_t pos) const
{
    if (pos < 0 || pos >= size_)
        throw std::range_error("Range error: position is invalid!");

    Node* curr = front_;
    for (int i = 0; i < pos; ++i)
        curr = curr->next_;

    return curr->data_;
}

// set the value of the item at position using 0-based indexing
// throws std::range_error if position is invalid
template <typename T>
void List<T>::setEnt(std::size_t pos, const T& nwVal)
{
    if (pos < 0 || pos >= size_)
        throw std::range_error("Range error: position is invalid!");

    Node* curr = front_;
    for (int i = 0; i < pos; ++i)
        curr = curr->next_;
    curr->data_ = nwVal;
}
