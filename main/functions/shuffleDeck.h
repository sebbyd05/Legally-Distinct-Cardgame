/*
Header file that provides a function that shuffles the cards 10,000 times.
*/

#include"createDeck.h"
#include<stdlib.h>
#include<time.h>

void shuffleDeck(card deck[]) {
    card temp;
    int cardA, cardB;
    srand((int)time(0));
    //Create a loop to ensure it runs a certain number of times
    for(int i = 0; i < MINIMUM_SHUFFLE; i++) {
        cardA = rand() % DECK_SIZE;
        cardB = rand() % DECK_SIZE;

        temp = deck[cardA];
        deck[cardA] = deck[cardB];
        deck[cardB] = temp;
    }

    return;
}