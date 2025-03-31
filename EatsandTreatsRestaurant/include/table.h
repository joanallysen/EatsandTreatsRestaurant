#pragma once
#include "raylib.h"
#include "raygui.h"
//#include "order.h"
#include "currentmenu.h"
#include <vector>
#include <map>

// Enum for table occupancy status
enum class Occupancy {
    AVAILABLE,
    OCCUPIED,
    BOOKED
};

// Extern declaration of currentMenu
extern CurrentMenu currentMenu;

extern const int screenWidth;
extern const int screenHeight;
extern const int centerWidth;
extern const int centerHeight;




// Table class
class Table {
private:
    unsigned int tableNumber;
    Rectangle positionAndSize;
    Occupancy tableState;
    unsigned int seatingCapacity;
public:
    Table(float _posX = 0, float _posY = 0, float _width = 0, float _height = 0, Occupancy _condition = Occupancy::AVAILABLE);

    Rectangle getPositionAndSize() const;
    Occupancy getOccupancy() const;
    unsigned int getTableNumber() const;
};

class TableManager {
private:
    static std::map<unsigned int, Table> numToTables;
    static int currentTable;

public:
    static int getCurrentTable();
    static void initializeTables();  // Method to initialize tables
    static void drawTable(CurrentMenu afterHittingButton);
};

