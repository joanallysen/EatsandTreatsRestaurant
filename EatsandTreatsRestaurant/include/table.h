/*
Menu and Table have a different process, where Menu uses pointer to save 
the data, but Table uses class. 

Both have their own advantage and disadvantages
Using pointer as variable
Advantage -> Able to uses function inside object more easily.
Disadvantage -> More complex syntax and reduce readability

Using class as variable
Advantage -> More readable, and simpler to understand
Disadvatage -> Every table have to be adjusted from a different class (TableManager)

*/

#pragma once
#include "raylib.h"
#include "raygui.h"

#include "currentmenu.h"
#include "order.h"
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <unordered_map>

// enum for table occupancy status
enum class Occupancy {
    AVAILABLE,
    OCCUPIED,
    BOOKED
};

// extern declaration of currentMenu
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
    std::string symbol;
    Order order;

public:
    Table(unsigned int tableNumber = 1, unsigned int seatingCapacity = 1, Occupancy condition = Occupancy::AVAILABLE, std::string _symbol = "+");

    Occupancy getOccupancy() const;
    unsigned int getTableNumber() const;
    unsigned int getCapacity() const;
    std::string getSymbol() const;
    
    // only usable by tableManager. One of the downside of not using pointer.
    void setSymbol();
    void setTableNumber(unsigned int _tableNumber);
    void setCapacity(unsigned int _capacity);
    void setOccupancy(Occupancy _occupancy);
    void bookTable();

    // order execution.
    void setTableOrder(Order order);
    Order getTableOrder() const;
};

class TableManager {
private:
    static std::map<int, Table> numToTables;
    static Table currentTable;
    static unsigned int currentTableIndex;

public:
    
    // for file manager.
    static void setTables(std::map<int, Table> tempNumToTables);
    static std::map<int, Table> getTables();

    static void drawTable(CurrentMenu afterHittingButton);
    
    // current table editing method
    static Table getCurrentTable();
    static void addTable();
    static void deleteTable();
    static void updateTableNumber(unsigned int newTableNumber);
    static void updateTableCapacity(unsigned int newTableCapacity);
    static void bookCurrentTable();
    static Occupancy getCurrentOccupation();

    // order execution
    static void updateCurrentTableOrder(Order order);
    static Order getCurrentTableOrder();
    static void debugCurrentTableOrder();
    static void serveTableOrder();
};
