#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct InventoryItem {
    int uniqueCode;
    char itemName[50];
    int departmentID;
    int isWorking;
};

struct Department {
    int departmentID;
    char departmentName[50];
    int itemCount;
    InventoryItem items[100]; // Assuming maximum 100 items per department
};

Department departments[10]; // Assuming maximum 10 departments

int totalDepartments = 0;
int totalInventoryItems = 0;

int generateUniqueCode() {
    static int code = 1000; // Starting from 1000
    return code++;
}

void issueInventoryItem(int departmentID, const char* itemName) {
    
    if (totalDepartments < 10) {
       int uniqueCode = generateUniqueCode();

        InventoryItem newItem;
        newItem.uniqueCode = uniqueCode;
        strcpy(newItem.itemName, itemName);
        newItem.departmentID = departmentID;
        newItem.isWorking = 1;

        departments[departmentID].items[departments[departmentID].itemCount] = newItem;
        departments[departmentID].itemCount++;

        totalInventoryItems++;

        cout << "Inventory item '" << itemName << "' with unique code " << uniqueCode
                  << " issued to department " << departments[departmentID].departmentName << ".\n";
    } else {
        cout << "Maximum number of departments reached.\n";
    }
}

void registerComplaint(int uniqueCode) {
    for (int i = 0; i < totalDepartments; i++) {
        for (int j = 0; j < departments[i].itemCount; j++) {
            if (departments[i].items[j].uniqueCode == uniqueCode) {
                departments[i].items[j].isWorking = 0;
                std::cout << "Complaint registered for inventory item with unique code " << uniqueCode << ".\n";
                return;
            }
        }
    }
    std::cout << "Inventory item with unique code " << uniqueCode << " not found.\n";
}

void printDepartmentInventory(int departmentID) {
    cout << "Inventory items issued to department " << departments[departmentID].departmentName << ":\n";
    for (int i = 0; i < departments[departmentID].itemCount; i++) {
        cout << "Unique Code: " << departments[departmentID].items[i].uniqueCode
             << ", Item: " << departments[departmentID].items[i].itemName
             << ", Working: " << (departments[departmentID].items[i].isWorking ? "Yes" : "No") << '\n';
    }
}

void countInventoryItems() {
    int itemCounts[7] = {0};

    for (int i = 0; i < totalDepartments; i++) {
        for (int j = 0; j < departments[i].itemCount; j++) {
            itemCounts[departments[i].items[j].itemName[0] - 'A']++;
        }
    }

    cout << "Inventory Item Counts:\n";
    cout << "Server: " << itemCounts[0] << '\n';
    cout << "Desktop Computer: " << itemCounts[1] << '\n';
    cout << "Laptop: " << itemCounts[2] << '\n';
    cout << "Printer: " << itemCounts[3] << '\n';
    cout << "UPS: " << itemCounts[4] << '\n';
    cout << "Scanner: " << itemCounts[5] << '\n';
    cout << "Projector: " << itemCounts[6] << '\n';
}

void saveInventoryToFile() {
    ofstream file("inventory_data.txt");

    if (!file.is_open()) {
        cout << "Error opening file for writing.\n";
        return;
    }

    file << totalDepartments << '\n';
    for (int i = 0; i < totalDepartments; i++) {
        file << departments[i].departmentID << ' ' << departments[i].departmentName << '\n';
        file << departments[i].itemCount << '\n';
        for (int j = 0; j < departments[i].itemCount; j++) {
            file << departments[i].items[j].uniqueCode << ' ' << departments[i].items[j].itemName
                 << ' ' << departments[i].items[j].departmentID << ' ' << departments[i].items[j].isWorking << '\n';
        }
    }

    std::cout << "Inventory data saved to file.\n";
}

void loadInventoryFromFile() {
    ifstream file("inventory_data.txt");

    if (!file.is_open()) {
        cout << "Error opening file for reading.\n";
        return;
    }

    totalDepartments = 0;
    totalInventoryItems = 0;

    file >> totalDepartments;
    for (int i = 0; i < totalDepartments; i++) {
        file >> departments[i].departmentID >> departments[i].departmentName;
        file >> departments[i].itemCount;
        for (int j = 0; j < departments[i].itemCount; j++) {
            file >> departments[i].items[j].uniqueCode >> departments[i].items[j].itemName
                 >> departments[i].items[j].departmentID >> departments[i].items[j].isWorking;

            totalInventoryItems++;
        }
    }

    cout << "Inventory data loaded from file.\n";
}

int main() {
    
    loadInventoryFromFile();

    int choice;
    do {
        cout << "\nInventory Management System\n";
        cout << "1. Issue Inventory Item\n";
        cout << "2. Register Complaint\n";
        cout << "3. Print Department Inventory\n";
        cout << "4. Count Inventory Items\n";
        cout << "5. Save Inventory Data to File\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int departmentID;
                char itemName[50];

                cout << "Enter Department ID: ";
                cin >> departmentID;
                cout << "Enter Item Name: ";
                cin >> itemName;

                issueInventoryItem(departmentID, itemName);
                break;
            }

            case 2: {
                int uniqueCode;

                cout << "Enter Unique Code for the item: ";
                cin >> uniqueCode;

                registerComplaint(uniqueCode);
                break;
            }

            case 3: {
                int departmentID;

                cout << "Enter Department ID: ";
                cin >> departmentID;

                printDepartmentInventory(departmentID);
                break;
            }

            case 4:
                countInventoryItems();
                break;

            case 5:
                saveInventoryToFile();
                break;

            case 6:
                std::cout << "Exiting...\n";
                break;

            default:
                std::cout << "Invalid choice. Please enter a valid option.\n";
                     }
    } while (choice != 6);

    return 0;
}
