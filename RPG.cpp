#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string>

using namespace std;

class Dragon {
public:
    string name;
    string ability;

    // Konstruktor domyślny
    Dragon() : name("Unknown"), ability("Unknown") {}

    // Konstruktor z parametrami
    Dragon(string name, string ability) : name(name), ability(ability) {}
};

class Tool {
public:
    string name;
    string description;

    Tool(string name, string description) : name(name), description(description) {}
};

class Game {
private:
    string playerName;
    vector<string> inventory;
    map<string, Dragon> dragons;
    vector<string> cities;
    string currentLocation;
    bool gameOver;
    int playerHealth;

public:
    Game() : gameOver(false), playerHealth(100) {
        initializeGame();
    }

    void initializeGame() {
        cities = {"Pyroklas", "Flametongue", "Scorchville"};
        currentLocation = cities[0];

        // Inicjalizacja smoków
        dragons["Fire Drake"] = Dragon("Fire Drake", "Spits fireballs");
        dragons["Smoke Wyrm"] = Dragon("Smoke Wyrm", "Creates smoke screens");
        dragons["Storm Dragon"] = Dragon("Storm Dragon", "Controls weather");

        // Przykładowe narzędzia
        inventory.push_back("Basic Hose");
        inventory.push_back("Fire Extinguisher");

        cout << "Welcome to the Fire Wing Brigade, brave firefighter!" << endl;
        cout << "Enter your name: ";
        cin >> playerName;
        cout << "Hello, " << playerName << "! Get ready to fight the fire-breathing dragons and save the city!" << endl;
    }

    void displayStatus() {
        cout << "\nCurrent Location: " << currentLocation << endl;
        cout << "Health: " << playerHealth << endl;
        cout << "Inventory: ";
        for (const string& item : inventory) {
            cout << item << ", ";
        }
        cout << endl;
    }

    void move() {
        cout << "Choose your next location: " << endl;
        for (size_t i = 0; i < cities.size(); ++i) {
            cout << i + 1 << ". " << cities[i] << endl;
        }

        int choice;
        cin >> choice;
        if (choice > 0 && choice <= static_cast<int>(cities.size())) {
            currentLocation = cities[choice - 1];
            cout << "You moved to " << currentLocation << endl;
        } else {
            cout << "Invalid choice, try again." << endl;
        }
    }

    void saveGame() {
        ofstream saveFile("savegame.txt");
        saveFile << playerName << endl;
        saveFile << currentLocation << endl;
        saveFile << playerHealth << endl;
        for (const string& item : inventory) {
            saveFile << item << endl;
        }
        saveFile.close();
        cout << "Game saved!" << endl;
    }

    void loadGame() {
        ifstream saveFile("savegame.txt");
        if (saveFile.is_open()) {
            getline(saveFile, playerName);
            getline(saveFile, currentLocation);
            saveFile >> playerHealth;
            saveFile.ignore();
            inventory.clear();
            string item;
            while (getline(saveFile, item)) {
                inventory.push_back(item);
            }
            saveFile.close();
            cout << "Game loaded!" << endl;
        } else {
            cout << "No saved game found!" << endl;
        }
    }

    void handleInput() {
        string command;
        cout << "\nEnter a command (move, status, save, load, quit): ";
        cin >> command;

        if (command == "move") {
            move();
        } else if (command == "status") {
            displayStatus();
        } else if (command == "save") {
            saveGame();
        } else if (command == "load") {
            loadGame();
        } else if (command == "quit") {
            gameOver = true;
        } else {
            cout << "Unknown command, try again." << endl;
        }
    }

    void gameLoop() {
        while (!gameOver) {
            handleInput();
        }
        cout << "Game Over. Thanks for playing!" << endl;
    }
};

int main() {
    Game game;
    game.gameLoop();
    return 0;
}
