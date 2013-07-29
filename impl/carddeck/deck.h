#ifndef DECK_H_
#define DECK_H_

#include "card.h"
#include <vector>

namespace PlayingCards
{
   // A deck tracks a fixed array of Card objects,
   // allows shuffling, and tracks the "next" card to be drawn
   class Deck
   {
   public:
      // Initializes the deck (constructs 52 card objects and
      // places them in the vector)
      Deck();
      ~Deck() {}

      // Re-orders the fixed away in a somewhat random way.
      void Shuffle();

      // Return a reference to the next card on the "top"
      // of the deck. Deck top is circular for simplicity.
      const Card& DrawCard();

      // Used to test deck shuffling and provide general sanity.
      void PrintDeckInfo();
   private:
      // Store the 52 cards in the deck.
      std::vector<Card> deck;

      // Track the "top" card in the deck.
      // Always [0,51]
      int deckTop;
   };
}

#endif
