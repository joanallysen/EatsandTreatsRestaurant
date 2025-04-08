#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include <map>
#include "menu.h"

class Item;
class Order {
private:
    std::string specialRequest{};

public:
    std::map<int, std::shared_ptr<Item>> numToUserOrder;
    void addOrder(std::shared_ptr<Item> item);
};