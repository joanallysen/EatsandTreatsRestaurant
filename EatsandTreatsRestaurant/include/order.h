#pragma once
#include <unordered_map>
#include <string>

class Order {
    unordered_map<std::string, float> orderedItemToPrice{};
    std::string specialRequest{};

public:
    // add order and remove order is already in the toggle box ray gui
    void editOrder() {};
    void cancelOrder() {};
};