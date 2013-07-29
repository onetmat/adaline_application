#include <iostream>

#include "deck.h"

using namespace PlayingCards;

static char denoms[13] =
   { 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};

Deck::Deck()
{
   // Four suits, one card each of A,2,3...Q,K per suit
   for (int i = 0; i < 13; ++i)
   {
      deck.push_back(Card(HEARTS, denoms[i]));
      deck.push_back(Card(SPADES, denoms[i]));
      deck.push_back(Card(DIAMONDS, denoms[i]));
      deck.push_back(Card(CLUBS, denoms[i]));
   }

   deckTop = 0;
}

void Deck::Shuffle()
{
}

const Card& Deck::DrawCard()
{
   if (deckTop == 51)
   {
      deckTop = 0;
   }

   return deck[deckTop++];
}


// Sanity checking.
void Deck::PrintDeckInfo()
{
   char ch; // used to wait for user

   for (int i = 0; i < deck.size(); ++i)
   {
      std::cout << "Card index " << i + 1 << " has denomination: "
         << deck[i].GetDenomination() << std::endl;
      std::cout << "\tAnd has snap numeric value of: "
         << deck[i].GetNumericValue() << std::endl;
   }
   std::cout << "Deck has " << deck.size() << " cards" << std::endl;
}
