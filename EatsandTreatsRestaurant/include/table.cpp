#include "table.h"
#include <iostream>
#include <string>


Table::Table(float _posX, float _posY, float _width, float _height, Occupancy _condition)
    : positionAndSize{ _posX, _posY, _width, _height }, tableState(_condition) {}

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

void TableManager::initializeTables() {
    numToTables[1] = (Table(centerWidth - 200 - 40, centerHeight - 200, 80, 80));
    numToTables[2] = (Table(centerWidth - 40, centerHeight - 200, 80, 80));
    numToTables[3] = (Table(centerWidth + 200 - 40, centerHeight - 200, 80, 80));
    numToTables[4] = (Table(centerWidth - 200 - 40, centerHeight, 80, 80));
    numToTables[5] = (Table(centerWidth - 40, centerHeight, 80, 80));
    numToTables[6] = (Table(centerWidth + 200 - 40, centerHeight, 80, 80));
    numToTables[7] = (Table(centerWidth - 200 - 40, centerHeight + 200, 80, 80));
    numToTables[8] = (Table(centerWidth - 40, centerHeight + 200, 80, 80));
}

void TableManager::drawTable(CurrentMenu afterHittingButton) {
    int gap = 400;
    for (const auto& table : numToTables) {
        if (GuiButton(table.second.getPositionAndSize(), std::to_string(table.first).c_str())){
            currentTable = table.first;
            currentMenu = afterHittingButton;
        }
    }
}
int TableManager::currentTable = -1;
int TableManager::getCurrentTable() {
    return currentTable;
}
std::map<unsigned int, Table> TableManager::numToTables;