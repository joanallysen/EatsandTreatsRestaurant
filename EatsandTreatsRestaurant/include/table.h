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
    Occupancy tableState;
    unsigned int seatingCapacity;

public:
    Table(unsigned int tableNumber = 1, unsigned int seatingCapacity = 1, Occupancy _condition = Occupancy::AVAILABLE);

    Occupancy getOccupancy() const;
    unsigned int getTableNumber() const;
    unsigned int getCapacity() const;
    void setTableNumber(unsigned int _tableNumber);
    void setCapacity(unsigned int _capacity);
};

class TableManager {
private:
    static std::map<int, Table> numToTables;
    static Table currentTable;
    static unsigned int currentTableIndex;

public:
    static Table getCurrentTable();
    static void initializeTables();  // Method to initialize tables
    static void drawTable(CurrentMenu afterHittingButton);
    static void updateTableNumber(unsigned int newTableNumber);
    static void updateTableCapacity(unsigned int newTableCapacity);
    static void addTable();
    static void deleteTable();
};

