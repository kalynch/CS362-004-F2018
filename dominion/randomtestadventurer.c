/* -----------------------------------------------------------------------
 * File: randomtestadventurer.c
 * Author: Kaitlin Lynch 
 * Include the following lines in your makefile:
 *
 * randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
 *      gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int generateRandomInRange(int, int);
void shuffleCards(int[], int);
int isTreasure(int);

int main() 
{
  // Set Up
  int testsFailed = 0;
  int seed = 1000;
  int numTimesTestRun = 0;
  int maxTimesToRunTest = 100;
  struct gameState G, testG;

  int actionCards[] = {//adventurer, COMMENTED OUT FOR THIS TEST. 18 cards remaining.
                        council_room, 
                        feast, 
                        gardens, 
                        mine, 
                        remodel, 
                        smithy, 
                        village, 
                        baron, 
                        great_hall, 
                        minion, 
                        steward, 
                        tribute, 
                        ambassador, 
                        cutpurse, 
                        embargo, 
                        outpost, 
                        sea_hag, 
                        treasure_map};

  int victoryCards[3] = {province,
                        duchy,
                        estate};

  int treasureCards[3] = {gold,
                          copper,
                          silver};

  int totalPossibleCards[25] = {adventurer, 
                                council_room, 
                                feast, 
                                gardens, 
                                mine, 
                                remodel, 
                                smithy, 
                                village, 
                                baron, 
                                great_hall, 
                                minion, 
                                steward, 
                                tribute, 
                                ambassador, 
                                cutpurse, 
                                embargo, 
                                outpost, 
                                sea_hag, 
                                treasure_map,
                                province,
                                duchy,
                                estate,
                                gold,
                                copper,
                                silver};

  // Assigned in test
  int expectedTreasuresDrawn,
      expectedCardsDiscarded, 
      treasureDrawn,
      cardsDiscarded, 
      i, 
      player, 
      temp, 
      handCountBeforeTurn,
      discardBeforeTurn;

  /************************************************************************************
  * RANDOM ASSIGNMENTS
  ************************************************************************************/
  int numPlayers = generateRandomInRange(2, 4);
  int k[10]; // action card deck in middle 

  // Adventurer must be in action card deck
  k[i] = adventurer;

  // Shuffle the action card deck
  shuffleCards(actionCards, 18);

  // Populate action card deck with the first 9 cards from
  // the shuffled deck
  for (i = 1; i < 10; i++)
  {
    k[i] = actionCards[i];
  }
    
  // initialize a game state and player cards
  initializeGame(numPlayer, k, seed, &G);

  printf("----------------- Random Testing Adventurer ----------------\n");

  while (numTimesTestRun < maxTimesToRunTest)
  {
    // Copy the game state to a test
    memcpy(&testG, &G, sizeof(struct gameState));
    // Locate the current player whose turn it is
    player = whoseTurn(&testG);
    // Initialize variables
    expectedTreasuresDrawn = 0;
    expectedCardsDiscarded = 0;
    treasureDrawn = 0;

    // The game starts with each player having 10 cards in his/her deck.
    // The player then draws five of these cards into his/her hand.
    // The number of card in the player's individual deck increases as the 
    // players buy and occassionally discard cards. For the sake of this test, 
    // I've assumed the valid number of cards a player may have in his or her deck 
    // at one time is between 5 and 15 (with the remaining five cards in the player's hand);
    testG.deckCount[player] = generateRandomInRange(10, 20);

    // Populate the player's deck
    // By not placing limits on the frequency with which a given card may be added
    // to the deck, this deck could represent an invalid game state. 
    // This is permissible because the behavior of adventurer is not determined by the
    // actual limits to the number of cards of each card type and the number of valid
    // configurations is much greater than the number of invalid ones.
    for (i = 0; i < testG.deckCount[player]; i++)
    {
      int newCardIndex = generateRandomInRange(0, 25);
      testG.deck[player][i] = totalPossibleCards[newCardIndex];

      // Count each treasure card added to the player's deck
      if (isTreasure(totalPossibleCards[newCardIndex]))
        expectedTreasuresDrawn++;
    }

    // The adventurer only allows two treasure cards max to be drawn.
    // Set expected accordingly
    if (expectedTreasuresDrawn > 2)
      expectedTreasuresDrawn = 2;

    // Cards drawn before the treasure cards are located are discarded
    // If a player has less than two treasure cards in the deck, 
    // all the non-treasure card would be discarded
    if (expectedTreasuresDrawn < 2)
      expectedCardsDiscarded = testG.deckCount[player] - expectedTreasuresDrawn;

    // If there are two treasures to draw, loop through the deck to see how many cards are
    // discarded and increment expectedCardsDiscarded accordingly
    else
    {
      for (i = 0; i < testG.deckCount[player]; i++)
      {
       
        // If all the expected treasure has been drawn, stop looking
        if(treasureDrawn == expectedTreasuresDrawn)
          break;
        // If it's treasure, increase the count
        else if(isTreasure(testG.deck[player][i]))
          treasureDrawn++;
        // If it's not treasure and the player is still drawing, expect to discard it
        else expectedCardsDiscarded++;
      }
    }

    // Check how many cards are in the player's hand and the discard before the turn
    handCountBeforeTurn = testG.handCount[player];
    discardBeforeTurn = testG.discardCount[player];

    // Play the card
    temp = cardEffect(adventurer, copper, copper, copper, &testG, 0 , 0);

    //
    treasureDrawn = testG.handCount[player] - handCountBeforeTurn;
    cardsDiscarded = testG.discardCount[player] - discardBeforeTurn;

     if (expectedTreasuresDrawn !=  treasureDrawn || expectedCardsDiscarded != cardsDiscarded)
     {
        printf("\n >>>>> FAILURE: Random Adventurer Tests failed <<<<<\n\n");
        return 0;
     }
     else numTimesTestRun++;
  }
  
  printf("\n >>>>> SUCCESS: Random Adventurer Tests successful <<<<<\n\n");

  return 0;
}

/************************************************************************************
 * Name: generateRandomInRange
 * Descirption: Generates a random integer in a specified range.
 * Parameters: low value, high value
 * Return: random integer
 * Source: coursework for OS
 ************************************************************************************/
int generateRandomInRange(int low, int high)
{
    int num = (rand() % (high - low + 1)) + low;
    return num;
}


/************************************************************************************
 * Name: shuffleCards
 * Descirption: Randomly shuffles the cards in the list
 * Parameters: none
 * Return: none
 ************************************************************************************/
void shuffleCards(int cardArray[], int numCards)
{
    for (i = 0; i < numCards; i++)
    {
        // Valid indixes are 0 to number of cards in array less one
        int j = i + generateRandomInRange(0, numCards-1);
        int = cardArray[j];
        cardArray[j] = cardArray[i];
        cardArray[i] = temp;
    }
}


/************************************************************************************
 * Name: isTreasure
 * Descirption: Returns 1 if the card is treasure or 0 if not
 * Parameters: card
 * Return: 1 or 0
 ************************************************************************************/
 int isTreasure(int card)
 {
    for (i = 0; i < 3; i++)
    {
      if (card == treasureCards[i])
        return 1;
    }

    return 0;
 }