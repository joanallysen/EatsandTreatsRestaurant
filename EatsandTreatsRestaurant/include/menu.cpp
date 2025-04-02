#include "menu.h"
#include <iostream>

using namespace std;



Item::Item(const std::string& _itemName, const std::string& _description, float _price) :
	itemName(_itemName), description(_description), price(_price) {
}

void Item::debug() const {
	cout << "a new item has been created" << endl;
}

string Item::getItemName() const {
	return itemName;
}

Drink::Drink(const std::string& _itemName, const std::string& _description, float _price) :
	Item(_itemName, _description, _price) {
}

void Drink::debug() const {
	cout << " a new DRINK has been created" << endl;
}


Food::Food(const std::string& _itemName, const std::string& _description, float _price) :
	Item(_itemName, _description, _price) {
}

void Food::debug() const{
	cout << " a new FOOD has been created" << endl;
}

Special::Special(const std::string& _itemName, const std::string& _description, float _price) :
	Item(_itemName, _description, _price) {}


void Special::debug() const {
	cout << " a new SPECIAL has been created" << endl;
}


std::map<int, std::shared_ptr<Item>> Menu::numToItem;
float Menu::totalIncomeToday = 0.0f;

void Menu::initializeMenu() {
	numToItem[0] = std::make_shared<Special>("Spicy Miso Ramen Tacos", "A unique fusion of ramen noodles wrapped in a soft taco shell, topped with spicy miso broth, crispy pork belly, and pickled vegetables.", 18.00f);
	numToItem[1] = std::make_shared<Special>("Sushi Burrito Supreme", "A giant sushi roll turned into a burrito with fresh salmon, avocado, cucumber, and a drizzle of spicy mayo, all wrapped in seaweed and rice.", 22.00f);
	numToItem[2] = std::make_shared<Special>("Crispy Tempura Avocado Toast", "A crunchy tempura-fried avocado slice served on a toasted brioche with a soy sauce drizzle and sesame seeds.", 14.00f);
	numToItem[3] = std::make_shared<Special>("Korean BBQ Beef Wellington", "A twist on the classic Beef Wellington, using tender Korean BBQ marinated beef wrapped in puff pastry with a kimchi aioli.", 28.00f);
	numToItem[4] = std::make_shared<Special>("Tandoori Chicken Bao Buns", "Soft bao buns filled with tender, tandoori-spiced chicken, topped with cucumber ribbons, and drizzled with raita.", 16.00f);
					
	numToItem[5] = std::make_shared<Food>("Mango Sticky Rice Spring Rolls", "Fresh spring rolls stuffed with sweet coconut rice and mango slices, served with a side of condensed milk for dipping.", 12.00f);
	numToItem[6] = std::make_shared<Food>("Kimchi Fried Rice", "A flavorful fried rice made with tangy kimchi, mixed veggies, and topped with a fried egg and sesame seeds.", 16.00f);
	numToItem[7] = std::make_shared<Food>("Peking Duck Pizza", "A crispy thin crust pizza topped with Peking duck, hoisin sauce, and fresh cilantro.", 22.00f);
	numToItem[8] = std::make_shared<Food>("Truffle Soy Udon", "Soft udon noodles served in a savory truffle soy broth, garnished with shiitake mushrooms, green onions, and a soft-boiled egg.", 20.00f);
	numToItem[9] = std::make_shared<Food>("Sichuan Spicy Hot Wings", "Crispy chicken wings tossed in a bold Sichuan peppercorn sauce, with a hint of garlic and chili oil.", 14.00f);

	numToItem[10] = std::make_shared<Drink>("Lychee Rose Mojito", "A refreshing twist on a classic mojito, with lychee fruit, fresh mint, rose water, and rum.", 10.00f);
	numToItem[11] = std::make_shared<Drink>("Matcha Latte Fizz", "A fizzy, green matcha latte with a hint of vanilla syrup and soda water, served over ice.", 8.00f);
	numToItem[12] = std::make_shared<Drink>("Thai Iced Tea Lemonade", "A blend of sweetened Thai iced tea mixed with tart lemonade for a balanced fusion of flavors.", 7.00f);
	numToItem[13] = std::make_shared<Drink>("Yuzu Ginger Mule", "A zesty combination of yuzu citrus, ginger beer, and vodka, served in a chilled copper mug.", 12.00f);
	numToItem[14] = std::make_shared<Drink>("Passionfruit Sake Sangria", "A tropical sangria made with passionfruit puree, sake, white wine, and fresh fruit slices.", 14.00f);
}

std::shared_ptr<Item> Menu::currentSharedPtr = {};

std::shared_ptr<Item> Menu::getSharedPtrItem() {
	cout << "DEBUG, NUMBER OF REFERENCE COUNT:" << currentSharedPtr.use_count() << endl;
	return currentSharedPtr;
}


void Menu::drawMenuEditor() {
	DrawText("Please pick a item to edit", centerWidth - MeasureText("Please pick a item to edit", 58) / 2, centerHeight - 300, 58, BLACK);

	DrawText("Special", centerWidth - MeasureText("Special", 40) / 2 - 550, centerHeight - 200, 40, BLACK);
	DrawText("Meals", centerWidth - MeasureText("Meals", 40) / 2, centerHeight - 200, 40, BLACK);
	DrawText("Drinks", centerWidth - MeasureText("Drinks", 40) / 2 + 550, centerHeight - 200, 40, BLACK);

	int gap = 80;
	int i = 0;
	// if one of the special item is hit.
	for (const auto & special : numToItem) {
		auto temp = std::dynamic_pointer_cast<Special>(special.second);
		if (!temp) continue;
		if (GuiButton(Rectangle{ float(centerWidth - 775), float(centerHeight) + i * gap - 100, 450, 40}, (special.second->getItemName()).c_str())) {
			currentMenu = MENU_EDITOR_PROCESS;
			currentSharedPtr = special.second;
		}
		i++;
	}
	if (GuiButton(Rectangle{ float(centerWidth - 700), float(centerHeight) + i * gap - 100, 300, 40 }, "Add New")) {

	}

	i = 0;
	for (const auto& food : numToItem) {
		auto temp = std::dynamic_pointer_cast<Food>(food.second);
		if (!temp) continue;
		if (GuiButton(Rectangle{ float(centerWidth - 225), float(centerHeight) + i * gap - 100, 450, 40 }, (food.second->getItemName()).c_str())) {
			currentMenu = MENU_EDITOR_PROCESS;
		}
		i++;
	}
	if (GuiButton(Rectangle{ float(centerWidth - 150), float(centerHeight) + i * gap - 100, 300, 40 }, "Add New")) {

	}

	i = 0;
	for (const auto& drink : numToItem) {
		auto temp = std::dynamic_pointer_cast<Drink>(drink.second);
		if (!temp) continue;
		if (GuiButton(Rectangle{ float(centerWidth + 325), float(centerHeight) + i * gap - 100, 450, 40 }, (drink.second->getItemName()).c_str())) {
			currentMenu = MENU_EDITOR_PROCESS;
		}
		i++;
	}
	if (GuiButton(Rectangle{ float(centerWidth + 400), float(centerHeight) + i * gap - 100, 300, 40 }, "Add New")) {

	}
}
