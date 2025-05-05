#include"functions/shuffleDeck.h" //This includes all nessicary libraries!

//Main game function
int main() {
    //Start by getting the number of players for the game
    int numPlayers;
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
    
    //Eat the \n from the last line to ensure it runs properly.
    getchar();
    
    for(int i = 0; i < numPlayers; i++) {
        //Loop to continue to ask for a name if none is input.
        while(1 == 1) {
            printf("\nEnter player #%d's name: ", (i+1));
            fgets(players[i].playerName, MAX_PLAYER_NAME, stdin);
            //Does double duty, if the player's name is invalid the function will notice, if it is valid it sets all the card names to NULL.
            if(initalizePlayer(&players[i]) == 0) {
                break;
            } else {
                printf("You must input a valid name!");
            }
        }
    }

    //Now that the players have been initalized, create the deck for the game.
    card deck[DECK_SIZE];
    createDeck(deck);
    shuffleDeck(deck);

    //Now give each player however many cards they are supposed to start with
    for(int p = 0; p < numPlayers; p++) {
        for(int c = 0; c < INITAL_DRAW; c++) {
            drawCard(deck, &players[p]);
        }
    }

    //Create a boolean to tell the game if it should continue.
    bool continueGame = true;
    while(continueGame == true) {
        //Print the available cards for the players.
        for(int p = 0; p < numPlayers; p++) {
            //Print the name of the player who's deck we are about to see.
            printf("\n%s's hand:\n", players[p].playerName);
            //Print each available card
            for(int c = 0; c < players[p].decksize; c++) {
                printf("\n[%d] ", c);
                switch(players[p].deck[c].color) {
                    case 'R':
                        printf("Red %c", players[p].deck[c].name);
                        break;
                    
                    case 'G':
                        printf("Green %c", players[p].deck[c].name);
                        break;

                    case 'B':
                        printf("Blue %c", players[p].deck[c].name);
                        break;

                    case 'Y':
                        printf("Yellow %c", players[p].deck[c].name);
                        break;

                    case 'S':
                        switch(players[p].deck[c].name) {
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
            printf("\n");
        }

        //Now that the cards the player has are printed, determine what user's turn it is and ask them for a move

    }
    
    return 0;
}