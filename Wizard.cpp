
#include "Foundable.h"
#include "Wizard.h"

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;


//srand(time(0));
int counter = 0;

Wizard::Wizard(){
    m_name = " ";
    m_toughness = 0;
    m_level = 0;
    m_wins = 0;
    m_losses = 0;
}

Wizard::Wizard(string name){
    srand(time(0));
    m_name = name;
    m_toughness = rand() % (MAX_START_TOUGH - MIN_START_TOUGH + 1) + MIN_START_TOUGH;
    m_level = 1;
    m_wins = 0;
    m_losses = 0;
}
string Wizard::GetName(){
    return m_name;
}

int Wizard::GetToughness(){
    return m_toughness;
}

int Wizard::GetLevel(){
    return m_level;
}

int Wizard::GetWins(){
    return m_wins;
}

int Wizard::GetLosses(){
    return m_losses;
}
void Wizard::SetName(string name){
    m_name = name;
}

void Wizard::SetToughness(int toughness){
    m_toughness = toughness;
}

void Wizard::InsertFoundable(Foundable newFoundable){
    m_foundables [counter] = newFoundable;
    counter++;
}


 bool Wizard::CheckFoundable(Foundable newFoundable){
     
     /*
     if(newFoundable.GetName() == " " && newFoundable.GetName() == " " && newFoundable.GetRarity() == 0
        && newFoundable.GetRarity() == 0){
         return false;
     }
     return true;*/
     
     //goes across m_foundables to see if newFoundable is in the array m_foundables
     
     for(int i = 0; i < NUM_FOUNDABLE; i++){
         if(m_foundables[i].GetName() == newFoundable.GetName() && m_foundables[i].GetType() == newFoundable.GetType() && m_foundables[i].GetRarity() == newFoundable.GetRarity() &&
         m_foundables[i].GetToughness() == newFoundable.GetRarity()){
             
             return true;
     }
         
         
         
     }
     return false;
     /*
     for(int i = 0; i < NUM_FOUNDABLE; i++){
         if(m_foundables[i].GetName() == newFoundable.GetName() && m_foundables[i].GetType() == newFoundable.GetType() && m_foundables[i].GetRarity() == newFoundable.GetRarity() &&
             m_foundables[i].GetToughness() == newFoundable.GetRarity()){
             return true;
         }
         
     }return false; */
 }

//attacks the foundable
//if the wizard wins, the wizard's wins goes up by 1 and levels up
//if the wizard loses, the wizard's losses goes up by 1
bool Wizard::AttackFoundable(Foundable enemy){
    if(m_toughness >  enemy.GetToughness()){
        
        Wizard::IncreaseLevel();
        //IncreaseLevel();
        Wizard::m_wins++;
        return true;
    }
    Wizard::m_losses++;
    return false;
}


void Wizard::PrintMyFoundables(){
    
    for(int i = 0; i < NUM_FOUNDABLE; i++){
        
        if (m_foundables[i].GetName() != " " && m_foundables[i].GetName() != " " && m_foundables[i].GetRarity() != 0
            && m_foundables[i].GetRarity() != 0){
            cout << m_foundables[i].GetName() << ", " <<  m_foundables[i].GetType() << ", " <<
            m_foundables[i].GetRarity() <<  ", " << m_foundables[i].GetToughness() << endl;
        }
        
    }
}

void Wizard::IncreaseLevel(){
    srand(time(0));
    m_level += 1;
    
    int levelToughness = rand() % LEVEL_TOUGH_INCREASE + 1;
    m_toughness += levelToughness;
}

