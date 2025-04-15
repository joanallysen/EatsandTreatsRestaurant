// This file is inspired by Raygui which don't have c++ and just go with it.
// unfortunately, I haven't saved the Order. Saving an object require json for modification.
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <memory>

#include "menu.h"
#include "table.h"

using namespace std;

class FileManager {
private:
	static const char* convertOccupancyToString(Occupancy occupancy) {
		static const char* enumStrings[] = { "AVAILABLE", "OCCUPIED", "BOOKED" };
		return enumStrings[static_cast<int>(occupancy)];
	}
public:
	// lots of this are hardcoded. and work specifically for this file and delimiter.
	static void loadMenuItem() {
		fstream menuFile("include/menuFile.txt");

		map<int, shared_ptr<Item>> tempNumToItems = {};
		int i = 0;

		if (!menuFile) {
			cout << "menu file is not opened" << endl;
			return;
		}

		string line{};
		vector<string> tempItemProperty;
		while (getline(menuFile, line)) {
			size_t start = 0;
			size_t end = line.find("&|");
			tempItemProperty = {};
			while (end != string::npos) {
				tempItemProperty.push_back(line.substr(start, end - start));
				start = end + 2; // delimiter size is 2
				end = line.find("&|", start);
			}
			tempItemProperty.push_back(line.substr(start));

			// the type
			if (tempItemProperty[3] == "special") {
				tempNumToItems[i++] = make_shared<Special>(tempItemProperty[0], tempItemProperty[1], stof(tempItemProperty[2]));
			}
			else if (tempItemProperty[3] == "food") {
				tempNumToItems[i++] = make_shared<Food>(tempItemProperty[0], tempItemProperty[1], stof(tempItemProperty[2]));
			}
			else if (tempItemProperty[3] == "drink") {
				tempNumToItems[i++] = make_shared<Drink>(tempItemProperty[0], tempItemProperty[1], stof(tempItemProperty[2]));
			}
		}

		menuFile.close();
		Menu::setMenuItem(tempNumToItems);
	}

	static void loadTable() {
		fstream tableFile("include/tableFile.txt");

		map<int, Table> tempNumToTables = {};
		int i = 0;

		if (!tableFile) {
			cout << "menu file is not opened" << endl;
			return;
		}

		string line{};
		vector<string> tempItemProperty;
		while (getline(tableFile, line)) {
			size_t start = 0;
			size_t end = line.find("&|");
			tempItemProperty = {};
			while (end != string::npos) {
				tempItemProperty.push_back(line.substr(start, end - start));
				start = end + 2; // delimiter size is 2
				end = line.find("&|", start);
			}
			tempItemProperty.push_back(line.substr(start));
			
			if (tempItemProperty[2] == "AVAILABLE") {
				tempNumToTables[i++] = Table(stoul(tempItemProperty[0]), stoul(tempItemProperty[1]), Occupancy::AVAILABLE);
			}
			else if (tempItemProperty[2] == "OCCUPIED") {
				tempNumToTables[i++] = Table(stoul(tempItemProperty[0]), stoul(tempItemProperty[1]), Occupancy::OCCUPIED);
			}
			else if (tempItemProperty[2] == "BOOKED") {
				tempNumToTables[i++] = Table(stoul(tempItemProperty[0]), stoul(tempItemProperty[1]), Occupancy::BOOKED);
			}
		}

		tableFile.close();
		TableManager::setTables(tempNumToTables);
	}

	static void saveMenuToFile() {
		cout << "saving the menu to file" << endl;
		ofstream menuFile("include/menuFile.txt");
		if (!menuFile) {
			cerr << "Failed to open file for writing!\n";
			return; // or handle errors
		}
		map<int, shared_ptr<Item>> tempNumToItems = Menu::getMenuItem();
		
		for (const auto& i : tempNumToItems) {
			menuFile << i.second->getName() << "&|" << i.second->getDescription() << "&|" << i.second->getPrice() << "&|";

			if (shared_ptr<Special> special = std::dynamic_pointer_cast<Special>(i.second)) {
				menuFile << "special" << endl;
			}else if(shared_ptr<Food> food = std::dynamic_pointer_cast<Food>(i.second)){
				menuFile << "food" << endl;
			}else if (shared_ptr<Drink> food = std::dynamic_pointer_cast<Drink>(i.second)) {
				menuFile << "drink" << endl;
			}
		}
		menuFile.close();
	}

	static void saveTableToFile() {
		cout << "saving the table to file" << endl;
		ofstream tableFile("include/tableFile.txt");
		if (!tableFile) {
			std::cerr << "Failed to open file for writing!\n";
			return; // or handle error
		}
		map<int, Table> tempNumToTables = TableManager::getTables();
		for (const auto& i : tempNumToTables) {
			tableFile << i.second.getTableNumber() << "&|" << i.second.getCapacity() << "&|" << convertOccupancyToString(i.second.getOccupancy()) << endl;
		}
		tableFile.close();
	}
};

// json. 
// table [1]{} table[2]{} menu[]{}[]{}[]{}
