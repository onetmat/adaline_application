#include <iostream>

#include "tablestate.h"
#include "../adaline.h"
#include "../carddeck/deck.h"

#undef DEBUG_TABLESTATE

using namespace Blackjack;

static const int BlackjackSignalCount = 20;
static const int IndexForPlayerSignals = 10;
static const int AceCountingSignalIndex = 18;

TableState::TableState(bool acesAreEleven)
{
   aceCountsAsEleven = acesAreEleven;
   dealerCardShowing = '0'; // intentionally invalid
   sumOfPlayerCards = 0;
}

TableState::TableState(const TableState& rhs)
{
   aceCountsAsEleven = rhs.aceCountsAsEleven;
   dealerCardShowing = rhs.dealerCardShowing;
   sumOfPlayerCards = rhs.sumOfPlayerCards;
}

void TableState::SetDealerCardShowing(const PlayingCards::Card& c)
{
   // if the dealer is receiving a face card
   if (c.IsFaceCard())
   {
      // treat it like a ten
      dealerCardShowing = 'T';
   }
   // otherwise just sore the character rep of the denomination
   else
   {
      dealerCardShowing = c.GetDenomination();
   }
}

void TableState::DealCardToPlayer(const PlayingCards::Card& c)
{
   // if the card is straight numeric, add that value to the current total
   if (c.IsNumeric())
   {
      sumOfPlayerCards += c.GetNumericValue();
   }
   else if (c.IsAce())
   {
   // else if the card is an ace
      // and aces count as eleven
      if (aceCountsAsEleven)
      {
         // add 11 to total
         sumOfPlayerCards += 11;
      }
      else
      {
         // else add 1 to total
         sumOfPlayerCards += 1;
      }
   }
   else if (c.IsFaceCard())
   {
      // else if card is a face card, add ten to the total
      sumOfPlayerCards += 10;
   }
   // else don't do anything
}

void TableState::SetAdalineInputs(CompIntel::Adaline& tgt)
{
   // for this to work, the adaline must be setup for at least 20
   // signals
   if (tgt.GetNumberOfInputs() >= BlackjackSignalCount)
   {
      // The signals need to be cleared each round (linearly independent)
      tgt.ClearInputSignals();

      // determine which signals need to be set based on the dealer card
      int adalineInputsForDealer = DealerToAdalineInputs();

      // set dealer signals (first 9)

#ifdef DEBUG_TABLESTATE
      // debugging
      std::cout << "Because dealer showing: " << dealerCardShowing
         << std::endl;
      std::cout << "About to set the first " << adalineInputsForDealer
         << " signals to Adaline." << std::endl;
#endif
      for (int i = 0; i < adalineInputsForDealer; ++i)
      {
         tgt.SetInputSignal(i, 1);
      }

      // next, determine signals for player card sum
      int playerCardSumSignals = PlayerCountToAdalineInputs();

#ifdef DEBUG_TABLESTATE
      std::cout << "Because player sum is: " << sumOfPlayerCards
         << std::endl;
      std::cout << "About to set the next " << playerCardSumSignals
         << " signals to Adaline." << std::endl;
#endif
      for (int i = IndexForPlayerSignals;
            i < IndexForPlayerSignals + playerCardSumSignals; ++i)
      {
         tgt.SetInputSignal(i, 1);
      }

      // finally,set the ace counted signal
      if (aceCountsAsEleven)
      {
         tgt.SetInputSignal(AceCountingSignalIndex, 1);
      }
   } // end if adaline has enough input lines
} // end set adaline inputs
