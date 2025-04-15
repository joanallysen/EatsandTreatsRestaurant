#pragma once
#include "raylib.h"
#include "raygui.h"

#include "currentmenu.h"
#include "order.h"

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <string>

extern CurrentMenu currentMenu;

extern const int screenWidth;
extern const int screenHeight;
extern const int centerWidth;
extern const int centerHeight;

// store and manage all the items. 
class Menu {
private:
	static float totalIncomeToday;
	static std::shared_ptr<Item> currentSharedPtr;
    static int currentItemIndex;
	static std::map<int, std::shared_ptr<Item>> numToItems; // shared between all menu


	static Order currentOrder;

public:
	// getter
	static std::shared_ptr<Item> getSharedPtrItem();
    
	// setter
	static void addItem(int type);
    static void deleteCurrentItem();

	// raygui related method
	static void drawMenuEditor();
	// due to menu not accessing table manager, I have to return.
    static std::pair<bool, Order> drawCustomerOrderingSystem();

    // file manager helper
    static void setMenuItem(std::map<int, std::shared_ptr<Item>> tempNumToItem);
    static std::map<int, std::shared_ptr<Item>> getMenuItem();
};