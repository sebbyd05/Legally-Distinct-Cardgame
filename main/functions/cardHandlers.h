/*
A collection of functions that determine how cards and actions work
*/
#include"../definitions/gameTypes.h"
#include<stdio.h>
#include<stdbool.h> //Might be able to remove, depending on how I want to do it

//Function that checks if the card can be played. Returns true if it can be, returns false if it can't.
bool checkCardValid(card lastPlayed, card canidate) {
    if(lastPlayed.color == canidate.color) {
        return true;
    } else if(lastPlayed.name == canidate.name) {
        return true;
    } else if(lastPlayed.name == '\0') {
        return true;
    } else if(lastPlayed.color == 'S') {
        return true;
    } else if(canidate.color == 'S') {
        return true;
    }

    //Return false if the color or name don't match
    return false;
}

//Function that draws a card to the player's next available card slot. Returns 0 upon success. Returns 1 upon empty deck, returns 2 on player hand reaching max cap.
int drawCard(card deck[], player *p) {
    int nextDeckAvail = -1;
    int nextPlayerAvail = -1;
    //First, check the location of the next available card in the deck

    for(int i = 0; i < DECK_SIZE; i++) {
        //Checks for a card with a name that isn't null.
        if(deck[i].name != '\0') {
            nextDeckAvail = i;
            break;
        }
    }

    //Return false if there aren't any cards left to draw so the game can re shuffle the deck
    if(nextDeckAvail == -1) {
        return 1;
    }

    //If that passed find the next avalable slot for the player to pick a card from
    for(int i = 0; i < PLAYER_MAX_CARDS; i++) {
        if(p->deck[i].name == '\0') {
            nextPlayerAvail = i;
            break;
        }
    }

    //Return 2 if the player can't draw another card
    if(nextPlayerAvail == -1) {
        return 2;
    }

    //Now give the player the next available card if function is still running
    p->deck[nextPlayerAvail].name = deck[nextDeckAvail].name;
    p->deck[nextPlayerAvail].color = deck[nextDeckAvail].color;

    //Set the card that has been taken from the deck's info to \0 to indicate that it has been used
    deck[nextDeckAvail].name = '\0';
    deck[nextDeckAvail].color = '\0';

    //Increase the number of cards in a player's deck by 1.
    p->decksize += 1;

    //Return 0 to indicate that the function funished running properly
    return 0;
}

//Function that checks if a player has the nessicary cards to not need to draw 4 from an OR card. Returns true if the player has the card needed.
bool checkOR(player targeted, card lastPlayed) {
    //Go one by one till a valid card is found
    for(int i = 0; targeted.deck[i].name != '\0'; i++) {
        if(targeted.deck[i].name == lastPlayed.name) {
            return true;
        } else if(targeted.deck[i].color == lastPlayed.color) {
            return true;
        }
    }

    //If none of those pass by the time the \0 cards are reached in the player's deck say that it couldn't find a valid card
    return false;
}

//Function that checks if a player has the nessicary cards to not need to draw 4 from an OR card. Returns true if the player has the card needed.
bool checkAND(player targeted, card lastPlayed) {
    //Go one by one till a valid card is found
    for(int i = 0; targeted.deck[i].name != '\0'; i++) {
        if(targeted.deck[i].name == lastPlayed.name && targeted.deck[i].color == lastPlayed.color) {
            return true;
        }
    }

    //If none of those pass by the time the \0 cards are reached in the player's deck say that it couldn't find a valid card
    return false;
}

//Function that handles the reverse card. Essentially tricks the next player function.
void handleReverse(bool gameReversed, int *currentPlayer) {
    if(gameReversed) {
        *currentPlayer = *currentPlayer + 1;
    } else {
        *currentPlayer = *currentPlayer - 1;
    }
    
    return;
}

//Function that prints a card Option 0 prints entire card, option 1 prints card color name.
void printCard(card c, bool colorOnly) {
    switch(c.color) {
        case 'R':
            if(!colorOnly) {
                printf("Red %c", c.name);
            } else {
                printf("Red");
            }
            break;
        
        case 'G':
            if(!colorOnly) {
                printf("Green %c", c.name);
            } else {
                printf("Green");
            }
            break;

        case 'B':
            if(!colorOnly) {
                printf("Blue %c", c.name);
            } else {
                printf("Blue");
            }
            break;

        case 'Y':
            if(!colorOnly) {
                printf("Yellow %c", c.name);
            } else {
                printf("Yellow");
            }
            break;

        case 'S':
            switch(c.name) {
                case 'A':
                    printf("And");
                    break;

                case 'O':
                    printf("Or");
                    break;

                case 'N':
                    printf("Not");
                    break;

                case 'R':
                    printf("Reverse");
                    break;
            }
            break;
    }

    return;
}

//Function that prints the player's name and hand, prints number of card in stack if the isUp bool is true.
void printPlayerHand(player p, bool isUp) {
    //Print the name of the player who's deck we are about to see.
    printf("\n%s's hand:\n", p.playerName);
    //Print each available card
    for(int c = 0; c < p.decksize; c++) {
        //If the player that gets to select a card is up, put the numbers next to their cards to help them choose
        if(isUp == true) {
            printf("\n[%d] ", c);
        } else {
            printf("\n");
        }
        //Print the card name based on atributes
        switch(p.deck[c].color) {
            case 'R':
                printf("Red %c", p.deck[c].name);
                break;
            
            case 'G':
                printf("Green %c", p.deck[c].name);
                break;

            case 'B':
                printf("Blue %c", p.deck[c].name);
                break;

            case 'Y':
                printf("Yellow %c", p.deck[c].name);
                break;

            case 'S':
                switch(p.deck[c].name) {
                    case 'A':
                        printf("And");
                        break;

                    case 'O':
                        printf("Or");
                        break;

                    case 'N':
                        printf("Not");
                        break;

                    case 'R':
                        printf("Reverse");
                        break;
                }
                break;
        }
    }

    return;
}

//Function that deletes the card the player just played
void playCard(player *p, int cardToPlay) {
    //Set the card the player just played to the last card in the deck
    p->deck[cardToPlay].color = p->deck[(p->decksize - 1)].color;
    p->deck[cardToPlay].name = p->deck[(p->decksize - 1)].name;

    //Set the last card in the player's deck to the empty state
    p->deck[(p->decksize - 1)].color = '\0';
    p->deck[(p->decksize - 1)].name = '\0';

    //Decrease the player's current deck size by one
    p->decksize -= 1;

    //Return to the program
    return;
}
