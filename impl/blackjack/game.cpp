#include <iostream>

#include "tablestate.h"
#include "../adaline.h"
#include "game.h"

using namespace Blackjack;

 // Number of times a new game with shuffle the card deck before setting up
static const int ShuffleCount = 5;
static const int BlackJackSum = 21;
static const int DealerStandMin = 17; // Minimum sum on which dealer can stand.

// RAII... in this case, you end up with an in-progress blackjack game!
Game::Game(bool acesCountAsEleven)
{
   Reset(acesCountAsEleven);
}

void Game::Reset(bool acesCountAsEleven)
{
   currentTableState = TableState(acesCountAsEleven);

   dealerSum = 0;
   tableStateHistory.clear();
   // According to Thorp page 9, to setup for a blackjack game
   // 1) Shuffle
   // 2) Player cuts
   // 3) Burn a card
   // 4) Dealer gets two (first one showing)
   // 5) Player gets two
   // This sim doesn't do a cut and doesn't allow for multiple players
   // No evidence that this violates Widrow, et. al's "Punish/Reward"

   // Shuffle
   for (int i = 0; i < ShuffleCount; ++i)
   {
      deck.Shuffle();
   }

   // Burn a card (face down)
   const PlayingCards::Card& c = deck.DrawCard();

   // Deal two cards to the dealer, first one showing
   DealToDealer(true);
   DealToDealer();

   // Now deal two cards to the player
   DealToPlayer();
   DealToPlayer();

#ifdef DEBUG_GAME
   std::cout << "END INITIAL DEALS" << std::endl;

#endif

   // Did player Blackjack?
   if (currentTableState.GetSumOfPlayerCards() == BlackJackSum)
   {
      // Did the dealer?
      if (dealerSum != BlackJackSum)
      {
         state = PLAYER_WON;
      }
      else
      {
         state = PUSH;
      }
   }
   else
   {
      state = IN_PROGRESS;
   }
}

void Game::PlayerHits()
{
   // if the game is in progress
   if (GameInProgress())
   {
      // Save off old tablestate
      tableStateHistory.push_back(currentTableState);

      // Give the player a card
      DealToPlayer();

      // Check to see if they have busted
      int playerSum = currentTableState.GetSumOfPlayerCards();
      if (playerSum > BlackJackSum)
      {
         // player just lost
         state = PLAYER_LOST;
#ifdef DEBUG_GAME
         std::cout << "PLAYER BUSTS WITH SCORE OF: " << playerSum
            << std::endl;
#endif
      }
      // if not, check to see if they just won
      else if (playerSum == BlackJackSum)
      {
#ifdef DEBUG_GAME
         std::cout << "PLAYER AT 21" << std::endl;
#endif
         state = PLAYER_WON;
      }

      // else, keep the game in progress and carry on.
   } // if game in progress 
}

void Game::PlayerStands()
{
   // if the game is still in progress
   if (GameInProgress())
   {
      // save the state of the game, this was the last
      // state on which the player will get to decide
      tableStateHistory.push_back(currentTableState);

      // Play the dealer strategy
      PlayDealer();
      // The game will end here.
   } // end if game in progress
}

void Game::PlayDealer()
{
   // The basic strategy from p 11 of "Beat the Dealer"
   // basically implies 16 or less is a dealer hit.
   while (dealerSum < DealerStandMin)
   {
      DealToDealer();
   }

   // if the dealer didn't bust
   if (dealerSum <= BlackJackSum)
   {
      // and has higher sum than player
      int playerSum = currentTableState.GetSumOfPlayerCards();
#ifdef DEBUG_GAME
      std::cout << "Player has: " << playerSum << ", Dealer has: "
         << dealerSum << std::endl;
#endif
      if (dealerSum > playerSum)
      {
         // player loses
         state = PLAYER_LOST;
#ifdef DEBUG_GAME
         std::cout << "PLAYER LOSES";
#endif
      }
      // else if the player has a higher sum
      else if (playerSum > dealerSum)
      {
         state = PLAYER_WON;
#ifdef DEBUG_GAME
         std::cout << "PLAYER WINS";
#endif
      }
      else
      {
         // game is a push and will be discarded
         state = PUSH;
#ifdef DEBUG_GAME
         std::cout << "GAME IS A PUSH";
#endif
      }
#ifdef DEBUG_GAME
      std::cout << std::endl;
#endif
   }
   else
   {
#ifdef DEBUG_GAME
      std::cout << "Dealer busts with sum of: " << dealerSum << std::endl;
#endif
      state = PLAYER_WON;
   }
}
