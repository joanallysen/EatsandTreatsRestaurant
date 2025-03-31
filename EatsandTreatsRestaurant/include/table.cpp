#include "table.h"
#include <iostream>
#include <string>


Table::Table(float _posX, float _posY, float _width, float _height, unsigned int _tableNumber, Occupancy _condition)
    : positionAndSize{ _posX, _posY, _width, _height }, tableState(_condition), tableNumber(_tableNumber) {}

// Get position and size of the table
Rectangle Table::getPositionAndSize() const {
    return positionAndSize;
}

// Get table occupancy status
Occupancy Table::getOccupancy() const {
    return tableState;
}

unsigned int Table::getTableNumber() const {
    return tableNumber;
}

void Table::setTableNumber(unsigned int _tableNumber) {
    tableNumber = _tableNumber;
}

void Table::setOccupancy(unsigned int _capacity) {
    seatingCapacity = _capacity;
}

void TableManager::initializeTables() {
    numToTables[1] = (Table(centerWidth - 200 - 40, centerHeight - 200, 80, 80, 1));
    numToTables[2] = (Table(centerWidth - 40, centerHeight - 200, 80, 80, 2));
    numToTables[3] = (Table(centerWidth + 200 - 40, centerHeight - 200, 80, 80, 3));
    numToTables[4] = (Table(centerWidth - 200 - 40, centerHeight, 80, 80, 4));
    numToTables[5] = (Table(centerWidth - 40, centerHeight, 80, 80, 5));
    numToTables[6] = (Table(centerWidth + 200 - 40, centerHeight, 80, 80, 6));
    numToTables[7] = (Table(centerWidth - 200 - 40, centerHeight + 200, 80, 80, 7));
    numToTables[8] = (Table(centerWidth - 40, centerHeight + 200, 80, 80, 8));
}

void TableManager::drawTable(CurrentMenu afterHittingButton) {
    int gap = 400;
    for (const auto& table : numToTables) {
        if (GuiButton(table.second.getPositionAndSize(), std::to_string(table.second.getTableNumber()).c_str())) {
            currentTable = table.second;
            currentMenu = afterHittingButton;
        }
    }
}
Table TableManager::currentTable = -1;
Table TableManager::getCurrentTable() {
    return currentTable;
}
std::map<unsigned int, Table> TableManager::numToTables;