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
    vector<string> PyroklasLocations;
    vector<string> FlametongueLocations;
    vector<string> ScorchvilleLocations;
    string currentLocation;
    string currentLocationInTown;
    bool gameOver;
    int playerHealth;

public:
    Game() : gameOver(false), playerHealth(100) {
        initializeGame();
    }

    void initializeGame() {
        cities = {"Pyroklas", "Flametongue", "Scorchville"};
        PyroklasLocations = {"Fire Wing headquarters","Marketplace","Main library"};
        FlametongueLocations = {"Centre for Fire Fighting Innovation","Harbour","Chemical Depot"};
        ScorchvilleLocations = {"Watchtower","Volcanic caves","Municipal school"};
        currentLocation = cities[0];
        currentLocationInTown = PyroklasLocations[0];

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
        cout << "\nCurrent City: " << currentLocation << endl;
        cout << "Current Location: " << currentLocationInTown << endl;
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
    //Ruch w obszarze miasta
    void move(){
        cout <<"Choose where you want to go: " << endl;

        if (currentLocation == "Pyroklas"){
            for (size_t i = 0; i < PyroklasLocations.size(); i++){
                cout << i + 1 << ". " << PyroklasLocations[i] << endl;
            }

            int choice;
            cin >> choice;
            if (choice > 0 && choice <= static_cast<int>(PyroklasLocations.size())) {
                currentLocationInTown = PyroklasLocations[choice - 1];
                describeLocationsInTown(currentLocation, currentLocationInTown);
            } else {
                cout << "Invalid choice, try again." << endl;
            }
        }

        if (currentLocation == "Flametongue"){
            for (size_t i = 0; i < FlametongueLocations.size(); i++){
                cout << i + 1 << ". " << FlametongueLocations[i] << endl;
            }

            int choice;
            cin >> choice;
            if (choice > 0 && choice <= static_cast<int>(FlametongueLocations.size())) {
                currentLocationInTown = FlametongueLocations[choice - 1];
                describeLocationsInTown(currentLocation, currentLocationInTown);
            } else {
                cout << "Invalid choice, try again." << endl;
            }
        }

        if (currentLocation == "Scorchville"){
            for (size_t i = 0; i < ScorchvilleLocations.size(); i++){
                cout << i + 1 << ". " << ScorchvilleLocations[i] << endl;
            }

            int choice;
            cin >> choice;
            if (choice > 0 && choice <= static_cast<int>(ScorchvilleLocations.size())) {
                currentLocationInTown = ScorchvilleLocations[choice - 1];
                describeLocationsInTown(currentLocation, currentLocationInTown);
            } else {
                cout << "Invalid choice, try again." << endl;
            }
        }


    }
    //Zapis
    void saveGame() {
        ofstream saveFile("savegame.txt");
        saveFile << playerName << endl;
        saveFile << currentLocation << endl;
        saveFile << currentLocationInTown << endl;
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
            getline(saveFile, currentLocationInTown);
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
        cout << "\nEnter a command (travel, move, status, save, load, quit): ";
        cin >> command;

        if (command == "travel") {
            travel();
        } else if (command == "status") {
            displayStatus();
        } else if (command == "move"){
            move();
        }
        else if (command == "save") {
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
    //Opisy miast
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

    //Opisy miejsc w mieście
    void describeLocationsInTown(const string& location, const string& locationInTown) {
        if (location == "Pyroklas") {
            if (locationInTown == "Fire Wing headquarters"){
                cout << "The Fire Wing Headquarters stands as the nerve center of the elite firefighting brigade." << endl;
                cout << "Tall observation towers pierce the skyline, equipped with the latest technology to detect dragon activity." << endl;
                cout << "Inside, the sound of alarms is constant, and the hustle of firefighters preparing for their next mission fills the air." << endl;
                cout << "The walls are adorned with maps and plans, and the atmosphere is one of relentless readiness and camaraderie." << endl;
                cout << "" << endl;
            }
            else if (locationInTown == "Main library"){
                cout << "The Main Library of Pyroklas is a sanctuary of knowledge and history." << endl;
                cout << "This grand, old building, with its towering shelves and ancient tomes, exudes an aura of wisdom." << endl;
                cout << "It's a place of quiet reflection, where the whispers of the past can almost be heard among the rows of books." << endl;
                cout << "Here, you can uncover the rich history and legends of dragons, guided by the knowledgeable librarians who dedicate their lives to preserving these tales." << endl;
                cout << "" << endl;
            }
            else if (locationInTown == "Marketplace"){
                cout << "The marketplace is the vibrant heart of Pyroklas, where life goes on despite the ever-present threat of dragon attacks." << endl;
                cout << "Stalls brimming with fresh fruits, vegetables, and handmade goods create a colorful tapestry." << endl;
                cout << "The air is filled with the sounds of vendors hawking their wares and children playing." << endl;
                cout << "However, the occasional scorched building and the wary glances of the townspeople remind you of the lurking danger." << endl;
                cout << "" << endl;
            }

        } else if (location == "Flametongue") {
            if (locationInTown == "Centre for Fire Fighting Innovation"){
                cout << "The Centre for Fire Fighting Innovation is a beacon of progress and hope." << endl;
                cout << "Its sleek, glass-fronted buildings house state-of-the-art laboratories and training facilities." << endl;
                cout << "Scientists and engineers work tirelessly to develop new technologies, while firefighters hone their skills in realistic simulations." << endl;
                cout << "The air is charged with a sense of urgency and innovation, as everyone here is united by a common goal: to protect the city from the dragon menace." << endl;
                cout << "" << endl;
            }
            else if (locationInTown == "Harbour"){
                cout << "The harbour of Flametongue is a bustling hub of activity, where the scent of the sea mingles with the occasional hint of smoke." << endl;
                cout << "Ships laden with goods come and go, and fishermen haul in their daily catch." << endl;
                cout << "The creak of wooden docks and the calls of seagulls create a lively soundtrack." << endl;
                cout << "However, the threat of dragon attacks is never far away, and the harbour's defenses are always on high alert." << endl;
                cout << "" << endl;
            }
            else if (locationInTown == "Chemical Depot"){
                cout << "The Chemical Depot is a critical yet perilous location, storing a variety of hazardous substances." << endl;
                cout << "Securely guarded, this facility is filled with rows of containers marked with warning signs." << endl;
                cout << "The air is thick with the acrid smell of chemicals, and the atmosphere is one of tense vigilance." << endl;
                cout << "Any mishap here could have catastrophic consequences, especially if a dragon were to strike." << endl;
                cout << "" << endl;
            }


        } else if (location == "Scorchville") {
            if (locationInTown == "Watchtower"){
                cout << "The watchtower in Scorchville stands tall and solitary, offering a panoramic view of the surrounding forests." << endl;
                cout << "This lookout point is crucial for spotting approaching dragons." << endl;
                cout << "The air is thick with anticipation, and the occasional distant roar of dragons sends shivers down your spine." << endl;
                cout << "From here, you can see the stark contrast between the untouched beauty of nature and the charred remnants left by dragon flames." << endl;
                cout << "" << endl;
            }
            else if (locationInTown == "Volcanic caves"){
                cout << "The volcanic caves near Scorchville are a network of hot, dark tunnels that weave through the mountains." << endl;
                cout << "The ground trembles with the occasional rumble of volcanic activity, and the air is thick with the smell of sulfur." << endl;
                cout << "Shadows dance on the walls as the light from molten lava casts an eerie glow." << endl;
                cout << "These caves are said to hold secrets and perhaps even the hiding place of the legendary Warlord of Embers." << endl;
                cout << "" << endl;
            }
            else if (locationInTown == "Municipal school"){
                cout << "The municipal school of Scorchville is a modest building, yet it stands as a symbol of hope and resilience." << endl;
                cout << "Classrooms are filled with the sounds of eager students learning, while the playground outside is a place of joy and laughter." << endl;
                cout << "However, the looming threat of dragon attacks means that evacuation drills are a regular occurrence." << endl;
                cout << "The teachers are dedicated not only to education but also to ensuring the safety of their young charges." << endl;
                cout << "" << endl;
            }
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
