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

    //Create variables that should persist across turns
    int playerTurn = 0;
    card topCard;

    //Initalize a top card that indicates that any card is valid to be played on top of.
    topCard.name = '\0';
    topCard.color = '\0';

    //Create a boolean to tell the game if it should continue.
    bool continueGame = true;
    while(continueGame == true) {
        //Print the available cards for the players.
        for(int p = 0; p < numPlayers; p++) {
            //Call the display player hand function
            printPlayerHand(players[p], (p == playerTurn));
            printf("\n");
        }

        //Print the card that's on the top of the pile
        if(topCard.name == '\0') {
            printf("\nCard pile is empty.\n");
        } else {
            printf("\nTop of card pile is: ");
            printCard(topCard);
            printf("\n");
        }
        
        //Begin a loop for the player to pick a card within
        while(1 == 1){ 
            int cardChoice = -2;
            //Prompt the current player for their choice for next card
            printf("\n%s, enter which card to play from 0 to %d. Enter -1 to draw a card: ", players[playerTurn].playerName, (players[playerTurn].decksize -1));
            scanf("%d", &cardChoice);
            //Check if the card played is valid or not, or see if they want to pick a card.
            if(cardChoice == -1) {
                drawCard(deck, &players[playerTurn]);
                break;
            } else if(cardChoice >= 0 && cardChoice < players[playerTurn].decksize) {
                if(checkCardValid(topCard, players[playerTurn].deck[cardChoice])) {
                    //Set the top card to be the card the player just played.
                    topCard = players->deck[cardChoice];
                    //Call the function to remove the used card from the player's hand
                    playCard(&players[playerTurn], cardChoice);
                    //Exit the while loop
                    break;
                } else {
                    printf("\nInvalid choice, cannot place ");
                    printCard(players[playerTurn].deck[cardChoice]);
                    printf(" on ");
                    printCard(topCard);
                    printf("\n");
                }
            } else {
                printf("\nThat is not an option!\n");
            }
        }
        //Now that the cards the player has are printed, determine what user's turn it is and ask them for a move

    }
    
    return 0;
}