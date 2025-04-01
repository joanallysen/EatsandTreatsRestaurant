#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

#include "raylib.h"
#include "include\table.h"
#include "include\menu.h"
//#include "include\order.h"
#include "include\currentmenu.h"

#define RAYGUI_IMPLEMENTATION
#include "include\raygui.h"


const int screenWidth = 1920;
const int screenHeight = 1080;
const int centerWidth = screenWidth / 2;
const int centerHeight = screenHeight / 2;

const int tableOffsetWidth = 200;


CurrentMenu currentMenu = MAIN_MENU;

bool is_number(const string& s) {
    string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) {
        it++;
    }
    return !s.empty() && it == s.end();
}



class Menu {
    string itemName{};
    string description{};
    float prices{};
};

bool toggleState1 = false;
bool toggleState2 = false;
bool exitOrderWindow = false;
void orderMenu() {
    if (!exitOrderWindow) {
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        exitOrderWindow = GuiWindowBox(Rectangle{ 50,50,900,900 }, "#198# Order Menu");

        if (GuiToggle(Rectangle{ 100, 100, 200, 40 }, toggleState1 ? "ON" : "OFF", &toggleState1)) {
            toggleState1 = !toggleState1;
        }
    }
    else {
        exitOrderWindow = false;
        currentMenu = FRONT_OF_HOUSE;
    }
}

bool exitWindow = false;
void frontOfHouseProcess() {
    
    if (!exitWindow) {
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        exitWindow = GuiWindowBox(Rectangle{ 50,50,screenWidth - 100, screenHeight - 100}, "#198# Process");
        if (GuiButton(Rectangle{ centerWidth - 100, centerHeight, 200, 40 }, "ORDER")) {
            exitWindow = false;
            currentMenu = ORDER_MENU;
        }
        if (GuiButton(Rectangle{ centerWidth - 100, centerHeight + 100, 200, 40 }, "BOOK")) {

        }
    }
    else {
        exitWindow = false;
        currentMenu = FRONT_OF_HOUSE;
    }
}

void frontOfHouse(){
    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
    GuiSetStyle(DEFAULT, TEXT_SIZE, 30);
    GuiSetStyle(BUTTON, RAYGUI_MESSAGEBOX_BUTTON_HEIGHT, 400);

    DrawText("Click one of the table to assign or book seat to new customer", centerWidth - MeasureText("Click one of the table to assign or book seat to new customer", 24) / 2, centerHeight - 300, 24, BLACK);

    TableManager::drawTable(FRONT_OF_HOUSE_PROCESS);

}

void kitchenStaff() {

}


const int maxInputBox = 2;  // number of input boxes
char inputs[maxInputBox][64] = { "" };  // 2 box 64 letter each
bool editMode[maxInputBox] = { false }; // fill all element with false

void tableEditorProcess() {
    if (!exitWindow) {
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        exitWindow = GuiWindowBox(Rectangle{ 50,50,screenWidth - 100, screenHeight - 100 }, "#198# Table Edit Process");
        Table currentTable = TableManager::getCurrentTable();

        string numberText = "Table number " + to_string(currentTable.getTableNumber());
        DrawText(numberText.c_str(), centerWidth - MeasureText(numberText.c_str(), 58) / 2, centerHeight - 300, 58, BLACK);
        string capacityText = "Table capacity  " + to_string(currentTable.getCapacity());
        DrawText(capacityText.c_str(), centerWidth - MeasureText(capacityText.c_str(), 58) / 2, centerHeight - 220, 58, BLACK);
        DrawText("Please click enter after inputting", centerWidth - MeasureText("Please click enter after inputting", 22)/2, centerHeight - 160, 22, BLACK);

        DrawText("New Table Number: ", centerWidth - MeasureText("New Table Number: ", 24) / 2 - 160, centerHeight - 70, 24, BLACK);
        DrawText("New Seating Capacity: ", centerWidth - MeasureText("New Seating Capacity: ", 24) / 2 - 160, centerHeight, 24, BLACK);
        for (int i = 0; i < maxInputBox; i++) { 
            Rectangle box = { centerWidth + 180 - 150, centerHeight - (i * 80), 300, 50 };

            // If clicked, toggle editing mode
            if (GuiTextBox(box, inputs[i], 64, editMode[i])) { // make the 3 boxes with all edit mode being false, if clicked it will see what box have been clicked(j) and put it to editmode.
                for (int j = 0; j < maxInputBox; j++) {
                    if (i == j){
                        editMode[j] = true;
                    }else {
                        editMode[j] = false;
                    }
                    
                }
            }

            if (i == 0 && IsKeyPressed(KEY_ENTER)) {

                TableManager::updateTableCapacity(strtoul(inputs[i], nullptr, 10));
                cout << "THE CAPACITYYYY" << inputs[i];
            }
            else if (i == 1 && IsKeyPressed(KEY_ENTER)) {
                // convert char * to unsigned int using strtoul
                TableManager::updateTableNumber(strtoul(inputs[i], nullptr, 10));
                cout << "TABLE NUMBERRRR" << inputs[i];
            }
        }

        if (GuiButton(Rectangle{ centerWidth - 550, centerHeight + 300, 200, 40 }, "DELETE")) {
            for (int i = 0; i < maxInputBox; i++) { inputs[i][0] = '\0'; }
            TableManager::deleteTable();
            currentMenu = TABLE_EDITOR;
        }

        if (GuiButton(Rectangle{ centerWidth + 400, centerHeight + 300, 200, 40 }, "EXIT")) {
            for (int i = 0; i < maxInputBox; i++) { inputs[i][0] = '\0'; }
            currentMenu = TABLE_EDITOR;
        }
    }
    else {
        exitWindow = false;
        currentMenu = MAIN_MENU;
    }
}



void tableEditor() {
    if (!exitWindow) {
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        exitWindow = GuiWindowBox(Rectangle{ 50,50,screenWidth - 100, screenHeight - 100 }, "#198# Process");
        DrawText("Please pick a table to edit", centerWidth - MeasureText("Please pick a table to edit", 58) / 2, centerHeight - 300, 58, BLACK);
        TableManager::drawTable(TABLE_EDITOR_PROCESS);

        if (GuiButton(Rectangle{ centerWidth - 400, centerHeight + 400, 800, 50 }, "Add new Table")) {
            TableManager::addTable();
        }
    }
    else {
        exitWindow = false;
        currentMenu = MAIN_MENU;
    }
}

void menuEditor() {

}

void editorMenu() {
    if (!exitWindow) {
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        exitWindow = GuiWindowBox(Rectangle{ 50,50,screenWidth - 100, screenHeight - 100 }, "#198# Process");
        DrawText("What do you want to edit?", centerWidth - MeasureText("What do you want to edit?", 58) / 2, centerHeight - 300, 58, BLACK);
        if (GuiButton(Rectangle{ centerWidth - 100, centerHeight, 200, 40 }, "TABLE")) {
            exitWindow = false;
            currentMenu = TABLE_EDITOR;
        }
        if (GuiButton(Rectangle{ centerWidth - 100, centerHeight + 100, 200, 40 }, "MENU")) {
            exitWindow = false;
            currentMenu = EDITOR;
        }
    }
    else {
        exitWindow = false;
        currentMenu = MAIN_MENU;
    }
}

void mainMenu() {
    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
    GuiSetStyle(DEFAULT, TEXT_SIZE, 30);

    DrawText("Eats and Treats", centerWidth - MeasureText("Eats and Treats", 58) / 2, centerHeight - 300, 58, BLACK);
    if (GuiButton(Rectangle{ centerWidth - 400, centerHeight + 80, 800, 50 }, "Front Of House")) {
        currentMenu = FRONT_OF_HOUSE;
    }


    if (GuiButton(Rectangle{ centerWidth - 400, centerHeight, 800, 50 }, "Kitchen Staff")) {
        currentMenu = KITCHEN_STAFF;
    }

    if (GuiButton(Rectangle{ centerWidth - 400, centerHeight + 160, 800, 50 }, "Editor")) {
        currentMenu = EDITOR;
    }
}

void update() {
    while (!WindowShouldClose())
    {
        //debug
        /*if (toggleState1 == true) {
            cout << "THE FIRST ONE IS ACTIVATED!!";
        }
        if (toggleState2 == true) {
            cout << "THE SECOND ONE IS ACTIVATED!!";
        }*/
        //cout << nameof(TableManager::getCurrentTable().getOccupancy()) << endl;
        //cout << TableManager::getCurrentTable().getTableNumber() << endl;


        BeginDrawing();
        switch (currentMenu) {
            case CurrentMenu::MAIN_MENU:
                mainMenu();
                break;
            case CurrentMenu::FRONT_OF_HOUSE:
                frontOfHouse();
                break;
            case CurrentMenu::FRONT_OF_HOUSE_PROCESS:
                frontOfHouseProcess();
                break;
            case CurrentMenu::KITCHEN_STAFF:
                kitchenStaff();
                break;
            case CurrentMenu::ORDER_MENU:
                orderMenu();
                break;
            case CurrentMenu::EDITOR:
                editorMenu();
                break;
            case CurrentMenu::TABLE_EDITOR:
                tableEditor();
                break;
            case CurrentMenu::MENU_EDITOR:
                editorMenu();
                break;
            case CurrentMenu::TABLE_EDITOR_PROCESS:
                tableEditorProcess();
                break;
            default:
                break;
        }
        
        EndDrawing();
    }
    CloseWindow();
}



int main()
{
    // im adjusting so it is similar to unity where it used start() and update()
    //APP PREPARATION
    TableManager::initializeTables();
    InitWindow(screenWidth, screenHeight, "Eats and Treats");
    SetTargetFPS(60);
    update();

    return 0;
}

/*if (showMessageBox)
        {
            int result = GuiMessageBox(Rectangle{ centerWidth - 400, centerHeight - 400, 800, 800 },
                "#191#Message Box", "Hi! This is a message!", "Nice;Cool");

            if (result >= 0) showMessageBox = false;
        }*/