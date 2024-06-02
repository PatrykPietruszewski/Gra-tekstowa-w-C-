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

struct DialogueOption {
    string text;
    int nextNodeID;
};

struct DialogueNode {
    int id;
    string text;
    vector<DialogueOption> options;
};

class NPC {
public:
    string name;
    map<int, DialogueNode> dialogueTree;

    NPC() : name("None"){};
    NPC(const string& name) : name(name) {}

    void addDialogueNode(const DialogueNode& node) {
        dialogueTree[node.id] = node;
    }

    void startDialogue() {
        int currentNodeID = 0;
        while (true) {
            if (dialogueTree.find(currentNodeID) != dialogueTree.end()) {
                //Wyświetlenie obecnych opcji dialogowych (na zasadzie drzewa)
                DialogueNode& node = dialogueTree[currentNodeID];
                cout << node.text << endl;
                if (node.options.empty()) break; // End dialogue if no options available

                for (size_t i = 0; i < node.options.size(); ++i) {
                    cout << i + 1 << ". " << node.options[i].text << endl;
                }

                int choice;
                cin >> choice;
                if (choice > 0 && choice <= static_cast<int>(node.options.size())) {
                    currentNodeID = node.options[choice - 1].nextNodeID;
                } else {
                    cout << "Invalid choice. Please try again." << endl;
                }
            } else {
                cout << "Dialogue node not found. Ending conversation." << endl;
                break;
            }
        }
    }
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
    vector<string> HQNPC;
    vector<string> MarketNPC;
    vector<string> LibraryNPC;
    vector<string> HarbourNPC;
    vector<string> CenterNPC;
    vector<string> DepotNPC;
    vector<string> TowerNPC;
    vector<string> SchoolNPC;
    string currentLocation;
    string currentLocationInTown;
    bool gameOver;
    int playerHealth;
    map<string, NPC> npcs;

public:
    Game() : gameOver(false), playerHealth(100) {
        initializeGame();
    }

    void initializeGame() {
        cities = {"Pyroklas", "Flametongue", "Scorchville"};
        PyroklasLocations = {"Fire Wing headquarters","Marketplace","Main library"};
        FlametongueLocations = {"Centre for Fire Fighting Innovation","Harbour","Chemical Depot"};
        ScorchvilleLocations = {"Watchtower","Volcanic caves","Municipal school"};
        HQNPC = {"Chief Firefighter Elias", "Equipment Specialist Mia", "Trainee Alex"};
        MarketNPC = {"Merchant Carla", "Blacksmith Garrick"};
        LibraryNPC = {"Researcher Dr. Victor", "Student Emily"};
        CenterNPC = {"Lead Scientist Dr. Iris", "Training Officer Mark", "Engineer Linda"};
        HarbourNPC = {"Harbormaster Finn", "Fisherman Joe"};
        DepotNPC = {"Security Chief Leon", "Chemist Dr. Sarah"};
        TowerNPC = {"Scout Liam"};
        SchoolNPC = {"Teacher Mr. Roberts", "Lily"};
        currentLocation = cities[0];
        currentLocationInTown = PyroklasLocations[0];

        dragons["Fire Drake"] = Dragon("Fire Drake", "Spits fireballs");
        dragons["Smoke Wyrm"] = Dragon("Smoke Wyrm", "Creates smoke screens");
        dragons["Storm Dragon"] = Dragon("Storm Dragon", "Controls weather");

        inventory.push_back("Basic Hose");
        inventory.push_back("Fire Extinguisher");
        welcomePlayer();
        setupNPCs();

    }
    void welcomePlayer() {
        cout << "Enter your name: ";
        cin >> playerName;
        cout << "Hello, " << playerName << "! Get ready to fight the fire-breathing dragons and save the city!\n" << endl;
        cout << "=== Welcome to the World of Fire Wing Brigade ===" << endl;
        cout << "In a modern world where cities and towns coexist with fearsome dragons," << endl;
        cout << "you are a member of the elite 'Fire Wing Brigade' tasked with protecting the citizens from dragon fires." << endl;
        cout << "Your journey begins in the bustling city of Pyroklas, a place known for frequent dragon sightings and devastating fires." << endl;
        cout << "Recently, the attacks have become more frequent and intense, hinting at a sinister force behind the scenes." << endl;
        cout << "As a new but promising firefighter, it's your duty to uncover the mystery and save Pyroklas from destruction.\n" << endl;
        describeLocation("Pyroklas");
        describeLocationsInTown("Pyroklas","Fire Wing headquarters");
    }
    //Drzewa dialogowe dla każdego NPC
    //Każda odpowiedż ma swój ID, który prowadzi do określonych opcji i tak dalej
    void setupNPCs() {

        //ELIAS
        NPC elias("Chief Firefighter Elias");
        elias.addDialogueNode({0, "Welcome to the Fire Wing Headquarters. I have an important task for you.", {
                {"How do I fight dragons?", 1},
                {"What is it sir?", 2},
                {"I have to go now.", 3}
        }});
        elias.addDialogueNode({1, "Use your equipment and remember your training. It is also worth visiting the library to find out more.", {
                {"Thanks. About that task you mention.",2},
                {"I have to go now.", 3}
        }});
        elias.addDialogueNode({2, "Dragons have been getting more and more aggressive lately, there are rumours of the appearance of the largest dragon we have ever seen. Dr. Iris is investigating this situation and I want you to find her in Flametongue and help her with her research", {
                {"Why can't you send someone else?", 4},
                {"Yes, sir. I'm already on it.", 3}
        }});
        elias.addDialogueNode({3, "Stay safe out there!", {}});
        elias.addDialogueNode({4, "They are all busy putting out fires, you have to deal with it yourself. Now go!", {
                {"I can do it!", 3}
        }});

        npcs["Chief Firefighter Elias"] = elias;


        //MIA
        NPC mia("Equipment Specialist Mia");
        mia.addDialogueNode({0, "You must be "+playerName+", right? I have something for you." , {
                {"What is it?", 1},
                {"Could you upgrade my equipment?", 2},
                {"Not now.", 3}
        }});
        mia.addDialogueNode({1, "Here, take this. It will help you during your mission.", {
                {"Thanks, it will certainly come in handy.", 3}
        }});
        mia.addDialogueNode({2, "I can't do it, but I'm sure someone at the Centre will help you.", {
                {"Thanks, I'll check them out.", 3}
        }});
        mia.addDialogueNode({3, "Stay safe out there!", {}});

        npcs["Equipment Specialist Mia"] = mia;


        //ALEX
        NPC alex("Trainee Alex");
        alex.addDialogueNode({0, "Hey, I heard the boss has a very important mission for you. Good luck!" , {
                {"I've got to go.", 3}
        }});
        alex.addDialogueNode({3, "Stay safe out there!", {}});

        npcs["Trainee Alex"] = alex;
    }



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

    void move() {
        cout << "Choose where you want to go: " << endl;

        if (currentLocation == "Pyroklas") {
            for (size_t i = 0; i < PyroklasLocations.size(); i++) {
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

        if (currentLocation == "Flametongue") {
            for (size_t i = 0; i < FlametongueLocations.size(); i++) {
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

        if (currentLocation == "Scorchville") {
            for (size_t i = 0; i < ScorchvilleLocations.size(); i++) {
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

    void interact() {
        if (currentLocationInTown == "Fire Wing headquarters") {
            cout << "People you can talk to:\n";
            for (size_t i = 0; i < HQNPC.size(); i++) {
                cout << i + 1 << ". " << HQNPC[i] << endl;
            }
            int choice;
            cin >> choice;
            if (choice > 0 && choice <= static_cast<int>(HQNPC.size())) {
                string selectedNPC = HQNPC[choice - 1];
                if (npcs.find(selectedNPC) != npcs.end()) {
                    npcs[selectedNPC].startDialogue();
                } else {
                    cout << "NPC dialogue not available." << endl;
                }
            } else {
                cout << "Invalid choice, try again." << endl;
            }
        }

        // Add more NPC interactions similarly for other locations...
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
    void play() {
        while (!gameOver) {
            displayStatus();
            cout << "\nWhat do you want to do?\n";
            cout << "1. Travel to a new city\n";
            cout << "2. Move to a different location within the city\n";
            cout << "3. Interact with people\n";
            cout << "4. Save game\n";
            cout << "5. Load game\n";
            cout << "6. Quit\n";

            int choice;
            cin >> choice;

            switch (choice) {
                case 1:
                    travel();
                    break;
                case 2:
                    move();
                    break;
                case 3:
                    interact();
                    break;
                case 4:
                    saveGame();
                    break;
                case 5:
                    loadGame();
                    break;
                case 6:
                    gameOver = true;
                    break;
                default:
                    cout << "Invalid choice, try again." << endl;
            }
        }
    }
};

int main() {
    Game game;
    game.play();
    return 0;
}
