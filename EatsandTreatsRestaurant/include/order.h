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
    static float totalIncome;
    std::string specialRequest;
    // key to {item object, amount}
    // items and amount ordered
    std::map<int, std::pair<std::shared_ptr<Item>, int>> numToUserOrderAndAmount;
    // item name to {item object, amount}
    // all item and the amount ordered
    static std::map<std::string, std::pair<std::shared_ptr<Item>, int>> itemToAmountOrdered;

public:
    // setter
    void addOrder(std::shared_ptr<Item> item);
    void reduceOrder(std::shared_ptr<Item> item);
    void addToTotalIncome();
    void setSpecialRequest(std::string _specialRequest);
    static void saveMostItemOrdered(Order order);

    // get user and the amount
    std::map<int, std::pair<std::shared_ptr<Item>, int>> getNumToUserOrderAndAmount() const;

    // raygui related method
    void drawCustomerOrder();
    static void drawAllOrderReport();


    // getter
    static std::string getMostOrderedItem();
    std::string getSpecialRequest();
    static float getTotalIncome();
    
};