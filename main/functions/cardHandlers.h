#include"../definitions/gameTypes.h"
#include"../definitions/gameRules.h"
#include<stdio.h>
#include<stdbool.h> //Might be able to remove, depending on how I want to do it

//Returns true if the played card is valid
bool checkCardValid(card lastPlayed, card canidate) {
    if(lastPlayed.color == canidate.color) {
        return true;
    } else if(lastPlayed.name == canidate.name) {
        return true;
    }

    //Return false if the color or name don't match
    return false;
}

