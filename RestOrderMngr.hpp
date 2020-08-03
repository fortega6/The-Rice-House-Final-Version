#ifndef REST_ORDER_MNGR_HPP
#define REST_ORDER_MNGR_HPP

#include "List.hpp"
#include "MealOrder.hpp"
#include <string>

class RestOrderMngr
{
    List<std::string> dishes_;
    List<MealOrder> orders_;

public:
    RestOrderMngr();

    void addDishe(const std::string& dishe);
    void addOrder(const MealOrder& order);
    MealOrder getOrder(int id);

    void printAllOrder(void);
    void printByBrach(void);
    void printByMeals(void);
};
#include "RestOrderMngr.cpp"
#endif  //REST_ORDER_MNGR
