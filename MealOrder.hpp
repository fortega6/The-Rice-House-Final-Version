#ifndef MEAL_ORDER_HPP
#define MEAL_ORDER_HPP

#include "Stack.hpp"
#include "OrderItem.hpp"
#include <string>
#include <ctime>

struct MealOrder
{
    int orderId_;
    std::string respbl_;
    tm* date_;
    Stack<OrderItem> items;

    MealOrder(int id = -1, const std::string& respbl = "");

    void addItem(int id, int units);
    void rmvItem(int id);
    void chgUnits(int id, int nwUnits);
};

#endif // MEAL_ORDER_HPP
