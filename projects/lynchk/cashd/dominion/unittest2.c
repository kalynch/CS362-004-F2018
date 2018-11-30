/* -----------------------------------------------------------------------
 * Author: Kaitlin Lynch Source: school testUpdateCoins example
 * Include the following lines in your makefile:
 *
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
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

   printf("----------------- Testing Supply Count ----------------\n");
   printf("----------------- Test 1: return value = game state supply of province  ----------------\n");
   memcpy(&testG, &G, sizeof(struct gameState));
   expected = testG.supplyCount[province];
   result = supplyCount(province, &testG);
   assert(expected == result);

      printf("----------------- Test 2: return value province ! = game state supply of ducky  ----------------\n");
   memcpy(&testG, &G, sizeof(struct gameState));
   expected = testG.supplyCount[province];
   result = supplyCount(gold, &testG);
   assert(expected != result);


   printf("\n >>>>> SUCCESS: Testing Whose Turn complete <<<<<\n\n");

   return 0;
}
