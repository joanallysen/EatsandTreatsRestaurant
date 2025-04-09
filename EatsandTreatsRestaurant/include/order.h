#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include <map>
#include "item.h"
#include "raygui.h"
#include "raylib.h"
#include <unordered_map>

extern const int screenWidth;
extern const int screenHeight;
extern const int centerWidth;
extern const int centerHeight;

class Order {
private:
    std::string specialRequest;
    static float totalIncome;
    static std::unordered_map<std::shared_ptr<Item>, int> itemToAmountOrdered;

public:
    std::map<int, std::pair<std::shared_ptr<Item>, int>> numToUserOrderAndAmount;
    void addOrder(std::shared_ptr<Item> item);
    void reduceOrder(std::shared_ptr<Item> item);
    std::map<int, std::pair<std::shared_ptr<Item>, int>> getNumToUserOrderAndAmount() const;
    void drawCustomerOrder();
    void addToTotalIncome();


    static float getTotalIncome();
    static float saveMostItemOrdered();
};