#include "order.h";

using namespace std;

map<int, pair<shared_ptr<Item>, int>> numToUserOrderAndAmount = {};
map<string, pair<shared_ptr<Item>, int>> Order::itemToAmountOrdered = {};
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

void Order::setSpecialRequest(std::string _specialRequest) {
	specialRequest = _specialRequest;
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
	DrawText("Special Request", centerWidth - MeasureText("Special Request", 20) / 2, centerHeight + i * gap - 200, 20, BLACK);
	GuiLabel(Rectangle{ float(centerWidth - 350), float(centerHeight) + i * gap - 150, 450, 40 }, (specialRequest).c_str());
}

void Order::drawAllOrder() {
	// col offset
	int col1 = -650; int col2 = -150; int col3 = 200; int col4 = 500;
	int gap = 60;
	int i = 0;
	GuiLabel(Rectangle{ float(centerWidth + col1), float(centerHeight) + i * gap - 400, 450, 40 }, ("Item"));
	GuiLabel(Rectangle{ float(centerWidth + col2), float(centerHeight) + i * gap - 400, 450, 40 }, ("Amount"));
	GuiLabel(Rectangle{ float(centerWidth) + col3, float(centerHeight) + i * gap - 400, 450, 40 }, ("Individual Price"));
	GuiLabel(Rectangle{ float(centerWidth + col4), float(centerHeight) + i * gap - 400, 450, 40 }, ("Total"));
	i = 1;
	float todayTotalPrice = 0;
	string todayPriceText = "";
	int totalAmount = 0;
	for (const auto& item : itemToAmountOrdered) {
		GuiLabel(Rectangle{ float(centerWidth + col1), float(centerHeight) + i * gap - 400, 450, 40 }, (item.first.c_str()));
		GuiLabel(Rectangle{ float(centerWidth + col2), float(centerHeight) + i * gap - 400, 450, 40 }, (to_string(item.second.second).c_str()));
		totalAmount += item.second.second;
		float price = item.second.first->getPrice();
		string priceText = "$" + Util::formatFloat(price);
		GuiLabel(Rectangle{ float(centerWidth) + col3, float(centerHeight) + i * gap - 400, 450, 40 }, (priceText).c_str());
		string totalPrice = "$" + Util::formatFloat(price * item.second.second);
		GuiLabel(Rectangle{ float(centerWidth + col4), float(centerHeight) + i * gap - 400, 450, 40 }, (totalPrice).c_str());
		todayTotalPrice += (price * item.second.second);
		todayPriceText = "$" + Util::formatFloat(todayTotalPrice);
		i++;
	}
	i += 2;
	GuiLabel(Rectangle{ float(centerWidth + col1), float(centerHeight) + i * gap - 400, 450, 40 }, ("Total Income : "));
	GuiLabel(Rectangle{ float(centerWidth + col4), float(centerHeight) + i * gap - 400, 450, 40 }, (todayPriceText.c_str()));

	i++;
	GuiLabel(Rectangle{ float(centerWidth + col1), float(centerHeight) + i * gap - 400, 450, 40 }, ("Number of Order Today :"));
	GuiLabel(Rectangle{ float(centerWidth + col4), float(centerHeight) + i * gap - 400, 450, 40 }, (to_string(totalAmount).c_str()));

	i++;
	GuiLabel(Rectangle{ float(centerWidth + col1), float(centerHeight) + i * gap - 400, 450, 40 }, ("Most Ordered Item Of The Day :"));
	GuiLabel(Rectangle{ float(centerWidth + col4), float(centerHeight) + i * gap - 400, 450, 40 }, (getMostOrderedItem().c_str()));

	i++;
	if (todayTotalPrice < 999) {
		GuiLabel(Rectangle{ float(centerWidth + col1), float(centerHeight) + i * gap - 400, 1400, 40 }, ("Sales are below target and underperforming, consider trying different strategies and aprroach"));
	}
	else if (todayTotalPrice < 1799) {
		GuiLabel(Rectangle{ float(centerWidth + col1), float(centerHeight) + i * gap - 400, 1400, 40 }, ("Sales are average and have hit expected value, steady performance with room for growth"));
	}
	else {
		GuiLabel(Rectangle{ float(centerWidth + col1), float(centerHeight) + i * gap - 400, 1400, 40 }, ("Sales exceeded typical levels, marking a high performance day, great work maintaining customer flow and service"));
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

string Order::getMostOrderedItem() {
	if (itemToAmountOrdered.empty()) { return " "; }
	pair<shared_ptr<Item>, int> itemAndAmount = {};
	for (const auto& item : itemToAmountOrdered) {
		if (itemAndAmount.second <= item.second.second) {
			itemAndAmount = item.second;
		}
	}
	return itemAndAmount.first->getName();
}

string Order::getSpecialRequest() {
	return specialRequest;
}

void Order::saveMostItemOrdered(Order order) {

	//debug
	for (const auto& i : order.getNumToUserOrderAndAmount()) {
		if (itemToAmountOrdered.find(i.second.first->getName()) != itemToAmountOrdered.end()) {
			itemToAmountOrdered[i.second.first->getName()].second += i.second.second;
		}
		else {
			itemToAmountOrdered[i.second.first->getName()] = i.second;
		}
	}

	// debug..
	cout << "Current All Report : ";
	for (const auto& i : itemToAmountOrdered) {
		cout << i.first << " $" << i.second.first->getPrice() << " " << i.second.second << endl;
	}
}
