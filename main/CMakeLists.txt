cmake_minimum_required(VERSION 3.10)
project(LegallyDistinctCardGame C)

set(CMAKE_C_STANDARD 99)

include_directories(main main/definitions main/functions)

add_executable(game
    main/game.c
    main/functions/cardHandlers.h
    main/functions/createDeck.h
    main/functions/shuffleDeck.h
    main/definitions/gameRules.h
    main/definitions/gameTypes.h
)