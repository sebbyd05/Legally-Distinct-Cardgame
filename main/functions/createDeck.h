/*
Header file that creates things nessicary for the creation of the game deck and player deck
*/

#include"cardHandlers.h"

//Function that creates a full deck of 100 cards
void createDeck(card deck[DECK_SIZE]) {
    //Position for card being created sense using for loops for aspects
    int deckPos = 0;
    //Begin with a loop that goes through each card color to do the numbered cards: 0 - R, 1 - Y, 2 - G, 3 - B
    for(int color = 0; color < 4; color++) {
        for(int num = 0; num <= 9; num++) {
            switch (color) {
                //Checks wich color to make the card, makes the card that color, then sets the card to the ascii value of the charecter for that card
                case 0:
                    deck[deckPos].color = 'R';
                    deck[(deckPos + 1)].color = 'R';
                    deck[deckPos].name = (num + 48);
                    deck[(deckPos + 1)].name = (num + 48);

                    deckPos += 2;
                    break;
                case 1:
                    deck[deckPos].color = 'Y';
                    deck[(deckPos + 1)].color = 'Y';
                    deck[deckPos].name = (num + 48);
                    deck[(deckPos + 1)].name = (num + 48);

                    deckPos += 2;
                    break;
                case 2:
                    deck[deckPos].color = 'G';
                    deck[(deckPos + 1)].color = 'G';
                    deck[deckPos].name = (num + 48);
                    deck[(deckPos + 1)].name = (num + 48);

                    deckPos += 2;
                    break;
                case 3:
                    deck[deckPos].color = 'G';
                    deck[(deckPos + 1)].color = 'G';
                    deck[deckPos].name = (num + 48);
                    deck[(deckPos + 1)].name = (num + 48);

                    deckPos += 2;
                    break;
            }
        }
    }
    //Once it's done adding those cards, add the special cards. 0 - AND, 1 - OR, 2 - NOT, 3 - Reverse
    for(int type = 0; type < 4; type++) {
        for(int quant = 0; quant < 5; quant++) {
            deck[deckPos].color = 'S';
            switch(type) {
                case 0:
                    deck[deckPos].name = 'A';
                    deckPos++;
                    break;
                
                case 1:
                    deck[deckPos].name = 'O';
                    deckPos++;
                    break;
                
                case 2:
                    deck[deckPos].name = 'N';
                    deckPos++;
                    break;

                case 3:
                    deck[deckPos].name = 'R';
                    deckPos++;
                    break;
            }
        }
    }

    //We are now finished creating the deck, ready to return.

    return;
}

//Create player, if they have an invalid name return 1, if valid return 0.
int initalizePlayer(player *playerToMod) {
    //Check if the player doesn't have a name.
    if(playerToMod->playerName[0] == '\n') {
        return 1;
    }
    //Start by removing the player to modifie's name to not have the newline
    for(int i = 0; playerToMod->playerName[i] != '\0'; i++) {
        if(playerToMod->playerName[(i + 1)] == '\n') {
            playerToMod->playerName[(i + 1)] = '\0';
        }
    }

    //Next, initalize the player's cards to \0, which indicates an empty card.
    for(int i = 0; i < PLAYER_MAX_CARDS; i++) {
        playerToMod->deck[i].name = '\0';
    }

    //If all was successful, return 0
    return 0;
}