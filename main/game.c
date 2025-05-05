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
    int playerNext = 1;
    card topCard;
    card oldTopCard;

    //Initalize a top card that indicates that any card is valid to be played on top of.
    topCard.name = '\0';
    topCard.color = '\0';

    //Create a boolean to tell the game if it should continue.
    bool continueGame = true;
    bool reverse = false;
    bool outOfCards = false;
    bool repeatPlayer = false;
    
    //While loop to contain the main part of the game
    while(continueGame == true) {
        bool skipNext = false;
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
            printCard(topCard, false);
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
                if(drawCard(deck, &players[playerTurn]) == 1) {
                    outOfCards = true;
                }
                break;
            } else if(cardChoice >= 0 && cardChoice < players[playerTurn].decksize) {
                if(checkCardValid(topCard, players[playerTurn].deck[cardChoice])) {
                    //Set the previous top card to be the current top card so we can change it out (for NOT or Reverse)
                    oldTopCard = topCard;
                    //Set the top card to be the card the player just played.
                    topCard = players[playerTurn].deck[cardChoice];
                    //Call the function to remove the used card from the player's hand
                    playCard(&players[playerTurn], cardChoice);
                    //Exit the while loop
                    break;
                } else {
                    printf("\nInvalid choice, cannot place ");
                    printCard(players[playerTurn].deck[cardChoice], false);
                    printf(" on ");
                    printCard(topCard, false);
                    printf("\n");
                }
            } else {
                printf("\nThat is not an option!\n");
            }
        }
        
        //Check if the player has won, announce and break if they have.
        if(players[playerTurn].decksize < 1) {
            printf("\n\n%s has won!!\n", players[playerTurn].playerName);
            continueGame = false;
            break;
        }

        //Add some clauses to handle the special cards, only checks color first to save compute.
        if(topCard.color == 'S') {
            //Follow a branch based on which special card is played.
            if(topCard.name == 'O') {
                while (1 == 1) {
                    int cardChoice = -2;
                    printPlayerHand(players[playerTurn], true);
                    printf("\nChoose the card to play with OR from 0 to %d: ", (players[playerTurn].decksize -1));
                    scanf("%d", &cardChoice);
                    //Check if the user's input is valid, perform normal steps if it is.
                    if(cardChoice >= 0 && cardChoice < players[playerTurn].decksize) {
                        //Set the top card to be the card the player just played.
                        topCard = players[playerTurn].deck[cardChoice];
                        //Call the function to remove the used card from the player's hand
                        playCard(&players[playerTurn], cardChoice);
                        //Exit the while loop
                        break;
                    } else {
                        printf("\nThat is not a valid selection, please try again!\n");
                    }
                }

                //Check if the player won by playing that card
                if(players[playerTurn].decksize < 1) {
                    printf("\n\n%s has won!!\n", players[playerTurn].playerName);
                    continueGame = false;
                    break;
                }
                
                //See if the next user has a card that fits the OR rules, make the next player pick however many they need to if they don't:
                if(!checkOR(players[playerNext], topCard)) {
                    printf("%s has no cards that match ", players[playerNext].playerName);
                    printCard(topCard, true);
                    printf("or %c\n OR penalty, Draw %d", topCard.name, (int)PENALTY_QUANTITY);
                    //Make the next player draw that many cards
                    for(int i = 0; i < PENALTY_QUANTITY; i++) {
                        if(drawCard(deck, &players[playerNext]) == 1) {
                            outOfCards = true;
                        }
                    }
                }
                //Just continue if the player does satisfy the requirements.
            } else if(topCard.name == 'A') {
                while (1 == 1) {
                    int cardChoice = -2;
                    printPlayerHand(players[playerTurn], true);
                    printf("\nChoose the card to play with AND from 0 to %d: ", (players[playerTurn].decksize -1));
                    scanf("%d", &cardChoice);
                    //Check if the user's input is valid, perform normal steps if it is.
                    if(cardChoice >= 0 && cardChoice < players[playerTurn].decksize) {
                        //Set the top card to be the card the player just played.
                        topCard = players[playerTurn].deck[cardChoice];
                        //Call the function to remove the used card from the player's hand
                        playCard(&players[playerTurn], cardChoice);
                        //Exit the while loop
                        break;
                    } else {
                        printf("\nThat is not a valid selection, please try again!\n");
                    }
                }

                //Check if the player won by playing that card.
                if(players[playerTurn].decksize < 1) {
                    printf("\n\n%s has won!!\n", players[playerTurn].playerName);
                    continueGame = false;
                    break;
                }

                //See if the next user has a card that fits the OR rules, make the next player pick however many they need to if they don't:
                if(!checkAND(players[playerNext], topCard)) {
                    printf("%s has no cards that match ", players[playerNext].playerName);
                    printCard(topCard, true);
                    printf("and %c\n AND penalty, Draw %d", topCard.name, (int)PENALTY_QUANTITY);
                    //Make the next player draw that many cards
                    for(int i = 0; i < PENALTY_QUANTITY; i++) {
                        if(drawCard(deck, &players[playerNext]) == 1) {
                            outOfCards = true;
                        }
                    }
                }
                //Just continue if the player does satisfy the requirements.
            } else if(topCard.name == 'N') {
                //Check if the player won by playing that card before doing anything else
                if(players[playerTurn].decksize < 1) {
                    printf("\n\n%s has won!!\n", players[playerTurn].playerName);
                    continueGame = false;
                    break;
                }
                //Revert to the previous top card as it just skips player
                topCard = oldTopCard;
                //Tell the system that determines what player goes next to true.
                skipNext = true;
            } else if(topCard.name == 'R') {
                //Check if the player won by playing that card. If this isn't done here future checking will be very messed up.
                if(players[playerTurn].decksize < 1) {
                    printf("\n\n%s has won!!\n", players[playerTurn].playerName);
                    continueGame = false;
                    break;
                }

                //Set the card to whatever was on top before the reverse was played
                topCard = oldTopCard;
                //Make the reverse setting whatever it wasn't
                reverse = !reverse;
                //Set the repeat player flag to true so the player that played the reverse goes again.
                repeatPlayer = true;
            }
        }

        //Go to the next player
        //If the reverse bool isn't activated:
        if(!repeatPlayer){
            if(!skipNext) {
                if(!reverse) {
                    //Step up the number of players by 1
                    playerTurn++;
                    //Modulo the player turn counter by the number of players to loop it back around when it goes over the number of players
                    playerTurn = playerTurn % numPlayers;
                    //Set the playerNext variable to whatever player turn is plus 1
                    playerNext = (playerTurn + 1);
                    //Modulo that for the same reason.
                    playerNext = playerNext % numPlayers;
                } else {
                    //If it is in reverse, do the same except backwards, ensuring that the result of modulo won't be negative.
                    playerTurn--;
                    playerTurn = (playerTurn + numPlayers) % numPlayers;
                    playerNext = (playerTurn - 1 + numPlayers);
                    playerNext = playerNext % numPlayers;
                }
            } else {
                //If the skip next clause is active this needs to be done twice as much, and the skip next needs to be set to false
                if(!reverse) {
                    playerTurn += 2;
                    //Modulo that by the player cound to ensure that it loops back around
                    playerTurn = playerTurn % numPlayers;
                    //Give the player next the same treatment
                    playerNext = (playerTurn + 1) % numPlayers;
                    //Set skip next to false so it doesn't trigger again
                    skipNext = false;
                } else {
                    playerTurn -= 2;
                    playerTurn = (playerTurn + numPlayers) % numPlayers;
                    playerNext = (playerTurn - 1 + numPlayers) % numPlayers;
                    //Set skip next to be false
                    skipNext = false;
                }
            }
        } else {
            //Set the repeat player flag to false and do nothing.
            repeatPlayer = false;
        }
        
        //If the deck is out of cards, end the game and declare a winner.
        if(outOfCards) {
            //Create a variable that stores whichever player in the players array has the least cards
            int leastCards = 0;
            //Search through the players to see which has the least amount of cards
            for(int i = 0; i < numPlayers; i++) {
                if(players[i].decksize < players[leastCards].decksize) {
                    leastCards = i;
                }
            }

            //Now that we know who has the least amount of cards, announce that the game is over.
            printf("\n\nThe deck has ran out of cards! The game is over!\n");
            printf("%s wins, as they only had %d cards left!", players[leastCards].playerName, players[leastCards].decksize);

            //Set continue game to false, and break out of the loop.
            continueGame = false;
            break;
        }
        

    } //Continue game loop end
    
    return 0;
}