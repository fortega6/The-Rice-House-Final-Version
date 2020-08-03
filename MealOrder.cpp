#include "MealOrder.hpp"

/**
 * @brief MealOrder::MealOrder
 * @param id
 * @param respbl
 */
MealOrder::MealOrder(int id, const std::string& respbl)
{
    orderId_ = id;
    respbl_  = respbl;

    time_t curTim = time(0);
    date_ = localtime(&curTim);
}

/**
 * @brief MealOrder::addItem
 * @param id
 * @param units
 */
void MealOrder::addItem(int id, int units)
{
    //if dishe is in the order... update the serves number
    Stack<OrderItem> tmpStk;
    bool added = false;

    while (!added && !items.empty())
    {
        OrderItem it = items.pop();
        if (it.id_ == id)
        {
            it.units_ += units;
            added = true;
        }

        tmpStk.push(it);
    }

    while (!tmpStk.empty())
        items.push(tmpStk.pop());   //restore moved items

    //if dishe isn't in the order... push it in the top
    if (!added)
        items.push(OrderItem(id, units));
}

/**
 * @brief MealOrder::rmvItem
 * @param id
 */
void MealOrder::rmvItem(int id)
{
    //remove dishe from the stack
    bool rmved = false;
    Stack<OrderItem> tmpStk;

    while (!rmved && !items.empty())
    {
        OrderItem it = items.pop();
        if (it.id_ == id)
            rmved = true;
        else
            tmpStk.push(it);
    }

    //restore moved items
    while (!tmpStk.empty())
        items.push(tmpStk.pop());
}


void MealOrder::chgUnits(int id, int nwUnits)
{
    Stack<OrderItem> tmpStk;

    //update serves number for the dishe in the stack
    //(if the dishe exists)
    bool chged = false;
    while (!chged && !items.empty())
    {
        OrderItem it = items.pop();
        if (it.id_ == id)
        {
            it.units_ = nwUnits;
            chged = true;
        }

        tmpStk.push(it);
    }

    //restore moved items
    while (!tmpStk.empty())
        items.push(tmpStk.pop());
}