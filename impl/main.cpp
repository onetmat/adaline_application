#include <iostream>

#include <cstdlib> // for srand

#include "adaline.h"
#include "shapes.h"

#include "carddeck/deck.h"
#include "blackjack/tablestate.h"
#include "blackjack/game.h"

void TeachAdalineT();
void TestDrawingCards();
void TestSettingAdalineInputsFromTableState();
void TestGameKernel();
void TestAdalineAdapter();

int main(int argc, char **argv)
{
   //Shapes::TeachAllShapes();
   //TestDrawingCards();
   //TestSettingAdalineInputsFromTableState();
   TestGameKernel();
   return 0;
}

void TestGameKernel()
{
   Blackjack::Game acesEleven;
   int gameTurns = 1;

   while (acesEleven.GameInProgress())
   {
      std::cout << "Turn: " << gameTurns++ << std::endl;

      // auto-stand on 18
      if (acesEleven.GetCurrentTableState().GetSumOfPlayerCards() < 18)
      {
         acesEleven.PlayerHits();
      }
      else
      {
         acesEleven.PlayerStands();
      }
   }

   if (acesEleven.PlayerWonGame())
   {
      std::cout << "Player won!" << std::endl;
   }
   else
   {
      std::cout << "Player did not win." << std::endl;
   }

   std::cout << "Table states in history: "
      << acesEleven.GetTableStateHistory().size() << std::endl;
   std::cout << "=========" << std::endl;
   srand(time(NULL));
   Blackjack::Game acesOne(false);
   gameTurns = 1;

   while (acesOne.GameInProgress())
   {
      std::cout << "Turn: " << gameTurns++ << std::endl;

      // auto-stand on 18
      if (acesOne.GetCurrentTableState().GetSumOfPlayerCards() < 18)
      {
         acesOne.PlayerHits();
      }
      else
      {
         acesOne.PlayerStands();
      }
   }
   if (acesOne.PlayerWonGame())
   {
      std::cout << "Player won!" << std::endl;
   }
   else
   {
      std::cout << "Player did not win." << std::endl;
   }
   std::cout << "Table states in history: "
      << acesOne.GetTableStateHistory().size() << std::endl;
}

void TestSettingAdalineInputsFromTableState()
{
   PlayingCards::Card dealerShowingOne(PlayingCards::HEARTS, 'A');
   PlayingCards::Card playerCardOneA(PlayingCards::SPADES, '8');
   PlayingCards::Card playerCardTwoA(PlayingCards::SPADES, 'K');

   Blackjack::TableState stateOne;
   CompIntel::Adaline player(20);

   stateOne.SetDealerCardShowing(dealerShowingOne);
   stateOne.DealCardToPlayer(playerCardOneA);
   stateOne.DealCardToPlayer(playerCardTwoA);

   stateOne.SetAdalineInputs(player);

   PlayingCards::Card dealerShowingTwo(PlayingCards::HEARTS, '7');
   PlayingCards::Card playerCardOneB(PlayingCards::SPADES, 'A');
   PlayingCards::Card playerCardTwoB(PlayingCards::SPADES, '2');

   Blackjack::TableState stateTwo(true);

   stateTwo.SetDealerCardShowing(dealerShowingTwo);
   stateTwo.DealCardToPlayer(playerCardOneB);
   stateTwo.DealCardToPlayer(playerCardTwoB);

   stateTwo.SetAdalineInputs(player);
}

void TestDrawingCards()
{
   PlayingCards::Deck d;

   d.PrintDeckInfo();
   d.Shuffle();
   d.Shuffle();
   d.Shuffle();
   d.PrintDeckInfo();

   std::cout << "Drawing cards" << std::endl;
   for( int i = 0; i < 5; ++i)
   {
      const PlayingCards::Card &c = d.DrawCard();
      std::cout << "Card has suit (numeral): " << c.GetSuit() << std::endl;

      if (c.IsNumeric())
      {
         std::cout << "Card is numeric with value: " << c.GetNumericValue()
            << std::endl;
      }
      else
      {
         std::cout << "Card is ";
         if (c.IsAce())
         {
            std::cout << "an Ace: " << c.GetDenomination();
         }
         else if (c.IsFaceCard())
         {
            std::cout << "a face card: " << c.GetDenomination();
         }
         else
         {
            std::cout << "a Problem.";
         }
         std::cout << std::endl;
      }
      
   }
}

void PrintWeightVector(const CompIntel::Adaline& adaline)
{
   const double* weightVector = adaline.GetWeightVector();

   for (unsigned int i = 0;
      i < adaline.GetNumberOfWeights();
      ++i)
   {
      std::cout << "Weight " << i << ": " << weightVector[i] << std::endl;
   }

   char ch;
   std::cout << "Press..." << std::endl;
   std::cin >> ch;
}

// This method demonstrates an Adaline learning to recognize a T
// shaped signal.
void TeachAdalineT()
{

   static char tShapeOne[17] =
      "XXX "
      " X  "
      " X  "
      "    "
   ;

   CompIntel::Adaline tAdaline(16);

   double desiredOutput = 60.0; // trying to set output of adaline to 60
      // when a T is "seen"

   for (int tmp = 0; tmp < 100; ++tmp)
   {
      // for inspection purposes, pring the weights
      // of the adaline.
      PrintWeightVector(tAdaline);
      // first attach all input signals
      for (int sig = 0; sig < 16; ++sig)
      {
         if (tShapeOne[sig] == 'X')
         {
            tAdaline.SetInputSignal(sig, 1);
         }
         else
         {
            tAdaline.SetInputSignal(sig, 0);
         }
      }
      tAdaline.WeighInputs();
      tAdaline.Learn(desiredOutput);
      std::cout << "Output signal: " << tAdaline.GetOutputSignal()
         << std::endl;
   }
}
