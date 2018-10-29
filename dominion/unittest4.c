/* -----------------------------------------------------------------------
 * Author: Kaitlin Lynch Source: school testUpdateCoins example
 * Include the following lines in your makefile:
 *
 * unittest4: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
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

   printf("----------------- Testing Buy Card ( ----------------\n");
   printf("----------------- Test 1: no more buys allowed  ----------------\n");
   memcpy(&testG, &G, sizeof(struct gameState));
   expected = -1;
   testG.numBuys = 0;
   result = buyCard(province, &testG);
   assert(expected == result);

   printf("----------------- Test 2: no more of that card  ----------------\n");
   memcpy(&testG, &G, sizeof(struct gameState));
   expected = -1;
   testG.supplyCount[province] = 0;
   result = buyCard(province, &testG);
   assert(expected == result);

   printf("----------------- Test 3: not enough money  ----------------\n");
   memcpy(&testG, &G, sizeof(struct gameState));
   expected = -1;
   testG.coins = 7;
   result = buyCard(province, &testG);
   assert(expected == result);

   printf("----------------- Test 4: buy card successful  ----------------\n");
   memcpy(&testG, &G, sizeof(struct gameState));
   expected = 0;
   testG.coins = 8;
   testG.supplyCount[province] = 1;
   testG.numBuys = 1;
   result = buyCard(province, &testG);
   assert(expected == result);

   printf("\n >>>>> SUCCESS: Testing Whose Turn complete <<<<<\n\n");

   return 0;
}
