# include "order.h"

using namespace std;

map<int, pair<shared_ptr<Item>, int>> numToUserOrderAndAmount = {};
unordered_map<shared_ptr<Item>, int >> itemToAmountOrdered = {};
float Order::totalIncome = 0;
void Order::addOrder(std::shared_ptr<Item> newItem) {
	for (auto &item : numToUserOrderAndAmount) {
		if (item.second.first == newItem) {
			item.second.second += 1;
			return;
		}
	}
	if (numToUserOrderAndAmount.size() == 0) {
		numToUserOrderAndAmount[0] = { newItem, 1 };
		return;
	}
	numToUserOrderAndAmount.insert({ { numToUserOrderAndAmount.rbegin()->first + 1 }, { newItem, 1 } });
}

void Order::reduceOrder(std::shared_ptr<Item> itemToBeReduced) {
	for (auto& item : numToUserOrderAndAmount) {
		if (item.second.first == itemToBeReduced) {
			item.second.second -= 1;
			if (item.second.second == 0) {
				numToUserOrderAndAmount.erase(item.first);
			}
			return;
		}
	}
}


map<int, pair<shared_ptr<Item>, int>> Order::getNumToUserOrderAndAmount() const{
	return numToUserOrderAndAmount;
}

void Order::drawCustomerOrder() {
	int gap = 80;
	int i = 0;
	for (const auto& item : numToUserOrderAndAmount) {
		GuiLabel(Rectangle{ float(centerWidth - 350), float(centerHeight) + i * gap - 200, 450, 40 }, (item.second.first->getName().c_str()));
		GuiLabel(Rectangle{ float(centerWidth + 300), float(centerHeight) + i * gap - 200, 450, 40 }, (to_string(item.second.second).c_str()));
		i++;
	}
}

void Order::addToTotalIncome() {
	for (const auto& item : numToUserOrderAndAmount) {
		totalIncome += item.second.first->getPrice() * item.second.second;
	}
	cout << "Total Income Currently: " << totalIncome << endl;
}

float Order::getTotalIncome() {
	return totalIncome;
}

float Order::saveMostItemOrdered() {
	// loop through and jsut add them to the unordered map.
}
