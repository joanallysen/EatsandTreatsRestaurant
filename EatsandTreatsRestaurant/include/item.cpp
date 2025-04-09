#include "item.h"

using namespace std;


void Item::debug() const { cout << "a new item has been created" << endl; }

const string& Item::getName() const { return name; }
const string& Item::getDescription() const { return description; }
float Item::getPrice() const { return price; }
void Item::setName(string& _name) { name = _name; }
void Item::setDescription(string& _description) { description = _description; }
void Item::setPrice(float _price) { price = _price; }

//Drink::Drink(const char* _name, const char* _description, float _price): Item(_name, _description, _price) {}
void Drink::debug() const { cout << " a new DRINK has been created" << endl; }

//Food::Food(const char* _name, const char* _description, float _price) : Item(_name, _description, _price) {}
void Food::debug() const {
	cout << " a new FOOD has been created" << endl;
}

//Special::Special(const char* _name, const char* _description, float _price) : Item(_name, _description, _price) {}
void Special::debug() const {
	cout << " a new SPECIAL has been created" << endl;
}