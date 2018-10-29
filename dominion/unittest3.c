/* -----------------------------------------------------------------------
 * Author: Kaitlin Lynch Source: school testUpdateCoins example
 * Include the following lines in your makefile:
 *
 * unittest3: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
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
   printf("----------------- Test 1: No more province cards = game over  ----------------\n");
   memcpy(&testG, &G, sizeof(struct gameState));
   expected = 1;
   testG.supplyCount[province] = 0;
   result = isGameOver(&testG);
   assert(expected == result);

   printf("----------------- Test 2: Any province cards = game not over  ----------------\n");
   memcpy(&testG, &G, sizeof(struct gameState));
   expected = 0;
   result = isGameOver(&testG);
   assert(expected == result);

   printf("----------------- Test 3: Out of two cards = game not over  ----------------\n");
   memcpy(&testG, &G, sizeof(struct gameState));
   expected = 0;
   testG.supplyCount[adventurer] = 0;
   testG.supplyCount[council_room] = 0;
   result = isGameOver(&testG);
   assert(expected == result);

   printf("----------------- Test 4: Out of three  cards = game over  ----------------\n");
   memcpy(&testG, &G, sizeof(struct gameState));
   expected = 1;
   testG.supplyCount[adventurer] = 0;
   testG.supplyCount[council_room] = 0;
   testG.supplyCount[feast] = 0;
   result = isGameOver(&testG);
   assert(expected == result);

   printf("----------------- Test 5: Out of four cards = game over  ----------------\n");
   memcpy(&testG, &G, sizeof(struct gameState));
   expected = 1;
   testG.supplyCount[adventurer] = 0;
   testG.supplyCount[council_room] = 0;
   testG.supplyCount[feast] = 0;
   testG.supplyCount[gardens] = 0;
   result = isGameOver(&testG);
   assert(expected == result);

   printf("\n >>>>> SUCCESS: Testing Whose Turn complete <<<<<\n\n");

   return 0;
}
