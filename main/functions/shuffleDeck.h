/*
Header file that provides a function that shuffles the cards 10,000 times.
*/

#include"../definitions/gameTypes.h"
#include<stdlib.h>
#include<time.h>
#define TIMES 10000

void shuffleDeck(card deck[]) {
    card temp;
    int cardA, cardB;
    srand((int)time(0));
    //Create a loop to ensure it runs a certain number of times
    for(int i = 0; i < TIMES; i++) {
        cardA = rand() % 100;
        cardB = rand() % 100;

        temp = deck[cardA];
        deck[cardA] = deck[cardB];
        deck[cardB] = temp;
    }

    return;
}