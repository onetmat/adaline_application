#ifndef GAMESTATE_H_
#define GAMESTATE_H_

namespace CompIntel
{
   class Adaline;
}

namespace PlayingCards
{
   class Card;
}

namespace Blackjack
{
   // TableState tracks the three input variables
   // from Widrow, et. al, "Punish/Reward..."
   class TableState
   {
   public:
      TableState(bool acesAreEleven = false);
      ~TableState() {};

      TableState(const TableState& rhs);

      // Set the current dealer card showing
      void SetDealerCardShowing(const PlayingCards::Card& c);
      // Deal the player a card.
      void DealCardToPlayer(const PlayingCards::Card& c);

      // Method enocdes the current state into the referenced
      // adaline object per "Punish/Reward..."
      // Does check for valid number of signals, etc.
      void SetAdalineInputs(CompIntel::Adaline& tgt) const;

      // Retrieve the current sum of cards delt to the player
      // if the player has > 21, then the round is over
      inline int GetSumOfPlayerCards() const { return sumOfPlayerCards; }
   private:

      // Convert the character representation of the showing dealer card
      // to a number that allows an iterative set of an Adaline.
      inline int DealerToAdalineInputs() const
      {
         // from the source paper w/r/t dealer cards
         // A, 2, 3, 4, 5, 6, 7, 8, 9, 10
         // sets
         // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
         // first signals
         int numberOfSignals = 0;
         if (dealerCardShowing == 'T')
         {
            numberOfSignals = 9;
         }
         else if (dealerCardShowing != 'A') // dealer is showing a numeric
         {
            numberOfSignals = dealerCardShowing - '1';
         }
         return numberOfSignals;
      }

      // Convert the current sum of all cards delt the player
      // into a number of signals to set into the adaptive player.
      int PlayerCountToAdalineInputs() const
      {
         // From the source material
         // <12, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21
         // sets
         // 0,    1,  2,  3,  4,  5,  6,  7,  8,  9, 10
         // Signals
         int numberOfSignals = 0;

         if (sumOfPlayerCards > 11)
         {
            numberOfSignals = sumOfPlayerCards - 11;
         }
         return numberOfSignals;
      }

      bool aceCountsAsEleven; // T => Ace has numeric value 11
                               // F => Ace has numeric value 1
                               // default is F
      char dealerCardShowing;  // Denomination from dealer card
      int sumOfPlayerCards;    // The sum of the cards delt the player
   };
}

#endif
