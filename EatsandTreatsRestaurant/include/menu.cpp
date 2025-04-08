#include "menu.h"
#include <iostream>

using namespace std;


void Item::debug() const {cout << "a new item has been created" << endl;}

const string& Item::getName() const { return name; }
const string& Item::getDescription() const {return description;}
float Item::getPrice() const {return price;}
void Item::setName(string &_name) { name = _name; }
void Item::setDescription(string &_description) { description = _description; }
void Item::setPrice(float _price) { price = _price; }

//Drink::Drink(const char* _name, const char* _description, float _price): Item(_name, _description, _price) {}
void Drink::debug() const {cout << " a new DRINK has been created" << endl;}

//Food::Food(const char* _name, const char* _description, float _price) : Item(_name, _description, _price) {}
void Food::debug() const{
	cout << " a new FOOD has been created" << endl;
}

//Special::Special(const char* _name, const char* _description, float _price) : Item(_name, _description, _price) {}
void Special::debug() const {
	cout << " a new SPECIAL has been created" << endl;
}


std::map<int, std::shared_ptr<Item>> Menu::numToItems;
float Menu::totalIncomeToday = 0.0f;


std::shared_ptr<Item> Menu::currentSharedPtr = {};
int Menu::currentItemIndex = {};

std::shared_ptr<Item> Menu::getSharedPtrItem() {
	/*cout << "DEBUG, NUMBER OF REFERENCE COUNT:" << currentSharedPtr.use_count() << endl;*/
	return currentSharedPtr;
}

// Planned to use type_info& type to add item based on their type, realized that's time consuming
// And also not readable and also du to time constraint, I'm just gonna use int.
// (Special, 0), (Food, 1), (Drink, 2)
void Menu::addItem(int type) {
	// check if there's any item
	if (numToItems.empty()) return;

	std::shared_ptr<Item> newItem;
	switch (type) {
	case 0:
		newItem = std::make_shared<Special>("New Special", "...", 0.0f);
		break;
	case 1:
		newItem = std::make_shared<Food>("New Food", "...", 0.0f);
		break;
	case 2:
		newItem = std::make_shared<Drink>("New Drink", "...", 0.0f);
		break;
	}

	numToItems[numToItems.rbegin()->first + 1] = newItem; // reason why I use this is after deletion is not truly gone. The index is skipped
}
void Menu::deleteCurrentItem() {
	numToItems.erase(currentItemIndex);
}



void Menu::drawMenuOrder() {
	DrawText("Please pick an item to order", centerWidth - MeasureText("Please click an item to order", 58) / 2, centerHeight - 300, 58, BLACK);

	DrawText("Special", centerWidth - MeasureText("Special", 40) / 2 - 650, centerHeight - 200, 40, BLACK);
	DrawText("Meals", centerWidth - MeasureText("Meals", 40) / 2 - 300, centerHeight - 200, 40, BLACK);
	DrawText("Drinks", centerWidth - MeasureText("Drinks", 40) / 2 + 50, centerHeight - 200, 40, BLACK);
	DrawText("Customer Order", centerWidth - MeasureText("Customer Order", 40) / 2 + 750, centerHeight - 200, 40, BLACK);

	// if one of the special item is hit.
	int gap = 50;
	int i = 0;

	shared_ptr<Order> currentOrder = TableManager::getCurrentTableOrderPointer();
	for (const auto& special : numToItems) {
		auto temp = std::dynamic_pointer_cast<Special>(special.second);
		if (!temp) continue;
		if (GuiButton(Rectangle{ float(centerWidth - 800), float(centerHeight) + i * gap - 100, 300, 40 }, (special.second->getName().c_str()))) {
			
		}
		i++;
	}

	i = 0;
	for (const auto& food : numToItems) {
		auto temp = std::dynamic_pointer_cast<Food>(food.second);
		if (!temp) continue;
		if (GuiButton(Rectangle{ float(centerWidth - 450), float(centerHeight) + i * gap - 100, 300, 40 }, (food.second->getName().c_str()))) {
			currentMenu = MENU_EDITOR_PROCESS;
			currentSharedPtr = food.second;
			currentItemIndex = food.first;
		}
		i++;
	}

	i = 0;
	for (const auto& drink : numToItems) {
		auto temp = std::dynamic_pointer_cast<Drink>(drink.second);
		if (!temp) continue;
		if (GuiButton(Rectangle{ float(centerWidth - 100), float(centerHeight) + i * gap - 100, 300, 40 }, (drink.second->getName().c_str()))) {
			
		}
		i++;
	}

	for (const auto& item : currentOrder->numToUserOrder) {
		if (GuiButton(Rectangle{ float(centerWidth - 100), float(centerHeight) + i * gap - 100, 300, 40 }, (item.second->getName().c_str()))) {

		}
	}
}






void Menu::drawMenuEditor() {
	DrawText("Please pick an item to edit", centerWidth - MeasureText("Please pick an item to edit", 58) / 2, centerHeight - 300, 58, BLACK);

	DrawText("Special", centerWidth - MeasureText("Special", 40) / 2 - 550, centerHeight - 200, 40, BLACK);
	DrawText("Meals", centerWidth - MeasureText("Meals", 40) / 2, centerHeight - 200, 40, BLACK);
	DrawText("Drinks", centerWidth - MeasureText("Drinks", 40) / 2 + 550, centerHeight - 200, 40, BLACK);

	int gap = 80;
	int i = 0;
	// if one of the special item is hit.
	for (const auto& special : numToItems) {
		auto temp = std::dynamic_pointer_cast<Special>(special.second);
		if (!temp) continue;
		if (GuiButton(Rectangle{ float(centerWidth - 775), float(centerHeight) + i * gap - 100, 450, 40}, (special.second->getName().c_str()))) {
			currentMenu = MENU_EDITOR_PROCESS;
			currentSharedPtr = special.second;
			currentItemIndex = special.first; //this is to allow removal.
		}
		i++;
	}
	// if the add new button is hit
	if (GuiButton(Rectangle{ float(centerWidth - 700), float(centerHeight) + i * gap - 100, 300, 40 }, "Add New")) {
		addItem(0);
	}

	i = 0;
	for (const auto& food : numToItems) {
		auto temp = std::dynamic_pointer_cast<Food>(food.second);
		if (!temp) continue;
		if (GuiButton(Rectangle{ float(centerWidth - 225), float(centerHeight) + i * gap - 100, 450, 40 }, (food.second->getName().c_str()))) {
			currentMenu = MENU_EDITOR_PROCESS;
			currentSharedPtr = food.second;
			currentItemIndex = food.first;
		}
		i++;
	}
	if (GuiButton(Rectangle{ float(centerWidth - 150), float(centerHeight) + i * gap - 100, 300, 40 }, "Add New")) {
		addItem(1);
	}

	i = 0;
	for (const auto& drink : numToItems) {
		auto temp = std::dynamic_pointer_cast<Drink>(drink.second);
		if (!temp) continue;
		if (GuiButton(Rectangle{ float(centerWidth + 325), float(centerHeight) + i * gap - 100, 450, 40 }, (drink.second->getName().c_str()))) {
			currentMenu = MENU_EDITOR_PROCESS;
			currentSharedPtr = drink.second;
			currentItemIndex = drink.first;
		}
		i++;
	}
	if (GuiButton(Rectangle{ float(centerWidth + 400), float(centerHeight) + i * gap - 100, 300, 40 }, "Add New")) {
		addItem(2);
	}
}

void Menu::setMenuItem(std::map<int, std::shared_ptr<Item>> tempNumToItem) {
	numToItems = tempNumToItem;
}

std::map<int, std::shared_ptr<Item>> Menu::getMenuItem() {
	return numToItems;
}