
#include <iostream>
#include "Wizard.h"
#include "Foundable.h"
#include "Game.h"

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    cout << "Hello, World!\n";
    //cout << "Potatos forever";
    
    Game newGame;
    newGame.MainMenu();
    //newgame.LoadFoundables();
    //cout << newgame.LoadFoundables() << " foundables loaded" << endl;
    //newgame.PrintFoundables();
    return 0;
}
