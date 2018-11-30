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
#include <stdlib.h>
#include <time.h>

int generateRandomInRange(int, int);
void shuffleCards(int[], int);
int isTreasure(int);

int temp;

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

int main() 
{
  // Set Up
  int seed = 1000;
  int numTimesTestRun = 0;
  int maxTimesToRunTest = 1;
  struct gameState G, testG;
  int printStatusFlag = 1;
  srand(time(0));

  // Assigned in test
  int expectedTreasuresDrawn, 
      treasureDrawn,
      player, 
      i,
      handCountBeforeTurn,
      discardBeforeTurn,
      minCardsDiscarded,
      maxCardsDiscarded,
      actualCardsDiscarded;

  /************************************************************************************
  * RANDOM ASSIGNMENTS
  ************************************************************************************/
  int numPlayers = generateRandomInRange(2, 4);
  int k[10]; // action card deck in middle 

  // Adventurer must be in action card deck
  k[0] = adventurer;

  // Shuffle the action card deck
  shuffleCards(actionCards, 18);

  // Populate action card deck with the first 9 cards from
  // the shuffled deck
  for (i = 1; i < 10; i++)
  {
    k[i] = actionCards[i];
  }
    
  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);

  printf("----------------- Random Testing Adventurer ----------------\n");

  while (numTimesTestRun < maxTimesToRunTest)
  {
    if(printStatusFlag)
      printf("Run #%d\n", numTimesTestRun+1);

    // Copy the game state to a test
    memcpy(&testG, &G, sizeof(struct gameState));
    // Locate the current player whose turn it is
    player = whoseTurn(&testG);
    // Initialize variables
    expectedTreasuresDrawn = 0;
    treasureDrawn = 0;
    minCardsDiscarded = 0;
    maxCardsDiscarded = testG.deckCount[player];

    // The game starts with each player having 10 cards in his/her deck.
    // The player then draws five of these cards into his/her hand.
    // The number of card in the player's individual deck increases as the 
    // players buy and occassionally discard cards. For the sake of this test, 
    // I've assumed the valid number of cards a player may have in his or her deck 
    // at one time is between 5 and 15 (with the remaining five cards in the player's hand).
    // if the deck was empty, adventurer would shuffle the discards. This is not being tested here.
    testG.deckCount[player] = generateRandomInRange(5, 15);

    // Populate the player's deck
    // By not placing limits on the frequency with which a given card may be added
    // to the deck, this deck could represent an invalid game state. 
    // This is permissible because the behavior of adventurer is not determined by the
    // actual limits to the number of cards of each card type and the number of valid
    // configurations is much greater than the number of invalid ones.
    if(printStatusFlag)
      printf("......populating the player's deck\n");

    for (i = 0; i < testG.deckCount[player]; i++)
    {
      int newCardIndex = generateRandomInRange(0, 25);
      testG.deck[player][i] = totalPossibleCards[newCardIndex];

      // Count each treasure card added to the player's deck
      if (isTreasure(testG.deck[player][i]))
      {
        expectedTreasuresDrawn++;
      }
    }

    // The adventurer only allows two treasure cards max to be drawn.
    // Set expected accordingly
    if (expectedTreasuresDrawn > 2)
      expectedTreasuresDrawn = 2;

    // Check how many cards are in the player's hand
    handCountBeforeTurn = testG.handCount[player];

    // Check how many cards are in the discard
      discardBeforeTurn = testG.discardCount[player];

    // Play the card
    if(printStatusFlag)
      printf("......playing the card\n");

    // Note that only the adventure variable and game state are used in this card effect
    // the other variables are merely serving as placeholders in the function call.
    temp = cardEffect(adventurer, copper, copper, copper, &testG, 0 , 0);

    treasureDrawn = testG.handCount[player] - handCountBeforeTurn;
    actualCardsDiscarded = testG.discardCount[player] - discardBeforeTurn;

    // Game should prevent and does not
    if (treasureDrawn < 0)
      treasureDrawn = 0;

   // Reset max discard based on treasures drawn
      maxCardsDiscarded = testG.deckCount[player] - treasureDrawn;

    if(printStatusFlag)
      printf("......comparing the results\n");

   if (expectedTreasuresDrawn !=  treasureDrawn || actualCardsDiscarded < minCardsDiscarded || actualCardsDiscarded > maxCardsDiscarded)
   {
       if( expectedTreasuresDrawn !=  treasureDrawn)
       {
           printf("\n >>>>> FAILURE: Random Adventurer Tests failed <<<<<\n");
           printf(" >>>>> Expected Treasures: %d | Drawn Treasures: %d <<<<<\n\n", expectedTreasuresDrawn, treasureDrawn);
       }

       if( actualCardsDiscarded < minCardsDiscarded || actualCardsDiscarded > maxCardsDiscarded  )
       {
           printf("\n >>>>> FAILURE: Random Adventurer Tests failed <<<<<\n");
           printf(" >>>>> Permissible to dicard between %d and %d cards | Actually Discarded: %d <<<<<\n\n", minCardsDiscarded, maxCardsDiscarded, actualCardsDiscarded);
       }

      return 0;
   }
   else {

       if (printStatusFlag)
       {
           printf ("The number of treasures drawn was: %d", treasureDrawn);
           printf("The number of cards discarded was: %d", actualCardsDiscarded);
           printf("The max permissible discards waas: %d", maxCardsDiscarded);
       }
       numTimesTestRun++;
   }
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
  int i;
  for (i = 0; i < numCards; i++)
  {
      // Valid indixes are 0 to number of cards in array less one
      int j = i + generateRandomInRange(0, numCards-1);
      temp = cardArray[j];
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
    if (card == copper || card == silver || card == gold)
      return 1;
    else return 0;
 }
