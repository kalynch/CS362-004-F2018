/* -----------------------------------------------------------------------
 * Author: Kaitlin Lynch Source: school testUpdateCoins example
 * Include the following lines in your makefile:
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
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
    int seed = 1000;
    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;
    
    // initialize a game state and player cards
    initializeGame(numPlayer, k, seed, &G);

   printf("----------------- Testing Whose Turn ----------------\n");
   printf("----------------- Test 1: return value = game state turn  ----------------\n");
   memcpy(&testG, &G, sizeof(struct gameState));
   expected = testG.whoseTurn;
   result = whoseTurn(&testG);
   assert(expected == result);

   printf("\n >>>>> SUCCESS: Testing Whose Turn complete <<<<<\n\n");

   return 0;
}
   
