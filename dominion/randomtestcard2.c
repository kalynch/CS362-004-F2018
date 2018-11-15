/* -----------------------------------------------------------------------
 * File: randomtestcard2.c
 * Author: Kaitlin Lynch 
 * Include the following lines in your makefile:
 *
 * randomtestcard2: randomtestcard2.c dominion.o rngs.o
 *      gcc -o rrandomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

// OUTPOST
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

int temp;

int actionCards[] = {adventurer, 
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
                      // outpost, COMMENTED OUT FOR THIS TEST. 18 cards remaining.
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
  int maxTimesToRunTest = 10;
  struct gameState G, testG;
  int printStatusFlag = 1;
  srand(time(0));

  // Assigned in test
  int expectedOutpostFlag, 
      actualOutpostFlag,
      expectedPlayedCardCountChange,
      actualPlayedCardCountChange,
      player, 
      i,
      outpostFlagBeforeTurn,
      playedCardCountBeforeTurn;

  /************************************************************************************
  * RANDOM ASSIGNMENTS
  ************************************************************************************/
  int numPlayers = generateRandomInRange(2, 4);
  int k[10]; // action card deck in middle 

  // Outpost must be in action card deck
  k[0] = outpost;

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

  // Initialize to avoid seg fault
  G.playedCardCount = 0;
  G.outpostPlayed = 0;

  printf("----------------- Random Testing Outpost ----------------\n");

  while (numTimesTestRun < maxTimesToRunTest)
  {
    if(printStatusFlag)
      printf("Run #%d\n", numTimesTestRun+1);

    // Copy the game state to a test
    memcpy(&testG, &G, sizeof(struct gameState));
    // Locate the current player whose turn it is
    player = whoseTurn(&testG);
    // Initialize variables
    expectedOutpostFlag = 1; // Outpost flag is incremented
    expectedPlayedCardCountChange = 1; // One card is discarded
    actualOutpostFlag = 0;
    actualPlayedCardCountChange = 0;

    // // The game starts with each player having 10 cards in his/her deck.
    // // The player then draws five of these cards into his/her hand.
    // // The number of card in the player's individual deck increases as the 
    // // players buy and occassionally discard cards. For the sake of this test, 
    // // I've assumed the valid number of cards a player may have in his or her deck 
    // // at one time is between 0 and 15 (with the remaining five cards in the player's hand).
    // testG.deckCount[player] = generateRandomInRange(3, 15);

    // // Populate the player's deck
    // // By not placing limits on the frequency with which a given card may be added
    // // to the deck, this deck could represent an invalid game state. 
    // // This is permissible because the behavior of smithy is not determined by the
    // // actual limits to the number of cards of each card type and the number of valid
    // // configurations is much greater than the number of invalid ones.
    // if(printStatusFlag)
    //   printf("......populating the player's deck\n");

    // for (i = 0; i < testG.deckCount[player]; i++)
    // {
    //   int newCardIndex = generateRandomInRange(0, 25);
    //   testG.deck[player][i] = totalPossibleCards[newCardIndex];
    // }

    // // Check how many cards are in the player's hand and discard pile
    outpostFlagBeforeTurn = testG.outpostPlayed; 
    playedCardCountBeforeTurn = testG.playedCardCount;

    // Play the card
    if(printStatusFlag)
      printf("......playing the card\n");

    // Note that only the outpost variable and game state are used in this card effect
    // the other variables are merely serving as placeholders in the function call.
    temp = cardEffect(outpost, copper, copper, copper, &testG, 0 , 0);

    actualOutpostFlag = testG.outpostPlayed - outpostFlagBeforeTurn;
    actualPlayedCardCountChange = testG.playedCardCount - playedCardCountBeforeTurn;

    if(printStatusFlag)
      printf("......comparing the results\n");

   if (expectedOutpostFlag !=  actualOutpostFlag || expectedPlayedCardCountChange != actualPlayedCardCountChange)
   {
      printf("\n >>>>> FAILURE: Random Outpost Tests failed <<<<<\n");
      printf(" >>>>> Expected Outpost Flag: %d | Actual Outpost Flag: %d <<<<<\n", expectedOutpostFlag, actualOutpostFlag);
      printf(" >>>>> Expected Cards Discarded: %d | Actual Cards Discarded: %d <<<<<\n\n", expectedPlayedCardCountChange, actualPlayedCardCountChange);
      return 0;
   }
   else numTimesTestRun++;
  }
  
  printf("\n >>>>> SUCCESS: Random Outpost Tests successful <<<<<\n\n");

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