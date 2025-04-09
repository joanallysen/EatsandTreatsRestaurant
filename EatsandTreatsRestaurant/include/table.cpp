#include "table.h"

#include <iostream>
#include <string>


Table::Table(unsigned int _tableNumber, unsigned int _seatingCapacity, Occupancy _condition, std::string _symbol)
    : tableState(_condition), seatingCapacity(_seatingCapacity), tableNumber(_tableNumber), symbol(_symbol) {
    setSymbol();
}

void Table::setSymbol() {
    if (tableState == Occupancy::AVAILABLE) {
        symbol = "+";
    }else if (tableState == Occupancy::OCCUPIED){
        symbol = "x";
    } else if (tableState == Occupancy::BOOKED) {
        symbol = "-";
    }
}

std::string Table::getSymbol() const {
    return symbol;
}
// Get table occupancy status
Occupancy Table::getOccupancy() const {
    return tableState;
}

unsigned int Table::getCapacity() const {
    return seatingCapacity;
}

unsigned int Table::getTableNumber() const {
    return tableNumber;
}

void Table::setTableNumber(unsigned int _tableNumber) {
    tableNumber = _tableNumber;
}

void Table::setCapacity(unsigned int _capacity) {
    seatingCapacity = _capacity;
}

void Table::setOccupancy(Occupancy _occupancy) {
    tableState = _occupancy;
    setSymbol();
}
void Table::bookTable() {
    std::cout << "bookTable" << std::endl;
    tableState = Occupancy::BOOKED;
    setSymbol();
}

// order execution
void Table::setTableOrder(Order _order) {
    order = _order;
}

Order Table::getTableOrder() const{
    return order;
}





// number to tables map.
std::map<int, Table> TableManager::numToTables;

void TableManager::setTables(std::map<int, Table> tempNumToTables) {
    numToTables = tempNumToTables;
}

std::map<int, Table> TableManager::getTables() {
    return numToTables;
}
// this function also update the current table that the user is looking.
void TableManager::drawTable(CurrentMenu afterHittingButton) {
    int row = 3; int col = 3;
    int offset = 350; int gap = 40;
    if (numToTables.size() > 9) { col = 5; offset = 550; }
    if (numToTables.size() > 15) { col = 7; offset = 750; }

    Rectangle buttonRect = { centerWidth - offset - gap, centerHeight - offset - (gap * 2) };

    std::map<int, Table>::iterator it = numToTables.begin();
    for (int i = row; i > 0; i--)
    {
        for (int j = col; j > 0; j--) {
            if (it == numToTables.end()) return;
            if (GuiButton(Rectangle{float(centerWidth - (j * 200) + offset), float(centerHeight - i*200 + 400), 80, 80}, (it->second.getSymbol()).c_str())) {
                currentTable = it->second;
                currentTableIndex = it->first;
                currentMenu = afterHittingButton;
            }
            it++;
        }
    }
}
Table TableManager::currentTable = -1;
unsigned int TableManager::currentTableIndex = -1;

// return the table that user is looking on.
Table TableManager::getCurrentTable() { // return current Table that user want to see the info of
    return numToTables[currentTableIndex];
}

void TableManager::updateTableNumber(unsigned int newTableNumber) {
    std::cout << "Updating table #" << currentTableIndex << " number to: " << newTableNumber << std::endl;
    numToTables[currentTableIndex].setTableNumber(newTableNumber);
}

void TableManager::updateTableCapacity(unsigned int newTableCapacity) {
    std::cout << "Updating table #" << currentTableIndex << " capacity to: " << newTableCapacity << std::endl;
    numToTables[currentTableIndex].setCapacity(newTableCapacity);
}

void TableManager::addTable() {
    std::cout << "A new table is added, index: " << numToTables.size() << std::endl;

    numToTables.insert({ numToTables.rbegin()->first + 1, Table(0, 4, Occupancy::AVAILABLE)});
    
}

void TableManager::deleteTable() {
    std::cout << currentTableIndex << std::endl;
    numToTables.erase(currentTableIndex);
}

void TableManager::bookCurrentTable() {
    std::cout << currentTableIndex << "booking..." << std::endl;
    numToTables[currentTableIndex].bookTable();
    numToTables[currentTableIndex].setOccupancy(Occupancy::BOOKED);
}

Occupancy TableManager::getCurrentOccupation() {
    return numToTables[currentTableIndex].getOccupancy();
}

void TableManager::updateCurrentTableOrder(Order order) {
    std::cout << "Adding order... table manager" << std::endl;
    numToTables[currentTableIndex].setTableOrder(order);
    debugCurrentTableOrder();
    numToTables[currentTableIndex].setOccupancy(Occupancy::OCCUPIED);
}

void TableManager::debugCurrentTableOrder() {
    std::cout << "Current Item Inside Table Index:  " << currentTableIndex << std::endl;
    for (const auto& i : numToTables[currentTableIndex].getTableOrder().getNumToUserOrderAndAmount()) {
        std::cout << i.second.first->getName() << " " << i.second.second << " " << std::endl;
    }
}

Order TableManager::getCurrentTableOrder() {
    return numToTables[currentTableIndex].getTableOrder();
}

void TableManager::serveTableOrder() {
    numToTables[currentTableIndex].getTableOrder().addToTotalIncome();
    numToTables[currentTableIndex].setOccupancy(Occupancy::AVAILABLE);
    numToTables[currentTableIndex].setTableOrder(Order());
}