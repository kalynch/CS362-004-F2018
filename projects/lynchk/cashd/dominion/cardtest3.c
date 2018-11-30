/* -----------------------------------------------------------------------
 * Author: Kaitlin Lynch Source: school cardTest4  example
 * Include the following lines in your makefile:
 *
 * cardtest3: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
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

   printf("----------------- Testing Outpost ----------------\n");
   printf("----------------- Test 1: Outpost flag set  ----------------\n");
   memcpy(&testG, &G, sizeof(struct gameState));
   player = whoseTurn(&testG);
   temp = cardEffect(outpost, copper, copper, copper, &testG, handpos , 0);
   if (!testG.outpostPlayed)
   {
        printf("----------------- Test 1: Outpost flag set - FAILED  ----------------\n");
        testsFailed++;
   }

   printf("----------------- Test 2: 1 card discarded  ----------------\n");
   memcpy(&testG, &G, sizeof(struct gameState));
   player = whoseTurn(&testG);
   expected = 1;
   int discardBeforeTurn = testG.playedCardCount;
   temp = cardEffect(outpost, copper, copper, copper, &testG, handpos , 0);
   result = testG.playedCardCount - discardBeforeTurn;
   if (expected != result)
   {
        printf("----------------- Test 2: 1 card discarded - FAILED  ----------------\n");
        testsFailed++;
   }

   if ( testsFailed == 0 )
        printf("\n >>>>> SUCCESS: Testing Outpost complete <<<<<\n\n");
   else printf("\n >>>>> FAILURE: %d Outpost tests failed <<<<<\n\n", testsFailed);

   return 0;
}
