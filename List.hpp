#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>

template <typename T>
class List
{
    struct Node
    {
        T data_;
        Node* next_;

        Node(const T& data = T(), Node* next = nullptr)
        {
            data_ = data;
            next_ = next;
        }
    };

    Node* front_;
    Node* back_;
    std::size_t size_;

public:
     List();
     List(const List<T>& oth);
    ~List();

     List<T>& operator=(const List<T>& rhs);

    void pushFront(const T& item);
    void pushBack(const T& item);
    void popFront();
    void popBack();

    // determine if a list is empty
    bool empty() const noexcept;

    // return current length of the list
    std::size_t size() const noexcept;

    // insert item at position in the list using 0-based indexing
    // throws std::range_error if position is invalid
    void insert(std::size_t pos, const T& item);

    // remove item at position in the list using 0-based indexing
    // throws std::range_error if position is invalid
    void remove(std::size_t pos);

    // remove all items from the list
    void clear() noexcept;

    // get a copy of the item at position using 0-based indexing
    // throws std::range_error if position is invalid
    T getEnt(std::size_t pos) const;

    // set the value of the item at position using 0-based indexing
    // throws std::range_error if position is invalid
    void setEnt(std::size_t pos, const T& nwVal);
};

#include "List.tpp"
#endif  //LIST_HPP
