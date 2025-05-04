/*
A collection of functions that determine how cards and actions work
*/
#include"../definitions/gameTypes.h"
#include"../definitions/gameRules.h"
#include<stdio.h>
#include<stdbool.h> //Might be able to remove, depending on how I want to do it

//Function that checks if the card can be played. Returns true if it can be, returns false if it can't.
bool checkCardValid(card lastPlayed, card canidate) {
    if(lastPlayed.color == canidate.color) {
        return true;
    } else if(lastPlayed.name == canidate.name) {
        return true;
    }

    //Return false if the color or name don't match
    return false;
}

//Function that draws a card to the player's next available card slot. Returns 0 upon success. Returns 1 upon empty deck, returns 2 on player hand reaching max cap.
int drawCard(card deck[], player p) {
    int nextDeckAvail = NULL;
    int nextPlayerAvail = NULL;
    //First, check the location of the next available card in the deck

    for(int i = 0; i < DECK_SIZE; i++) {
        //Checks for a card with a name that isn't null.
        if(deck[i].name != NULL) {
            nextDeckAvail = i;
            break;
        }
    }

    //Return false if there aren't any cards left to draw so the game can re shuffle the deck
    if(nextDeckAvail == NULL) {
        return 1;
    }

    //If that passed find the next avalable slot for the player to pick a card from
    for(int i = 0; i < PLAYER_MAX_CARDS; i++) {
        if(p.deck[i].name == NULL) {
            nextPlayerAvail = i;
            break;
        }
    }

    //Return 2 if the player can't draw another card
    if(nextPlayerAvail == NULL) {
        return 2;
    }

    //Now give the player the next available card if function is still running
    p.deck[nextPlayerAvail].name = deck[nextDeckAvail].name;
    p.deck[nextPlayerAvail].color = deck[nextDeckAvail].name;

    //Set the card that has been taken from the deck's name to null to indicate that it has been used
    deck[nextDeckAvail].name == NULL;

    //Return 0 to indicate that the function funished running properly
    return 0;
}

//Function that checks if a player has the nessicary cards to not need to draw 4 from an OR card. Returns true if the player has the card needed.
bool checkOR(player targeted, card lastPlayed) {
    //Go one by one till a valid card is found
    for(int i = 0; targeted.deck[i].name != NULL; i++) {
        if(targeted.deck[i].name == lastPlayed.name) {
            return true;
        } else if(targeted.deck[i].color == lastPlayed.color) {
            return true;
        }
    }

    //If none of those pass by the time the null cards are reached in the player's deck say that it couldn't find a valid card
    return false;
}

//Function that checks if a player has the nessicary cards to not need to draw 4 from an OR card. Returns true if the player has the card needed.
bool checkAND(player targeted, card lastPlayed) {
    //Go one by one till a valid card is found
    for(int i = 0; targeted.deck[i].name != NULL; i++) {
        if(targeted.deck[i].name == lastPlayed.name && targeted.deck[i].color == lastPlayed.color) {
            return true;
        }
    }

    //If none of those pass by the time the null cards are reached in the player's deck say that it couldn't find a valid card
    return false;
}

//Function that handles the reverse card
void handleReverse(bool *gameReversed, int *currentPlayer, int playerCount) {
    if(playerCount == 2) {
        *currentPlayer = *currentPlayer - 1;
    } else {
        *gameReversed = true;
    }
    
    return;
}

