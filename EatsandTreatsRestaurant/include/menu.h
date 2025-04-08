#pragma once
#include "raylib.h"
#include "raygui.h"

#include "currentmenu.h"

#include <vector>
#include <map>
#include <string>
#include <memory>

// to order
#include "table.h"

extern CurrentMenu currentMenu;

extern const int screenWidth;
extern const int screenHeight;
extern const int centerWidth;
extern const int centerHeight;


//containing item name, description, and price
class Item {
protected:
    std::string name;
    std::string description;
    float price;

public:
    Item(const std::string& _name = "", const std::string& _description = "", float _price = 0.0f)
        : name(_name), description(_description), price(_price) {
    }

    virtual void debug() const;
    const std::string& getName() const;
    const std::string& getDescription() const;
    float getPrice() const;
    void setName(std::string& name);
    void setDescription(std::string& description);
    void setPrice(float price);
};

class Special : public Item {
public:
    Special(const std::string& _name, const std::string& _description, float _price)
        : Item(_name, _description, _price) {
    }

    void debug() const override;
};

class Food : public Item {
public:
    Food(const std::string& _name, const std::string& _description, float _price)
        : Item(_name, _description, _price) {
    }

    void debug() const override;
};

class Drink : public Item {
public:
    Drink(const std::string& _name, const std::string& _description, float _price)
        : Item(_name, _description, _price) {
    }

    void debug() const override;
};

// store and manage all the items. 
class Menu {
private:
	static float totalIncomeToday;
	static std::shared_ptr<Item> currentSharedPtr;
    static int currentItemIndex;
	static std::map<int, std::shared_ptr<Item>> numToItems; // shared between all menu
	float totalPrice;

public:
	static std::shared_ptr<Item> getSharedPtrItem();
    
	static void addItem(int type);
	static void drawMenuEditor();
    static void drawMenuOrder();
    static void deleteCurrentItem();

    // file manager only
    static void setMenuItem(std::map<int, std::shared_ptr<Item>> tempNumToItem);
    static std::map<int, std::shared_ptr<Item>> getMenuItem();
};