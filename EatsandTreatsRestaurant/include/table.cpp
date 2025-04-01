#include "table.h"
#include <iostream>
#include <string>


Table::Table(unsigned int _tableNumber, unsigned int _seatingCapacity, Occupancy _condition)
    : tableState(_condition), seatingCapacity(_seatingCapacity), tableNumber(_tableNumber) {}


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

// number to tables map.
std::map<int, Table> TableManager::numToTables;

void TableManager::initializeTables() {
    numToTables[0] = (Table(1, 4, Occupancy::AVAILABLE));
    numToTables[1] = (Table(2, 2, Occupancy::AVAILABLE));
    numToTables[2] = (Table(3, 2, Occupancy::AVAILABLE));
    numToTables[3] = (Table(4, 2, Occupancy::AVAILABLE));
    numToTables[4] = (Table(5, 2, Occupancy::AVAILABLE));
    numToTables[5] = (Table(6, 3, Occupancy::AVAILABLE));
    numToTables[6] = (Table(7, 4, Occupancy::AVAILABLE));
    numToTables[7] = (Table(8, 4, Occupancy::AVAILABLE));
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
            if (GuiButton(Rectangle{float(centerWidth - (j * 200) + offset), float(centerHeight - i*200 + 400), 80, 80}, std::to_string(it->second.getTableNumber()).c_str())) {
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
