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
char tableStateInput[100] = "";
char tableNumberInput[100] = "";
char seatingCapacityInput[100] = "";
void tableEditorProcess() {
    if (!exitWindow) {
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        exitWindow = GuiWindowBox(Rectangle{ 50,50,screenWidth - 100, screenHeight - 100 }, "#198# Process");
        string text = "Table number " + to_string(TableManager::getCurrentTable());
        DrawText(text.c_str(), centerWidth - MeasureText(text.c_str(), 58) / 2, centerHeight - 300, 58, BLACK);
        if (GuiTextBox(Rectangle{ centerWidth, centerHeight, 200, 100 }, tableStateInput, sizeof(100), true)) {
            cout << tableStateInput << endl;
        }
        if (GuiTextBox(Rectangle{ centerWidth, centerHeight - 80, 200, 100 }, tableNumberInput, sizeof(100), true)) {
            // This gets triggered when the text box content changes
            // You can add any logic you want here
        }
        if (GuiTextBox(Rectangle{ centerWidth, centerHeight - 160, 200, 100 }, seatingCapacityInput, sizeof(100), true)) {
            // This gets triggered when the text box content changes
            // You can add any logic you want here
        }
    }
    else {
        exitWindow = false;
        currentMenu = MAIN_MENU;
    }
}



void tableEditorProcessTwo() {
    if (!exitWindow) {
        ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
        exitWindow = GuiWindowBox(Rectangle{ 50,50,screenWidth - 100, screenHeight - 100 }, "#198# Process");
        string text = "You have pick table number " + TableManager::getCurrentTable();
        DrawText(text.c_str(), centerWidth - MeasureText(text.c_str(), 58) / 2, centerHeight - 300, 58, BLACK);
        if (GuiTextBox(Rectangle { centerWidth, centerHeight, 200, 100 }, tableStateInput, sizeof(100), true)) {
            cout << tableStateInput << endl;
        }
        if (GuiTextBox(Rectangle { centerWidth, centerHeight - 80, 200, 100 }, tableNumberInput, sizeof(100), true)) {
            // This gets triggered when the text box content changes
            // You can add any logic you want here
        }
        if (GuiTextBox(Rectangle { centerWidth, centerHeight - 160, 200, 100 }, seatingCapacityInput, sizeof(100), true)) {
            // This gets triggered when the text box content changes
            // You can add any logic you want here
        }
        TableManager::drawTable(TABLE_EDITOR_PROCESS);
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
        if (toggleState1 == true) {
            cout << "THE FIRST ONE IS ACTIVATED!!";
        }
        if (toggleState2 == true) {
            cout << "THE SECOND ONE IS ACTIVATED!!";
        }


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
            case CurrentMenu::TABLE_EDITOR_PROCESS_TWO:
                tableEditorProcessTwo();
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