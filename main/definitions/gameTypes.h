//Defines the structures that are available for the program
typedef struct card_t {
    char name;
    char color;
} card;

typedef struct player_t {
    char playerName[20];
    int decksize;
    card deck[]; //Could make this part a linked list or dynamic thing
} player;
