#ifndef BLACKJACK_GAME_H_
#define BLACKJACK_GAME_H_

#include <vector>

#include "../carddeck/deck.h" // need this full #include for vector

namespace Blackjack
{
   class TableState;

   // The game class acts like a turn based game of blackjack.
   // It manages the deck, tracks the table state (subject to the
   // rules outlined in that class), and manages the dealer
   // strategy.
   class Game
   {
   public:
      Game(bool acesCountAsEleven = true);

      // Current table state is managed entirely by this class.
      inline const TableState& GetCurrentTableState() const
         { return currentTableState; }

      inline const std::vector<TableState>& GetTableStateHistory() const
         { return tableStateHistory; }

      // Returns true if the game has been neither won nor lost.
      inline bool GameInProgress() const { return state == IN_PROGRESS; }

      // Indicates player won this game.
      inline bool PlayerWonGame() const { return state == PLAYER_WON; }

      // Indicates player lost this game.
      inline bool PlayerLostGame() const { return state == PLAYER_LOST; }

      // Two player actions affect the state of the game:
      // Plays out the current hand (one iteration) as if the notional
      // player said "Hit"/ asked for another card.
      void PlayerHits();

      // Player no longer wants any cards.
      void PlayerStands();

   private:

      // Plays basic strategy from Ed Thorp's "Beat the Dealer" as 
      // called out by Widow, et. al.
      void PlayDealer();

      // Draw a card from the deck, update the table state,
      // and update the dealer's card sum (unknown to the player before
      // the round is over).
      inline void DealToDealer(bool currentCardShowing = false)
      {
         const PlayingCards::Card& c = deck.DrawCard();
         if (currentCardShowing)
         {
            currentTableState.SetDealerCardShowing(c);
         }
         // All aces count as 11 to the dealer
         if (c.IsAce())
         {
            dealerSum += 11;
         }
         // Face cards are ten
         else if (c.IsFaceCard())
         {
            dealerSum += 10;
         }
         // Numerics are numerical
         else
         {
            dealerSum += c.GetNumericValue();
         }
      }

      // Draw a card from the deck and update the table state.
      inline void DealToPlayer()
      {
         const PlayingCards::Card& c = deck.DrawCard();
         currentTableState.DealCardToPlayer(c);
      }

      PlayingCards::Deck deck;

      TableState currentTableState;

      // Track cards given to dealer to play out
      // fixed strategy
      unsigned int dealerSum;

      // Each time the player makes a decision,
      // the table state is stored.
      std::vector<TableState> tableStateHistory;

      // Symbolic defines for what's going on with the game.
      // Once a game is constructed, it's considered in progress.
      enum GameState
      {
         IN_PROGRESS = 0,
         PLAYER_LOST,
         PLAYER_WON,
         PUSH  // Tie
      };

      GameState state;
   };
}

#endif
