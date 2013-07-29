#ifndef CARD_H_
#define CARD_H_

namespace PlayingCards
{
   enum Suit
   {
      HEARTS = 0,
      SPADES,
      DIAMONDS,
      CLUBS
   };

   // A "playing card", in the context of 21, has a suit
   // selected from the values above, and a denomination
   // selected from "A,2,3,4,5,6,7,8,9,10,J,Q,K"; represented
   // here as a letter.
   class Card
   {
   public:
      Card(Suit s, char denom) : suit(s), denomination(denom)
      {
      }

      ~Card() {};

      // Allow read acces to private variables.
      inline Suit GetSuit() const { return suit; }
      inline char GetDenomination() const { return denomination; }

      // A face card has denomination J, Q, or K
      inline bool IsFaceCard() const
      {
         bool isJack = denomination == 'J';
         bool isQueen = denomination == 'Q';
         bool isKing = denomination == 'K';

         return isJack || isQueen || isKing;
      }

      // An Ace has denomination 'A'
      inline bool IsAce() const
      {
         return denomination == 'A';
      }

      // A card is "numeric" if it is not an Ace or face card
      inline bool IsNumeric() const
      {
         bool isAceOrFaceCard = IsAce() || IsFaceCard();

         return !(isAceOrFaceCard);
      }

      // Return the numeric value (2..10) of this card's
      // denomination. Returns 0 if this card is not numeric
      inline int GetNumericValue() const
      {
         int value = 0;
         if (IsNumeric())
         {
            if (denomination == 'T')
            {
               value = 10;
            }
            else
            {
               value = denomination - '0';
            }
         }
         return value;
      }

   private:
      char denomination;
      Suit suit;
   };
}

#endif
