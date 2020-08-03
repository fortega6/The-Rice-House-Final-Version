#ifndef ORDER_ITEM_H
#define ORDER_ITEM_H

struct OrderItem
{
    int id_;
    int units_;

    OrderItem(int itemId = -1, int units = -1)
    {
        id_ = itemId;
        units_  = units;
    }
};

#endif  //ORDER_ITEM_H
