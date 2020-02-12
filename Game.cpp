#include "Game.h"
#include "Foundable.h"
#include "Wizard.h"

//Wizard w1 = Wizard("Test");


//initializes the game
Game::Game(){
    
    cout << "Welcome to Harry Potter: Wizards Unite" << endl;
    cout << LoadFoundables() << " foundables loaded" << endl;
    //Wizard w1 = Wizard("Test");
    GetWizardName();
    MainMenu();
    
    //cout << "0 Foundables loaded" << endl;
    //cout << "What is your wizard's name?" << endl;
    //string wizName;
    //cin >> wizName;
    //Wizard newWiz(wizName);
    
}

//asks for the Wizards name, and instantiates a new Wizard with the given name
//ranadom toughnes, and level 1
void Game::GetWizardName(){
    
    cout << "What is your wizard's name?" << endl;
    string wizName;
    cin >> wizName;
    m_wizard = Wizard(wizName);
    //m_wizard = m_wizard.
    
    
    
}


void Game::MainMenu(){
    
    bool all = false;
    bool quitGame = false;
    int inputNum = 0;
    

    do {
        
        do {
            cout << "What would you like to do?" << endl;
            cout << "1. Wizard Information" << endl;
            cout << "2. List my Foundables" << endl;
            cout << "3. List all Foundables" << endl;
            cout << "4. Attack Foundable" << endl;
            cout << "5. Quit " << endl;
            cin >> inputNum;
            
        } while(inputNum < 1 && inputNum > 5);
        switch(inputNum){
                
                
            case 1:
                WizardStat();
                break;
                
                
            case 2:
                PrintMyFoundables();
                break;
                
                
            case 3:
                PrintFoundables();
                break;
                
            case 4:
                AttackFoundable();
                break;
                
            case 5:
                quitGame = true;
                break;
        }
        
        inputNum = 0;
    } while (quitGame == false || all == false);

    
}

//Loads up the text file into the program
int Game::LoadFoundables(){
    
    int counter = 0;
    ifstream myFile ("proj2.txt");
    
    
    //values set for the foundables
    string name, type, rarity, toughness;
    
    //goes across each line and sets the values for the foundable that is set apart by commas
    while(getline(myFile, name, ',')){
    
    //gets the type of foundable
    getline(myFile, type, ',');
    
    //gets the rarity of foundable
    getline(myFile, rarity, ',');
        
    //gets the toughness of foundable
    getline(myFile, toughness);
    
    //converts the string obtained from getline into an int
    int rarityNum = stoi(rarity);
    int toughNum = stoi(toughness);
    
    //foundable is generated with the values obtained from getline
    Foundable a1;
    a1.SetName(name);
    a1.SetType(type);
    a1.SetRarity(rarityNum);
    a1.SetToughness(toughNum);
    
    //places said foundable into m_allFoundables
    m_allFoundables[counter] = a1;
    m_wizard.InsertFoundable(a1);
    counter++;
    }
    myFile.close();
    
    
    return  counter;
}

//Goes accross the entire m_allFoundables array and prints out the values from each foundable
void Game::PrintFoundables(){
    for(int i = 0; i < NUM_FOUNDABLE; i++){
        
       cout << m_allFoundables[i].GetName() << ", " <<  m_allFoundables[i].GetType() << ", " <<
         m_allFoundables[i].GetRarity() <<  ", " << m_allFoundables[i].GetToughness() << endl;
    }
    
    
}

//prints out the m_foundables array from m_wizard, which is an array of all foundables foudn by the wizard
void Game::PrintMyFoundables(){
    m_wizard.PrintMyFoundables();
}

//prints out the information from m_wizard
void Game::WizardStat(){
    
    cout << "Information about Wizard " << m_wizard.GetName() << endl;
    cout << "Level " <<  m_wizard.GetLevel() << endl;
    cout << "Toughness" << m_wizard.GetToughness() << endl;
    cout << "Foundables found " <<  m_wizard.GetWins() << endl;
    cout << "Wins " << m_wizard.GetWins();
    cout << " Losses " << m_wizard.GetLosses() << endl;
    
    double winRate = (double)m_wizard.GetWins()/ double(m_wizard.GetWins()+m_wizard.GetLosses());
    cout << "Win rate:" << setprecision(2) << winRate << endl;
}
//method to attack foundables
void Game::AttackFoundable(){
    
    int inputNum = 0;
    srand(time(0));
    int randNum = rand() % NUM_FOUNDABLE;
    
    bool foundMatch = false;
    
    //booleans to check if all foundables with said rarity have been found
    bool all1 = false;
    bool all2 = false;
    bool all3 = false;
    bool all4 = false;
    bool all5 = false;
    
    Foundable enemy;
    Foundable randomCopy [NUM_FOUNDABLE];
    Foundable randomTemp;
    
    //initializes a temporary array of foundables with the
    // same values as m_allFoundables
    for(int i = 0; i < NUM_FOUNDABLE; i++){
    
        randomCopy[i] = m_allFoundables[i];
    }
    
    //randomly sorts the values in randomTemp so that you randomly draw a foundable
    for(int i = 0; i < NUM_FOUNDABLE; i++){
        int randNum = rand() % NUM_FOUNDABLE;
        randomTemp = randomCopy[i];
        randomCopy[i] = randomCopy[randNum];
        randomCopy[randNum] = randomTemp;
        
    }
    
    
    do {
        cout << "What is the rarity of foundable would you like to challenge?" << endl;
        cin >> inputNum;
    } while(inputNum < 1 || inputNum > 5);
    
    
    switch(inputNum){
            
            
        case 1:
            
            
            //goes across randomCopy foundable array to find the next Foundable that is of the same rarity
            // and not in the Wizard's foundable array
            for(int i = 0; i < NUM_FOUNDABLE; i++){
                if(randomCopy[i].GetRarity() == 1 && m_wizard.CheckFoundable(randomCopy[i]) == false ){
                    
                    foundMatch = true;
                    cout << "The wizard attacks " << randomCopy[i].GetName() << "!!!" << endl;
                    
                    
                    
                    //if the Wizard wins, the wizard levels up when randomCopy is true
                    // or adds a loss if randomCopy is false
                    if(m_wizard.AttackFoundable(randomCopy[i]) == true){
                        cout << "You have defeated the foundable " << randomCopy[i].GetName() << "!!!" << endl;
                        
                        m_wizard.InsertFoundable(randomCopy[i]);
                        break;
                        
                    } else{
                        cout << "You did not successfully defeat the foundable " << randomCopy[i].GetName() << "!!!" << endl;
                        break;
                    }
                }
            }
            

            
            //if all the foundables of rarity 1 have been defeated already
            if (foundMatch == false){
                cout << "All foundables of that rarity have been defeated" << endl;
                all1 = true;
            }
            
            
            
            
            break;
            
            
        case 2:
            
            //goes across randomCopy foundable array to find the next Foundable that is of the same rarity
            // and not in the Wizard's foundable array
            for(int i = 0; i < NUM_FOUNDABLE; i++){
                if(randomCopy[i].GetRarity() == 2 && m_wizard.CheckFoundable(randomCopy[i]) == false ){
                    
                    foundMatch = true;
                    cout << "The wizard attacks " << randomCopy[i].GetName() << "!!!" << endl;
                    
                    
                    
                    //if the Wizard wins, the wizard levels up when randomCopy is true
                    // or adds a loss if randomCopy is false
                    if(m_wizard.AttackFoundable(randomCopy[i]) == true){
                        cout << "You have defeated the foundable " << randomCopy[i].GetName() << "!!!" << endl;
                        
                        m_wizard.InsertFoundable(randomCopy[i]);
                        break;
                        
                    } else{
                        cout << "You did not successfully defeat the foundable " << randomCopy[i].GetName() << "!!!" << endl;
                        break;
                    }
                }
            }
            
            
             //if all the foundables of rarity 2 have been defeated already
            if (foundMatch == false){
                cout << "All foundables of that rarity have been defeated" << endl;
                all2 = true;
            }
            break;
            
            
        case 3:
            
            //goes across randomCopy foundable array to find the next Foundable that is of the same rarity
            // and not in the Wizard's foundable array
            for(int i = 0; i < NUM_FOUNDABLE; i++){
                if(randomCopy[i].GetRarity() == 3 && m_wizard.CheckFoundable(randomCopy[i]) == false ){
                    
                    foundMatch = true;
                    cout << "The wizard attacks " << randomCopy[i].GetName() << "!!!" << endl;
                    
                    
                    
                    //if the Wizard wins, the wizard levels up when randomCopy is true
                    // or adds a loss if randomCopy is false
                    if(m_wizard.AttackFoundable(randomCopy[i]) == true){
                        cout << "You have defeated the foundable " << randomCopy[i].GetName() << "!!!" << endl;
                        
                        m_wizard.InsertFoundable(randomCopy[i]);
                        break;
                        
                    } else{
                        cout << "You did not successfully defeat the foundable " << randomCopy[i].GetName() << "!!!" << endl;
                        break;
                    }
                }
            }
            
            
            //if all the foundables of rarity 3 have been defeated already
            if (foundMatch == false){
                cout << "All foundables of that rarity have been defeated" << endl;
                all3 = true;
            }
            
            break;
            
        case 4:
            
            //goes across randomCopy foundable array to find the next Foundable that is of the same rarity
            // and not in the Wizard's foundable array
            for(int i = 0; i < NUM_FOUNDABLE; i++){
                if(randomCopy[i].GetRarity() == 4 && m_wizard.CheckFoundable(randomCopy[i]) == false ){
                    
                    foundMatch = true;
                    cout << "The wizard attacks " << randomCopy[i].GetName() << "!!!" << endl;
                    
                    
                    
                    //if the Wizard wins, the wizard levels up when randomCopy is true
                    // or adds a loss if randomCopy is false
                    if(m_wizard.AttackFoundable(randomCopy[i]) == true){
                        cout << "You have defeated the foundable " << randomCopy[i].GetName() << "!!!" << endl;
                        
                        m_wizard.InsertFoundable(randomCopy[i]);
                        break;
                        
                    } else{
                        cout << "You did not successfully defeat the foundable " << randomCopy[i].GetName() << "!!!" << endl;
                        break;
                    }
                }
            }
            
            //if all the foundables of rarity 4 have been defeated already
            if (foundMatch == false){
                cout << "All foundables of that rarity have been defeated" << endl;
                all4 = true;
            }
            
            break;
            
        case 5:
            
            //goes across randomCopy foundable array to find the next Foundable that is of the same rarity
            // and not in the Wizard's foundable array
            for(int i = 0; i < NUM_FOUNDABLE; i++){
                if(randomCopy[i].GetRarity() == 5 && m_wizard.CheckFoundable(randomCopy[i]) == false ){
                    
                    foundMatch = true;
                    cout << "The wizard attacks " << randomCopy[i].GetName() << "!!!" << endl;
                    
                    
                    
                    //if the Wizard wins, the wizard levels up when randomCopy is true
                    // or adds a loss if randomCopy is false
                    if(m_wizard.AttackFoundable(randomCopy[i]) == true){
                        cout << "You have defeated the foundable " << randomCopy[i].GetName() << "!!!" << endl;
                        
                        m_wizard.InsertFoundable(randomCopy[i]);
                        break;
                        
                    } else{
                        cout << "You did not successfully defeat the foundable " << randomCopy[i].GetName() << "!!!" << endl;
                        break;
                    }
                }
            }
            
            //if all the foundables of rarity 4 have been defeated already
            if (foundMatch == false){
                cout << "All foundables of that rarity have been defeated" << endl;
                all5 = true;
            }
            
            break;
    }
    
    if(all1 == true && all2 == true && all3 == true && all4 == true && all5 == true){
        cout << "All foundables have been found" << endl;
        exit(0);
    }
}

