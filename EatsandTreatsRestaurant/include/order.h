#pragma once
#include <string>
#include <vector>
#include <memory>
#include <map>
#include "item.h"
#include "raygui.h"
#include "raylib.h"
#include "simpleUtil.h"

extern const int screenWidth;
extern const int screenHeight;
extern const int centerWidth;
extern const int centerHeight;

class Order {
private:
    std::string specialRequest;
    static float totalIncome;
    // key to {item object, amount}
    std::map<int, std::pair<std::shared_ptr<Item>, int>> numToUserOrderAndAmount;
    // item name to {item object, amount}
    static std::map<std::string, std::pair<std::shared_ptr<Item>, int>> itemToAmountOrdered;

public:
    // similar to setter
    void addOrder(std::shared_ptr<Item> item);
    void reduceOrder(std::shared_ptr<Item> item);
    void addToTotalIncome();
    void setSpecialRequest(std::string _specialRequest);
    static void saveMostItemOrdered(Order order);

    std::map<int, std::pair<std::shared_ptr<Item>, int>> getNumToUserOrderAndAmount() const;

    // raygui related method
    void drawCustomerOrder();
    static void drawAllOrder();


    // getter
    static std::string getMostOrderedItem();
    std::string getSpecialRequest();
    static float getTotalIncome();
    
};