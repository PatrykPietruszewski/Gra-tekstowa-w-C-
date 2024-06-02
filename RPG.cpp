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

    Dragon() : name("Unknown"), ability("Unknown") {}
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

        dragons["Fire Drake"] = Dragon("Fire Drake", "Spits fireballs");
        dragons["Smoke Wyrm"] = Dragon("Smoke Wyrm", "Creates smoke screens");
        dragons["Storm Dragon"] = Dragon("Storm Dragon", "Controls weather");

        inventory.push_back("Basic Hose");
        inventory.push_back("Fire Extinguisher");

        welcomePlayer();
    }
    //Intro
    void welcomePlayer() {
        cout << "=== Welcome to the World of Fire Wing Brigade ===" << endl;
        cout << "In a modern world where cities and towns coexist with fearsome dragons," << endl;
        cout << "you are a member of the elite 'Fire Wing Brigade' tasked with protecting the citizens from dragon fires." << endl;
        cout << "Your journey begins in the bustling city of Pyroklas, a place known for frequent dragon sightings and devastating fires." << endl;
        cout << "Recently, the attacks have become more frequent and intense, hinting at a sinister force behind the scenes." << endl;
        cout << "As a new but promising firefighter, it's your duty to uncover the mystery and save Pyroklas from destruction.\n" << endl;
        cout << "Enter your name: ";
        cin >> playerName;
        cout << "Hello, " << playerName << "! Get ready to fight the fire-breathing dragons and save the city!\n" << endl;
        describeLocation("Pyroklas");
    }
    //Status
    void displayStatus() {
        cout << "\nCurrent Location: " << currentLocation << endl;
        cout << "Health: " << playerHealth << endl;
        cout << "Inventory: ";
        for (const string& item : inventory) {
            cout << item << ", ";
        }
        cout << endl;
    }
    //Ruch między miastami
    void travel() {
        cout << "Choose your next location: " << endl;
        for (size_t i = 0; i < cities.size(); ++i) {
            cout << i + 1 << ". " << cities[i] << endl;
        }

        int choice;
        cin >> choice;
        if (choice > 0 && choice <= static_cast<int>(cities.size())) {
            currentLocation = cities[choice - 1];
            describeLocation(currentLocation);
        } else {
            cout << "Invalid choice, try again." << endl;
        }
    }
    //Zapis
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
    //Wczytanie
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
    //Input gracza
    void handleInput() {
        string command;
        cout << "\nEnter a command (travel, status, save, load, quit): ";
        cin >> command;

        if (command == "travel") {
            travel();
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
    //Koniec gry
    void gameLoop() {
        while (!gameOver) {
            handleInput();
        }
        cout << "Game Over. Thanks for playing!" << endl;
    }
    //Opisy lokacji
    void describeLocation(const string& location) {
        if (location == "Pyroklas") {
            cout << "You are in Pyroklas, the heart of the region. Skyscrapers reach towards the sky," << endl;
            cout << "and the streets are always bustling with activity. Despite its grandeur, the city bears the scars of past dragon attacks." << endl;
        } else if (location == "Flametongue") {
            cout << "Flametongue, a city known for its advanced fire-fighting technology. The air is filled with the scent of smoke," << endl;
            cout << "and the horizon is often lit up by the glow of distant fires. It's a place where innovation meets necessity." << endl;
        } else if (location == "Scorchville") {
            cout << "Scorchville, a smaller town surrounded by forests. It's a peaceful place, but the threat of dragon attacks" << endl;
            cout << "always looms over the residents. The town has an eerie calmness, interrupted only by the occasional roar of dragons." << endl;
        }
    }
    //Opisy smoków
    void describeDragon(const Dragon& dragon) {
        cout << "A " << dragon.name << " has appeared! This fearsome creature is known for its " << dragon.ability << "." << endl;
        cout << "Beware, as it can cause immense destruction with its powers." << endl;
    }
    //NPC
    void interactWithNPC(const string& npcName) {
        if (npcName == "Chief Firefighter") {
            cout << "Chief Firefighter: 'We need to understand why the dragons are becoming more aggressive. There's something stirring them up.'" << endl;
            cout << "You: 'Do you have any leads, Chief?'" << endl;
            cout << "Chief Firefighter: 'Some say there's a legendary dragon, known as the Warlord of Embers, hidden in the volcanic mountains. We need to investigate.'" << endl;
        } else if (npcName == "Local Resident") {
            cout << "Local Resident: 'Thank you for saving us! We've heard rumors of a dark force controlling the dragons. Please be careful out there.'" << endl;
        }
    }
    //Zadania
    void startRescueMission() {
        cout << "Mission: A residential building in Pyroklas is engulfed in flames! Civilians are trapped inside." << endl;
        cout << "You must navigate through the blazing inferno, using your skills and tools to rescue them." << endl;
        cout << "The heat is intense, and the smoke makes it hard to see. You hear cries for help from the upper floors." << endl;
    }
    //Finał opis
    void finalConfrontation() {
        cout << "You have reached the lair of the Warlord of Embers, deep within the volcanic mountains." << endl;
        cout << "The ground trembles as the legendary dragon emerges from the shadows, its scales glowing with intense heat." << endl;
        cout << "'You have come far, mortal,' the Warlord of Embers growls. 'But your journey ends here.'" << endl;
        cout << "The final battle begins, as you use all your skills and tools to fight the dragon and save Pyroklas from utter destruction." << endl;
    }
    //Zakończenia
    void gameEnding(int endingType) {
        if (endingType == 1) {
            cout << "Congratulations! You have defeated the Warlord of Embers and saved Pyroklas. The city is safe once more, and you are hailed as a hero." << endl;
        } else if (endingType == 2) {
            cout << "You fought bravely, but the Warlord of Embers escaped. Pyroklas is in ruins, but your efforts saved many lives. The fight continues." << endl;
        } else if (endingType == 3) {
            cout << "The Warlord of Embers proved too strong. Pyroklas is lost, and the world falls into chaos. You are remembered as a valiant fighter who gave their all." << endl;
        }
    }
};

int main() {
    Game game;
    game.gameLoop();
    return 0;
}
