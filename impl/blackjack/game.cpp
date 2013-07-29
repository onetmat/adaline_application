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
Game::Game(bool acesCountAsEleven) : currentTableState(acesCountAsEleven)
{
   dealerSum = 0;
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

   // Now deal wo cards to the player
   DealToPlayer();
   DealToPlayer();

   state = IN_PROGRESS;
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
         std::cout << "PLAYER BUSTS WITH SCORE OF: " << playerSum
            << std::endl;
      }
      // if not, check to see if they just won
      else if (playerSum == BlackJackSum)
      {
         std::cout << "PLAYER BLACKJACK" << std::endl;
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

      std::cout << "Player has: " << playerSum << ", Dealer has: "
         << dealerSum << std::endl;
      if (dealerSum > playerSum)
      {
         // player loses
         state = PLAYER_LOST;
         std::cout << "PLAYER LOSES";
      }
      // else if the player has a higher sum
      else if (playerSum > dealerSum)
      {
         state = PLAYER_WON;
         std::cout << "PLAYER WINS";
      }
      else
      {
         // game is a push and will be discarded
         state = PUSH;
         std::cout << "GAME IS A PUSH";
      }
      std::cout << std::endl;
   }
   else
   {
      std::cout << "Dealer busts with sum of: " << dealerSum << std::endl;
      state = PLAYER_WON;
   }
}
