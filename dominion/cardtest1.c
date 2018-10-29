/* -----------------------------------------------------------------------
 * Author: Kaitlin Lynch Source: school cardTest4  example
 * Include the following lines in your makefile:
 *
 * cardtest1: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
    int expected, result;
    int testsFailed = 0;
    int seed = 1000;
    int numPlayer = 2;
    int player, temp;
    int handpos = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;

    // initialize a game state and player cards
    initializeGame(numPlayer, k, seed, &G);

   printf("----------------- Testing Smithy ----------------\n");
   printf("----------------- Test 1: Players hand gains 3 cards  ----------------\n");
   memcpy(&testG, &G, sizeof(struct gameState));
   player = whoseTurn(&testG);
   expected = 3;
   int handCountBeforeTurn = testG.handCount[player];
   temp = cardEffect(smithy, copper, copper, copper, &testG, handpos , 0);
   result = testG.handCount[player] - handCountBeforeTurn;
   if (expected != result)
   {
	printf("----------------- Test 1: Players hand gains 3 cards - FAILED  ----------------\n");
	testsFailed++;
   }

   printf("----------------- Test 2: 1 card discarded  ----------------\n");
   memcpy(&testG, &G, sizeof(struct gameState));
   player = whoseTurn(&testG);
   expected = 1;
   int discardBeforeTurn = testG.playedCardCount;
   temp = cardEffect(smithy, copper, copper, copper, &testG, handpos , 0);
   result = testG.playedCardCount - discardBeforeTurn;
   if (expected != result)
   {
        printf("----------------- Test 2: 1 card discarded - FAILED  ----------------\n");
        testsFailed++;
   }

   if ( testsFailed == 0 )
   	printf("\n >>>>> SUCCESS: Testing Smithy complete <<<<<\n\n");
   else printf("\n >>>>> FAILURE: %d Smithy tests failed <<<<<\n\n", testsFailed);

   return 0;
}
