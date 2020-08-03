#include <iostream>
#include "RestOrderMngr.hpp"

RestOrderMngr::RestOrderMngr()
{
}

void RestOrderMngr::addDishe(const std::string& dishe){
	dishes_.pushBack(dishe);
}

void RestOrderMngr::printByMeals(void){
	for (int i=0; i < dishes_.size(); i++)
		std::cout << dishes_.getEnt(i) << std::endl;
}