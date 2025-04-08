#include "order.h"

using namespace std;

map<int, shared_ptr<Item>> numToUserOrder = {};
void Order::addOrder(std::shared_ptr<Item> item) {
	numToUserOrder[numToUserOrder.size()] = item;
}

