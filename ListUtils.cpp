#include "ListUtils.hpp"
#include <iostream>
void ListUtils::sortByBranches(List<MealOrder>& list)
{
	MealOrder temp;
    //sorting algorithm here!
	for (int i=1; i<list.size(); i++)
	{
          for (int j=0 ; j<list.size() - 1; j++)
		  {
               if (list.getEnt(j).respbl_ > list.getEnt(j+1).respbl_)
			   {
                    temp = list.getEnt(j);
                    list.setEnt(j, list.getEnt(j+1));
                    list.setEnt(j+1, temp);
			   }
		  }
	}
}

void ListUtils::sortByReadyMeals(List<OrderItem>& list)
{
	OrderItem temp;

	for (int i=1; i<list.size(); i++)
	{
		for (int j=0 ; j<list.size() - 1; j++)
		{
		   if (list.getEnt(j).id_ > list.getEnt(j+1).id_)
		   {
				temp = list.getEnt(j);
				list.setEnt(j, list.getEnt(j+1));
				list.setEnt(j+1, temp);
		   }
		}
	}
}

int ListUtils::search(const List<MealOrder>& list, const int id)
{
    int pos = -1;
	int end = list.size()-1;
	int begin = 0;
	int center;

    //binary search algorithm here!
    while ((pos == -1) && begin <= end)
    {
		center = (end + begin)/2;
		std::cout << list.getEnt(center).orderId_ << "=" << id << std::endl;
		if (list.getEnt(center).orderId_ == id)
			pos = center;
		else if (id < list.getEnt(center).orderId_)
			end=center-1;
		else
			begin=center+1;
    }
	std::cout << pos << std::endl;
    return pos;
}
