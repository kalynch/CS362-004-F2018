/* -----------------------------------------------------------------------
 * Author: Kaitlin Lynch Source: school cardTest4  example
 * Include the following lines in your makefile:
 *
 * cardtest2: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
    int expected, result, i;
    int testsFailed = 0;
    int seed = 1000;
    int numPlayer = 2;
    int player, temp, handCountBeforeTurn;
    int handpos = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;

    // initialize a game state and player cards
    initializeGame(numPlayer, k, seed, &G);

   printf("----------------- Testing Adventurer ----------------\n");
   printf("----------------- Test 1: Players hand gains 2 cards  ----------------\n");
   memcpy(&testG, &G, sizeof(struct gameState));
   player = whoseTurn(&testG);
   testG.deck[player][0] = copper;
   testG.deck[player][1] = silver;
   expected = 2;
   handCountBeforeTurn = testG.handCount[player];
   temp = cardEffect(adventurer, copper, copper, copper, &testG, handpos , 0);
   result = testG.handCount[player] - handCountBeforeTurn;
   if (expected !=  result)
   {
        printf("----------------- Test 1: Players hand gains 2 cards - FAILED  ----------------\n");
        testsFailed++;
   }

   printf("----------------- Test 2: Players hand gains 1 card  ----------------\n");
   memcpy(&testG, &G, sizeof(struct gameState));
   player = whoseTurn(&testG);
   testG.deck[player][0] = gold;
   for (i = 1; i < testG.deckCount[player]; i++)
   {
	testG.deck[player][i] = duchy;
   }
   expected = 1;
   handCountBeforeTurn = testG.handCount[player];
   temp = cardEffect(adventurer, copper, copper, copper, &testG, handpos , 0);
   result = testG.handCount[player] - handCountBeforeTurn;
   if (expected !=  result)
   {
        printf("----------------- Test 2: Players hand gains 1 card - FAILED  ----------------\n");
        testsFailed++;
   }

   printf("----------------- Test 3: Players hand gains 0 cards  ----------------\n");
   memcpy(&testG, &G, sizeof(struct gameState));
   player = whoseTurn(&testG);
   for (i = 0; i < testG.deckCount[player]; i++)
   {
        testG.deck[player][i] = duchy;
   }
   expected = 0;
   handCountBeforeTurn = testG.handCount[player];
   temp = cardEffect(adventurer, copper, copper, copper, &testG, handpos , 0);
   result = testG.handCount[player] - handCountBeforeTurn;
   if (expected !=  result)
   {
        printf("----------------- Test 3: Players hand gains 0 cards - FAILED  ----------------\n");
        testsFailed++;
   }

   if ( testsFailed == 0 )
        printf("\n >>>>> SUCCESS: Testing Adventurer complete <<<<<\n\n");
   else printf("\n >>>>> FAILURE: %d Adventurer  tests failed <<<<<\n\n", testsFailed);

   return 0;
}
