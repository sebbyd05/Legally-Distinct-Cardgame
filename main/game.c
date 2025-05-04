#include<stdio.h>
#include<string.h>
#include"definitions/gameTypes.h"
#include"definitions/gameRules.h"
#include"functions/createDeck.h"
#include"functions/cardHandlers.h"

//Main game function
int main() {
    //Start by getting the number of players for the game
    int numPlayers = NULL;
    //Loop to ensure valid player number entry
    while(1 == 1) {
        printf("Enter how many players are playing: ");
        scanf("%d", &numPlayers);

        if(numPlayers > MAX_PLAYERS) {
            printf("\nThat is too many players! Please enter a value below %d!\n", (int)MAX_PLAYERS);
        } else if (numPlayers == 1) {
            printf("\nThe game isn't going to be very fun with only you!\n");
        } else if (numPlayers == 0) {
            printf("\nNo one wants to play. Closing program!\n");
            return 0;
        } else if (numPlayers < 0) {
            printf("\nYou can't have a negative amount of players! Sorry!\n");
        } else {
            break;
        }
    }

    //Create the player array with however many players the user wants
    player players[numPlayers];

    //Initalize the players, ask for their names.
    for(int i = 0; i < numPlayers; i++) {
        printf("\nEnter player #%d's name: ", (i+1));
        fgets(players[i].playerName, MAX_PLAYER_NAME, stdin);
    }
}