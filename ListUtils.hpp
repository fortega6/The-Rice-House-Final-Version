#ifndef LIST_UTILS_H
#define LIST_UTILS_H

#include "List.hpp"
#include "MealOrder.hpp"

namespace ListUtils
{
    void sortByBranches(List<MealOrder>& list);
	
	void sortByReadyMeals(List<OrderItem>& list);
	
    int search(const List<MealOrder>& list, const int id);
}

#endif  //LIST_UTILS_H
