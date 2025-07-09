#include <iostream>
#include <limits>
#include <cstdio>
#include <sstream>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <vector>
#include <memory>
#include <functional>
#include <algorithm>
#include <numeric>
#include <random>
#include <map>

#include "Card.h"
#include "Card.cpp"
#include "Deck.h"
#include "Deck.cpp"
#include "Player.h"
#include "Player.cpp"

using namespace std;



//-------------------------------FUNCTION DECLARATIONS--------------------------------------
void clearInputBuffer();
int getIntInput();
double getDoubleInput();
int initialMenu();
int main();
void playingBlackJack(Deck& deck, Player& player);
int playMenu();
void changeSettings(Deck& deck, Player& player);
int settingsMenu();
void const tutorialDisplay();
void const creditsDisplay();
void playerHoldCheck(Player& player, Player& dealer, Deck& deck, int &playerbet);
bool loadPlayerFromFile(Player& player);
bool loadDeckFromFile(Deck& deck);
void savePlayerToFile(Player& player);
void saveDeckToFile(Deck& deck);
//bool checkFile();
//------------------------------------------------------------------------------------------


//Clears the input buffer when needed
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//Gets an integer from the user, checking to make sure the input is actually an integer
int getIntInput() {
    int value;
    while (!(cin >> value)) {
        cout << "Invalid input. Please enter a number: ";
        clearInputBuffer();
    }
    clearInputBuffer();  
    return value;
}

//Same as integer, only for double
double getDoubleInput() {
    double value;
    while (!(cin >> value)) {
        cout << "Invalid input. Please enter a decimal: ";
        clearInputBuffer();
    }
    clearInputBuffer();
    return value;
}

//bool checkFile() {
//
//}


//Loads the amount of cards in the deck from the file
bool loadDeckFromFile(Deck& deck) {
    string filename = "blkjck_info.txt"; 

    //makes sure file opens
    ifstream file(filename);
    if (!file) {
        cerr << "Error: File Could Not Open " << filename << endl;
        return false;
    }

    string line;
    string mode;

    //checks which lines it needs to read
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') {
            if (line == "# player|chips") mode = "player";
            if (line == "# deck|amount") mode = "deck";
            continue;
        }

        //reads the formatted file lines
        stringstream ss(line);
        string part1, part2;
        getline(ss, part1, '|');
        getline(ss, part2);

        //if the deck line is selected, it stores the integer found into the deck
        //if there is an invalid or missing number, it initializes a standard 52 card deck
        if (mode == "deck") {
            if (part2.empty() || stoi(part2) <= 0) {
                cout << "\n- Deck size in file is empty, adding 52 to shoe -\n";
                deck.clearDeck();
                deck.populateDeck(52);
                file.close();
                return true;
            }
            deck.populateDeck(stoi(part2));

        }

    }

    //closes file and returns a true
    file.close();
    return true;

}


//Loads the player chip amount from the file, same as the deck function
bool loadPlayerFromFile(Player& player) {

    string filename = "blkjck_info.txt"; 

    ifstream file(filename);
    if (!file) {
        cerr << "Error: File Could Not Open " << filename << endl;
        return false;
    }

    string line;
    string mode;

    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') {
            if (line == "# player|chips") mode = "player";
            if (line == "# deck|amount") mode = "deck";
            continue;
        }

        stringstream ss(line);
        string part1, part2;
        getline(ss, part1, '|');
        getline(ss, part2);

        if (mode == "player") {
            if (part2.empty() || stoi(part2) <= 0) {
                cout << "\n- Player chips in file are empty, adding 50 -\n";
                player.setPlayerChips(50);
                file.close();
                return true;
            }
            player.addChipsToPlayer(stoi(part2));

        }

    }

    file.close();
    return true;

}

//Displays credits, nothin much here
void const creditsDisplay() {

    cout << "\n\n- - - - - - - - - - - - -\nCreated by Conner T (me)\n- - - - - - - - - - - - -\n\n";

}


//Diplays tutorial to user
void const tutorialDisplay() {

    cout << " -- Welcome to Black Jack! -- \n";
    cout << "The Goal of the game is to draw cards up to a rank value of 21.\n";
    cout << "Upon the keyboard prompts, you'll draw cards until you decide to hold them, where they'll be compared to the dealer's hand. \n";
    cout << "If your hand is better than the dealer (closer to 21) you'll win! \n";
    cout << "If your hand is lower or if you go over 21 (bust), you'll lose your bet. \n";
    cout << "Good luck out there, you'll need it! \n\n";

}

//Initial menu for the user, returns the user input integer
int initialMenu() {
    cout << "===== Black Jack =====\n";
    cout << "1. Play Plain Black Jack\n"; 
    cout << "2. Change Settings\n";
    cout << "3. View Tutorial\n";
    cout << "4. View Credits\n";
    cout << "5. Exit\n"; 
    cout << "Enter your choice (1-5): \n";
    cout << "======================\n>";
    return getIntInput();
}


//Settings menu for user, same as main menu
int settingsMenu() {
    cout << "----- GAME SETTINGS -----\n";
    cout << "1. Change Deck Size\n"; 
    cout << "2. Change Starting Chip Amount\n";
    //cout << "3. \n";  Change chip factor mulitply??
    //cout << "4. \n";
    cout << "0. Exit\n"; 
    cout << "Enter your choice (1-0): \n";
    cout << "-------------------------\n>";

    return getIntInput();
}


//Changes the settings of the game for the user
void changeSettings(Deck& deck, Player& player) {

    //initializes the variables for the switch case
    bool running = true;
    int userin;

    //While running is true, make the userinput for settings 0 and go into the switch case
    while (running) { 
        userin = 0;
        int choice = settingsMenu();

        switch (choice) {
            case 1: // Change deck size
                deck.clearDeck();
                cout << "Enter the new deck size (Amount of cards): \n>";
                userin = abs(getIntInput());
                deck.populateDeck(userin);
                cout << "- Deck repopulated to " << deck.countCardsInDeck() << " cards -\n";
                saveDeckToFile(deck);
                break;

            case 2: // Change starting chips 
                player.setPlayerChips(0);
                cout << "Enter the new chip amount: \n>";
                userin = abs(getIntInput());
                player.addChipsToPlayer(userin);
                cout << "- " << player.getPlayerChips() << " chips added to player - \n";
                savePlayerToFile(player);
                break;

            case 3: // 

                break;

            case 4: // 
                break;

            case 0: // Exit
                cout << "-Exiting Settings Menu-\n";
                running = false;
                break;
            default:
                cout << "-Unrecognized Input-\n";

        };

    }    


}

//Main function, it initializes the deck and player as well as seeds the random number
int main() {
    srand(time(0));
    bool running = true;
    Deck deck;
    Player player;

    //loads deck first in case of invalidness 
    loadDeckFromFile(deck);

    while (running) { 
        int choice = initialMenu();

        switch (choice) {
            case 1: // Play
                playingBlackJack(deck, player);
                break;
            case 2: // Change settings
                changeSettings(deck, player);
                break;
            case 3: // View tutorial
                tutorialDisplay();
                break;
            case 4: // View Credits
                creditsDisplay();
                break;
            case 5: // Exit
                cout << "\n-Exiting Program-\n";
                running = false;
                break;
            default:
                cout << "-Unrecognized Input-\n";

        };

    }

    return 0;

}


//Play menu for user
int playMenu() {
    cout << "\n--------BLACK JACK--------\n";
    cout << "1. Call Card\n";
    cout << "2. Check Hands\n";
    cout << "3. Hold\n";
    cout << "4. Forfeit Hand\n";
    cout << "Enter 1-4\n";
    cout << "--------------------------\n>";

    return getIntInput();

}



//Playing the game function holding most of the operations
void playingBlackJack(Deck& deck, Player& player) {

    //Initializing everything in this function
    //Bools for all the checks are set as well as the drawn card object
    Card draw;
    bool loaded_player = false;
    bool loaded_deck = false;
    bool findcard = true;
    bool playing = true;
    bool isdeckpop = true;
    bool phold = false;
    int players_total = 0; 
    int playerbet = 0;

    bool validbet = true;
    loaded_deck = loadDeckFromFile(deck);
    loaded_player = loadPlayerFromFile(player);


    //Checks that both player and deck are loaded from file
    if (loaded_player == false || loaded_deck == false) {
        cout << " - Error, player/deck not loaded - \n";
        return;

    }


    //Checks again that player and deck is loaded so that player may place bet
    if (loaded_player == true && loaded_deck == true) {
        //player bet setting
        player.displayPlayerChips();
        cout << "Place your bet amount: \n";
        //increments of chip values, make sure the input is available in player inventory

        while (validbet) {

            playerbet = getIntInput(); 

            //Checks that bet is in valid range
            if (playerbet > player.getPlayerChips() || playerbet <= 0) {
                cout << " - Invalid bet - \n";
                player.displayPlayerChips();
                playerbet = 0;
            }

            else if (playerbet <= player.getPlayerChips()) {
                validbet = false;
            }

            else {
                cout << " - Error in loop - ";
                validbet = false;
            }

        }
    }


    //Dealer Initialization - draws two cards
    Player dealer;
    dealer.clearPlayerHand();
    for (int i = 0; i < 1; i++) {
        findcard = true;
        while(findcard) {
            draw = draw.drawCard();
            if (deck.drawCardFromDeck(draw) == true) {
                dealer.addCardToHand(draw);
                findcard = false;

            }

        }
        
    }

    cout << "The dealer has two cards. One face up and one face down. Dealer has a " << draw.printRank() << " of " << draw.printSuit() << ".\n";

    //check for dealer black jack
    if (dealer.addPlayerHand() == 21) {
        cout << "Dealer has BlackJack";
        playing = false;
    }
    //Check for dealer bust
    if (dealer.checkPlayerHand() == false) {
        cout << "Dealer has bust.\n";
        playing = false;
    }

    //Player initialization
    draw = draw.drawCard();
    player.addCardToHand(draw);
    cout << "You are dealt one card. A " << draw.printRank() << " of " << draw.printSuit() << "\n"; 


    //While playing and while there are enough cards in the deck, run the switch case for playing
    while (playing && isdeckpop) {
        findcard = true;
        int choice = playMenu();    

        switch(choice) {
            case 1: // Call Card
                //Continues until a valid card is found in the deck then adds to hand
                while(findcard) {
                    draw = draw.drawCard();
                    if (deck.drawCardFromDeck(draw) == true) {
                        player.addCardToHand(draw);
                        cout << "You drew a " << draw.printRank() << " of " << draw.printSuit() << ".\n";    
                        cout << "Bringing your hand to a total of " << player.addPlayerHand() << "\n";
                        findcard = false;

                    } else { continue; }
                }

                break;

            case 2: // Check Hand
                cout << "You currently have: \n";
                player.displayPlayerHand();
                cout << "\nFor a total of " << player.addPlayerHand() << "\n";
                break;

            case 3: // Hold
                phold = true;
                playerHoldCheck(player, dealer, deck, playerbet);
                playing = false;
                break;

            case 4: // forfeit
                player.removeChipsFromPlayer(playerbet);
                cout << "You forfeit the hand, losing your bet amount.\n\n";  //!!make lose chips
                cout << "- Chips decreased to " << player.getPlayerChips() << " -\n";     
                savePlayerToFile(player);   
            
                cout << "Press Enter to Continue\n\n";
                cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
                
                playing = false;
                break;

        };


        //Checks if player is over 21 after a card is drawn
        if (player.checkPlayerHand() == false) { 
            player.removeChipsFromPlayer(playerbet);
            cout << "== You have bust ==\n";
            cout << "- Chips decreased to " << player.getPlayerChips() << " -\n";

            savePlayerToFile(player);

            cout << "Press Enter to Continue\n\n";
            cin.ignore(std::numeric_limits<streamsize>::max(),'\n');

            playing = false;



        }

        //checks if deck is populated
        if (deck.checkForEmptyDeck() == false) {
            isdeckpop = false;
        }


    }



}

//When the player holds their hand, it runs here
void playerHoldCheck(Player& player, Player& dealer, Deck& deck, int &playerbet) {
    //Initializing player total and dealer total hand
    int pt = player.addPlayerHand();
    int dt = dealer.addPlayerHand();
    Card draw;
    bool findcard;

    //Draws while dealer total is less than 17
    cout << "\nWhile dealer has less than 17, they draw.\n";
    while (dt <= 17) {
        findcard = true;
        //Same findcard function in playing function
        while(findcard) {
            draw = draw.drawCard();
            if (deck.drawCardFromDeck(draw) == true) {
                dealer.addCardToHand(draw);
                dt = dealer.addPlayerHand();
                cout << "The dealer draws a " << draw.printRank() << " of " << draw.printSuit() << "\n";
                cout << "Dealer is at " << dt << "\n";
                findcard = false;

            }
        }
    }


    //if dealer is above 21, they lose and player wins
    if (dt > 21) {
        cout << "The dealer has bust with: \n";
        dealer.displayPlayerHand();
        cout << "\nTotal of " << dt;
        cout << "\n=You Win!=\n";
        playerbet = playerbet * 2;
        player.addChipsToPlayer(playerbet);
        cout << " - Chips increased to: " << player.getPlayerChips() << " -\n";
        
    }
    //if dealer is at or above 17 and player is higher
    else if (pt > dt) {
        cout << "You beat the dealer!\nDealer: " << dt << "\nPlayer: " << pt << "\n=You Won!=\n";
        player.addChipsToPlayer(playerbet);
        cout << " - Chips increased to: " << player.getPlayerChips() << " -\n";

    }
    //if player is less than dealer
    else if (dt > pt) {
        cout << "Dealer: " << dt << "\nPlayer: " << pt << "\n=The dealer wins=\n";
        player.removeChipsFromPlayer(playerbet);
        cout << " - Chips decreased to: " << player.getPlayerChips() << " -\n";

    }
    //if dealer and player are equal
    else if (pt == dt) {
        cout << "You and the dealer have equal hands\n" << "Dealer: " << dt << "\nPlayer: " << pt << "\n=Pushed Hand=\n";
        cout << " - Chips stay the same - \n";

    }
    //error catch
    else {
        cout << " - Error in adding/comparing hands - \n"; 

    }


    //saves the chips to file and buffer for user
    savePlayerToFile(player);
    cout << "Press Enter to Continue\n\n";
    cin.ignore(std::numeric_limits<streamsize>::max(),'\n');

}

//Saves the player chips to the file
void savePlayerToFile(Player& player) {
    string filename = "blkjck_info.txt"; 

    ifstream file(filename);
    if (!file) {
        cerr << "Error: File Could Not read in save function" << filename << endl;
        return;
    }

    vector<string> file_lines;
    string line;
    int count;
    int line_number;

    //Finds the line where the player is 
    while (getline(file, line)) {
        count += 1;
        file_lines.push_back(line);
        if (line.empty() || line[0] == '#') {
            if (line == "# player|chips") line_number = count;
            continue;
        }
    }

    //makes a vector of the file, replacing the player chips
    int chips = player.getPlayerChips();
    string input = "player|" + to_string(chips);
    vector<char> input_vector(input.begin(), input.end());

    //Erases and replaces the player chip count
    file_lines.erase(file_lines.begin() + line_number);  
    for (size_t i; i < input_vector.size(); i++){
        file_lines[line_number].push_back(input_vector[i]);
    }
    file_lines[line_number].push_back('\n');
    file.close();


    ofstream myFile("blkjck_info.txt", ios::out);

    if (!myFile) {
        cerr << " -- Failed to write to file in save function -- " << endl;
        return;
    }


    //Writes the new file 
    for (size_t i = 0; i < file_lines.size(); i++) {
        myFile << file_lines[i] << "\n";

    }

    myFile.close();

    return;

}


//Saves the card amount to deck
//Exactly the same as the player function, only replacing the deck amount instead of player chip amount
void saveDeckToFile(Deck& deck) {

    string filename = "blkjck_info.txt"; 

    ifstream file(filename);
    if (!file) {
        cerr << "Error: File Could Not read in save function" << filename << endl;
        return;
    }

    vector<string> file_lines;
    string line;
    int count;
    int line_number;

    while (getline(file, line)) {
        count += 1;
        file_lines.push_back(line);
        if (line.empty() || line[0] == '#') {
            if (line == "# deck|amount") line_number = count;
            continue;
        }
    }

    int amount = deck.countCardsInDeck();
    string input = "deck|" + to_string(amount);
    vector<char> input_vector(input.begin(), input.end());

    file_lines.erase(file_lines.begin() + line_number); //!!Currently trying to get this to run without crashing -- 
    for (size_t i; i < input_vector.size(); i++) {  
        file_lines[line_number].push_back(input_vector[i]);
    }

    file_lines[line_number].push_back('\n');

    file.close();


    ofstream myFile("blkjck_info.txt", ios::out);

    if (!myFile) {
        cerr << " -- Failed to write to file in save function -- " << endl;
        return;
    }


    for (size_t i = 0; i < file_lines.size(); i++) {
        myFile << file_lines[i] << "\n";

    }

    myFile.close();

    return;

}




