/* -----------------------------------------------------------------------
 * Author: Kaitlin Lynch Source: school cardTest4  example
 * Include the following lines in your makefile:
 *
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
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
    int numPlayers = 2;
    int player, temp, handCountBeforeTurn;
    int handpos = 0;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

   printf("----------------- Testing Sea Hag ----------------\n");
   printf("----------------- Test 1: Players hand gains 1 card  ----------------\n");
   memcpy(&testG, &G, sizeof(struct gameState));
   player = whoseTurn(&testG);
   expected = 1;
   handCountBeforeTurn = testG.handCount[player];
   temp = cardEffect(sea_hag, copper, copper, copper, &testG, handpos , 0);
   result = testG.handCount[player] - handCountBeforeTurn;
   if (expected !=  result)
   {
        printf("----------------- Test 1: Players hand gains 1 card - FAILED  ----------------\n");
        testsFailed++;
   }

   printf("----------------- Test 2: Top deck card is curse  ----------------\n");
   memcpy(&testG, &G, sizeof(struct gameState));
   player = whoseTurn(&testG);
   temp = cardEffect(sea_hag, copper, copper, copper, &testG, handpos , 0);
   for (i = 0; i < numPlayers; i++)
   {
	// Only two players
	if (i != player)
	{
		result = testG.deck[i][testG.deckCount[i]--];
	}
   }
   
   if (result !=  curse)
   {
        printf("----------------- Test 2: Top deck card is curse - FAILED  ----------------\n");
        testsFailed++;
   }

   printf("----------------- Test 3: Players deck loses card (goes to hand)  ----------------\n");
   memcpy(&testG, &G, sizeof(struct gameState));
   player = whoseTurn(&testG);
   expected = 1;
   for (i = 0; i < numPlayers; i++)
   {
        // Only two players
        if (i != player)
        {
                expected = testG.deckCount[i] - 1;
        }
   }
   temp = cardEffect(sea_hag, copper, copper, copper, &testG, handpos , 0);
   for (i = 0; i < numPlayers; i++)
   {
        // Only two players
        if (i != player)
        {
                result = testG.deckCount[i];
        }
   }
   if (expected !=  result)
   {
        printf("----------------- Test 3: Players deck loses card (goes to hand) - FAILED  ----------------\n");
        testsFailed++;
   }

   if ( testsFailed == 0 )
        printf("\n >>>>> SUCCESS: Testing Sea Hag complete <<<<<\n\n");
   else printf("\n >>>>> FAILURE: %d Sea Hag tests failed <<<<<\n\n", testsFailed);

   return 0;
}
