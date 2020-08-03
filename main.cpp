#include "OrderItem.hpp"
#include "MealOrder.hpp"
#include "ListUtils.hpp"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

enum MainMenuOpt { EXIT,
                   NEW_ORDER,
                   SEARCH_ORDER,
                   VIEW_ORDER_LIST,
                   SUMM_BY_BRACH,
                   SUMM_BY_MEALS };

enum OrderMenuOpt { CANCEL_ORDER,
                    CONFIRM_ORDER,
                    ADD_ORDER_ITEM,
                    CHNG_ORDER_ITEM_DETAIL,
                    DISC_ORDER_ITEM };

const int BaseID = 1000;
List<std::string> RestDishes;
List<std::string> RestBranches;
List<MealOrder> RestOrders;

List<MealOrder> WaterfrontOrders;
List<MealOrder> PendingOrders;
List<MealOrder> KotaSentosaOrders;
List<MealOrder> PadawanOrders;
List<MealOrder> SamarahanOrders;

List<OrderItem> allItems;

void clrScrn(void);
void getPosInt(int& var, const std::string& prompt);
bool confirmAct(const std::string& action);

void presetData();
int selOption(const List<std::string>& options, const std::string& optMsg = "");

bool processItemAdd(MealOrder& order);
bool processItemChg(MealOrder& order);
bool processItemRmv(MealOrder& order);

bool processNewOrder();

void copyAllItems(void);
void appHead(void);
int mainMenu(void);
int orderMenu(void);
int selOrderId(void);
void insertBranch(MealOrder order);
void printOrderDetails(MealOrder mealOrder);
void printAllOrder(List<MealOrder> orders);
void printItemsByType(void);

int main(void)
{
    presetData();

    int exit = false, posOrder;
	MealOrder mealOrder;
	
    while (!exit)
    {
        clrScrn();
        int opt = mainMenu();
        switch (opt)
        {
        case EXIT:  //confirm exit
            clrScrn();
            if (confirmAct("exit"))
                exit = true;
            break;

        case NEW_ORDER:
            clrScrn();
            processNewOrder();
            break;

        case SEARCH_ORDER:
			clrScrn();
			posOrder = ListUtils::search(RestOrders, selOrderId());
			clrScrn();
			
			try
			{
				printOrderDetails(RestOrders.getEnt(posOrder));
			}
			catch (std::range_error e)
			{
				std::cout << e.what() << std::endl;
			}
			
			system ("pause");
            break;

        case VIEW_ORDER_LIST:
			clrScrn();
			printAllOrder(RestOrders);
			system ("pause");
            break;

        case SUMM_BY_BRACH:
			clrScrn();
			printAllOrder(WaterfrontOrders);
			printAllOrder(PendingOrders);
			printAllOrder(KotaSentosaOrders);
			printAllOrder(PadawanOrders);
			printAllOrder(SamarahanOrders);
			system ("pause");
            break;

        case SUMM_BY_MEALS:
			clrScrn();
			ListUtils::sortByReadyMeals(allItems);
			printItemsByType();
			std::cout << std::endl;
			system ("pause");
            break;

        default:
            break;
        }
    }

    return 0;
}

/**
 * @brief clrScrn
 */
void clrScrn(void)
{
    std::cout << std::string(100, '\n');
}

/**
 * @brief getPosInt
 * @param var
 * @param prompt
 */
void getPosInt(int& var, const std::string& prompt)
{
   do
   {
       std::cout << "  " << prompt << " ";
       std::cin >> var;
   }while (var <= 0);
}

/**
 * @brief confirmAct
 * @param action
 * @return
 */
bool confirmAct(const std::string& action)
{
    char ans;
    std::cout << "  Are you sure to " << action << " (Y/*): ";
    std::cin >> ans;

    return (ans == 'Y' || ans == 'y');
}

/**
 * @brief presetData
 */
void presetData()
{
    //rice dishes
    RestDishes.pushBack("Glutinous Rice Cake");
    RestDishes.pushBack("Nasi Lemak");
    RestDishes.pushBack("Steam Chicken Rice");
    RestDishes.pushBack("Inflated Rice Cookies");
    RestDishes.pushBack("Rice Pudding");

    //restaurant branches
    RestBranches.pushBack("Waterfront");
    RestBranches.pushBack("Pending");
    RestBranches.pushBack("Kota Sentosa");
    RestBranches.pushBack("Padawan");
    RestBranches.pushBack("Samarahan");

}

/**
 * @brief appHead
 */
void appHead(void)
{
    std::cout << "\n\tTHE RICE HOUSE\n\n";
}

/**
 * @brief mainMenu
 * @return
 */
int mainMenu(void)
{
    int opt = -1;

    clrScrn();
    appHead();
    std::cout << "  1. New Order\n";
    std::cout << "  2. View Order Details\n";
    std::cout << "  3. View Full Order List\n";
    std::cout << "  4. Summary Report by Branches\n";
    std::cout << "  5. Summary Report by Read-Meal\n";
    std::cout << "  0. Exit\n  ";
    std::cin >> opt;

    return opt;
}

/**
 * @brief orderMenu
 * @return
 */
int orderMenu(void)
{
    int opt = -1;

    clrScrn();
    appHead();
    std::cout << "  NEW ORDER IN PROCESS...\n";
    std::cout << "  1. Confirm Order\n";
    std::cout << "  2. Add Order Item\n";
    std::cout << "  3. Change Order Item Details\n";
    std::cout << "  4. Discard Order Item\n";
    std::cout << "  0. Cancel Order\n  ";
    std::cin >> opt;

    return opt;
}


bool processNewOrder()
{
    //sel. branch
    int branch = -1;
    while (branch < 0 || branch > RestBranches.size())
    {
        clrScrn();
        branch = selOption(RestBranches, "BRANCH:");
    }

    if (branch == 0)
        return false;

    //create order
    MealOrder order(BaseID + RestOrders.size() + 1,
                    RestBranches.getEnt(branch - 1));

    //items
    bool confirm = false;
    bool cancel = false;
    while (!cancel && !confirm)
    {
        clrScrn();
        int opt = orderMenu();

        switch (opt)
        {
        case CANCEL_ORDER:
            if (confirmAct("cancel order"))
                cancel = true;
            break;

        case CONFIRM_ORDER:
            if (order.items.size() > 0)
            {
                if (confirmAct("confirm order"))
                {
                    RestOrders.pushBack(order);
                    confirm = true;
					
					Stack<OrderItem> items = order.items;
					Stack<OrderItem> tmpStk;
					while (!items.empty())
					{
						OrderItem it = items.pop();
						allItems.pushBack(it);
						tmpStk.push(it);
					}

					//restore moved items
					while (!tmpStk.empty())
						items.push(tmpStk.pop());
					
					insertBranch(order);
                }
            }
            else
                std::cout << "  *** cannot confirm an empty order ***\n";
            break;

        case ADD_ORDER_ITEM:
            processItemAdd(order);
            break;

        case CHNG_ORDER_ITEM_DETAIL:
            processItemChg(order);
            break;

        case DISC_ORDER_ITEM:
            processItemRmv(order);
            break;

        default:
            std::cout << "  *** INVALID OPTION ***  " << std::endl;
            break;
        }
    }

    return confirm;
}


int selOption(const List<std::string>& options, const std::string& optMsg)
{
    int opt;

    std::cout << "  " << optMsg << std::endl;
    for (int i = 0; i < int(options.size()); ++i)
        std::cout << "  " << i+1 << ". " << options.getEnt(i) << std::endl;
    std::cout << "  0. None (Cancel Sel.)\n  ";
    std::cin >> opt;

    return opt;
}

/**
 * @brief processItemAdd
 * @param order
 * @return
 */
bool processItemAdd(MealOrder& order)
{
    bool added  = false;
    bool cancel = false;

    while (!cancel && !added)
    {
        clrScrn();
        int opt = selOption(RestDishes, "DISHES/DESSERTS:");

        if (opt >= 1 && opt <= int(RestDishes.size()))
        {
            int units;
            getPosInt(units, "Units/Serves: ");

            order.addItem(opt, units);
            added = true;
        }
        else if (opt == 0)
            cancel = true;
        else
            std::cout << "  *** INVALID OPTION *** " << std::endl;
    }

    return added;
}


/**
 * @brief processItemChg
 * @param order
 * @return
 */
bool processItemChg(MealOrder& order)
{
    List<OrderItem> items = order.items;

    //dishe descrip. by items
    List<std::string> ordDishes;
    List<int> ordItemIds;

    for (int i = 0; i < int(items.size()); ++i)
    {
        OrderItem it = items.getEnt(i);
        ordItemIds.pushBack(it.id_);
        ordDishes.pushBack(RestDishes.getEnt(it.id_ - 1));
    }

    //change order item details
    bool chnged = false;
    bool cancel = false;

    while (!cancel && !chnged)
    {
        clrScrn();
        int opt = selOption(ordDishes, "ADDED DISHES:");

        if (opt >= 1 && opt <= int(items.size()))
        {
            int units;
            getPosInt(units, "Units/Serves (New):");

            order.chgUnits(ordItemIds.getEnt(opt-1), units);
            chnged = true;
        }
        else if (opt == 0)
            cancel = true;
        else
            std::cout << "  *** INVALID OPTION *** " << std::endl;
    }

    return chnged;
}

/**
 * @brief processItemRmv
 * @param order
 * @return
 */
bool processItemRmv(MealOrder& order)
{
    List<OrderItem> items = order.items;

    //dishe descrip. by items
    List<std::string> ordDishes;
    List<int> ordItemIds;

    for (int i = 0; i < int(items.size()); ++i)
    {
        OrderItem it = items.getEnt(i);
        ordItemIds.pushBack(it.id_);
        ordDishes.pushBack(RestDishes.getEnt(it.id_ - 1));
    }

    //remove the order item
    bool rmved  = false;
    bool cancel = false;

    while (!cancel && !rmved)
    {
        clrScrn();
        int opt = selOption(ordDishes, "ADDED DISHES:");

        if (opt >= 1 && opt <= int(items.size()))
        {
            order.rmvItem(ordItemIds.getEnt(opt));
            rmved = true;
        }
        else if (opt == 0)
            cancel = true;
        else
            std::cout << "  *** INVALID OPTION *** " << std::endl;
    }

    return rmved;
}

int selOrderId(void){
	int id;
	std::cout << "  " << "SEARCH ORDER BY ID" << std::endl;
	for (int i = 0; i < RestOrders.size(); i++){
		std::cout  << "  " << RestOrders.getEnt(i).orderId_ << " " << RestOrders.getEnt(i).respbl_ << std::endl;
	}
	std::cout << "  " << "Enter Id: ";
	std::cin >> id;
	return id;
}

void printAllOrder(List<MealOrder> orders){
	for (int i = 0; i < orders.size(); i++){
		printOrderDetails(orders.getEnt(i));
	}
}

void insertBranch(MealOrder order){
	if (order.respbl_ == "Waterfront")
		WaterfrontOrders.pushBack(order);
    else if (order.respbl_ == "Pending")
		PendingOrders.pushBack(order);
    else if (order.respbl_ == "Kota Sentosa")
		KotaSentosaOrders.pushBack(order);
    else if (order.respbl_ == "Padawan")
		PadawanOrders.pushBack(order);
    else if (order.respbl_ == "Samarahan")
		SamarahanOrders.pushBack(order);
}

void printOrderDetails(MealOrder mealOrder){
	
	Stack<OrderItem> items = mealOrder.items;
	Stack<OrderItem> tmpStk;

    //update serves number for the dishe in the stack
    //(if the dishe exists)
    bool chged = false;
	int i = 1;
	std::cout << "  " << "=========================================" << std::endl;
	 std::cout << "  " << "Order ID : " << mealOrder.orderId_ << "\n" 
				  << "  " << "Branch : " << mealOrder.respbl_ << "\n" 
				  << "  " << "Date : " << asctime(mealOrder.date_) << "\n";
	std::cout << "  " << "=========================================" << std::endl;
    while (!chged && !items.empty())
    {
        OrderItem it = items.pop();
        std::cout  << "  " << "Item : " << i << "\n" 
				  << "  " << "Description : " << RestDishes.getEnt(it.id_-1) << "\n" 
				  << "  " << "Units/Set/Serves : " << it.units_ << ""
				  << std::endl;
		std::cout << "  " << "-----------------------------------------" << std::endl;
        tmpStk.push(it);
		i++;
    }
	std::cout << "  " << "=========================================" << std::endl;
	std::cout << std::endl;
    //restore moved items
    while (!tmpStk.empty())
        items.push(tmpStk.pop());
}

void printItemsByType(void){
	int type = allItems.getEnt(0).id_;
	OrderItem it;
	std::cout << "  " << "READY-MEALS" << "\t\t" << "UNITS/SET/SERVES" << std::endl << std::endl;
	for (int i = 0; i < allItems.size(); i++)
	{
		it = allItems.getEnt(i);
		if(type != it.id_){
			type = it.id_;
			std::cout << "  " << "-----------------------------------------" << std::endl;
		}
			
		std::cout << "  " << RestDishes.getEnt(it.id_-1) <<  "\t\t\t"  << it.units_ << std::endl;
	}
}