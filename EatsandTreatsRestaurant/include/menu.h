#pragma once
#include "raylib.h"
#include "raygui.h"

#include "currentmenu.h"
#include <vector>
#include <map>
#include <string>
#include <memory>

extern CurrentMenu currentMenu;

extern const int screenWidth;
extern const int screenHeight;
extern const int centerWidth;
extern const int centerHeight;




//containing item name, description, and price
class Item {
protected:
	std::string itemName;
	std::string description;
	float price;

public:
	Item(const std::string& _itemName = "", const std::string& _description = "", float _price = 0.0f);

	virtual void debug() const;
	std::string getItemName() const;
};

// for now there's no specific variable inside drink.
class Drink : public Item {
public:
	Drink(const std::string& _itemName = "", const std::string& _description = "", float _price = 0.0f);
	
	void debug() const override;
};

// for now there's no specific varianle inside food
class Food : public Item {
public:
	Food(const std::string& _itemName = "", const std::string& _description = "", float _price = 0.0f);

	void debug() const override;
};

class Special : public Item {
public:
	Special(const std::string& _itemName = "", const std::string& _description = "", float _price = 0.0f);

	void debug() const override;
};
// store and manage all the items. 
class Menu {
private:
	static float totalIncomeToday;
	static std::shared_ptr<Item> currentSharedPtr;
	static std::map<int, std::shared_ptr<Item>> numToItem; // shared between all menu
	float totalPrice;

public:
	static std::shared_ptr<Item> getSharedPtrItem();
	static void initializeMenu();
	static void updateNumToMenu();
	static void drawMenuEditor();
};