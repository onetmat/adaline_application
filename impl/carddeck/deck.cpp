#include <iostream>

#include <cstdlib> // for srand and rand

#include "deck.h"

using namespace PlayingCards;

static const int deckSize = 52;
static const int cardsPerSuit = 13;
static const int halfDeckSize = 26;

static char denoms[cardsPerSuit] =
   { 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};

Deck::Deck()
{
   deck.reserve(deckSize);
   // Four suits, one card each of A,2,3...Q,K per suit
   for (int i = 0; i < cardsPerSuit; ++i)
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
   // basic algorithm to shuffle a deck:
   // 1) split the deck in half
   // 2) then while either pile still has cards
   // 3) randomly pick a pile
   // 4) and put its top card into the new deck (on top)
   // 5) whichever pile is left, put each of its cards on top of new deck

   // 1) Split the deck in half
   // Need a temporary vector that exactly matches what we have
   std::vector<Card> tmpPile(deck);
   deck.clear();

   // also need two variables (one for each "sub-pile")
   int pileIndex1 = 0, pileIndex2 = 0; // both can range [0, 25]
      // pileIndex2's actual index is x+halfDeckSize

   // 2) then while either pile still has cards
   int randomPile = 0; // used to determine which pile
                       // will have it's next card taken

   while (pileIndex1 < halfDeckSize && pileIndex2 < halfDeckSize)
   {
      // 3) randomly pick a pile
      // 4) and put its top card into the new deck (on top)
      // get a random number from 0..10
      randomPile = rand() % 10;
      // if > 5, then pick pile 2
      if (randomPile >= 5)
      {
         deck.push_back(tmpPile[pileIndex2 + halfDeckSize]);
         pileIndex2 += 1;
      }
      else
      {
         // pick pile 1
         deck.push_back(tmpPile[pileIndex1]);
         pileIndex1 += 1;
      }
   }
   while (pileIndex1 < halfDeckSize)
   {
      deck.push_back(tmpPile[pileIndex1]);
      pileIndex1 += 1;
   }
   while (pileIndex2 < halfDeckSize)
   {
      deck.push_back(tmpPile[pileIndex2 + halfDeckSize]);
      pileIndex2 += 1;
   }

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
   int heartsSeen = 0;
   int clubsSeen = 0;
   int spadesSeen = 0;
   int diamondsSeen = 0;

   for (int i = 0; i < deck.size(); ++i)
   {
      std::cout << "Card index " << i + 1 << " has denomination: "
         << deck[i].GetDenomination() << std::endl;
      std::cout << "\tAnd has snap numeric value of: "
         << deck[i].GetNumericValue() << std::endl;

      if (deck[i].GetSuit() == HEARTS) { ++heartsSeen; }
      if (deck[i].GetSuit() == SPADES) { ++spadesSeen; }
      if (deck[i].GetSuit() == DIAMONDS) { ++diamondsSeen; }
      if (deck[i].GetSuit() == CLUBS) { ++clubsSeen; }
   }
   std::cout << "Deck has " << deck.size() << " cards" << std::endl;
   std::cout << "Saw " << heartsSeen << " hearts " << std::endl;
   std::cout << "Saw " << clubsSeen << " clubs " << std::endl;
   std::cout << "Saw " << spadesSeen << " spades " << std::endl;
   std::cout << "Saw " << diamondsSeen << " diamonds " << std::endl;
}
