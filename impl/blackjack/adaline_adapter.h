#ifndef ADALINE_ADAPTER_H_
#define ADALINE_ADAPTER_H_

#include "../adaline.h"
#include "game.h"

namespace Blackjack
{
   // An adaline adapter tracks total games that didn't end in a push,
   // total games won, and an adaline.
   class AdalineAdapter
   {
   public:
      AdalineAdapter();
      ~AdalineAdapter() { delete lastGame; }

      // Play a game of blackjack
      void PlayGameWithAcesAsEleven();
      void PlayGameWithAcesAsOne();

      // Get details of the last game
      inline const Game* GetLastGame() const { return lastGame; }

      // Get the adaline
      inline const CompIntel::Adaline& GetAdaline() const
         { return adaptivePlayer; }

      // Punish or reward the adaline circuit.
      void PunishOrRewardPlayer();

      inline double GetPercentGamesWon() const
      {
         double pctWon = 0.0;
         if (gamesPlayed > 0)
         {
            pctWon = (double)gamesWon / (double)gamesPlayed;
         }

         return pctWon;
      }

   private:

      // Feed the tablestate to the adaline, have it
      // weigh the inputs, quantize the output,
      // and feed that decision back into the game.
      // Repeate until win or loss
      void RunGameKernel();

      // Quantize the Adaline output using the function from
      // "Punish/Reward..."
      inline int QuantizeAdalineOutput(double outputSignal)
      {
         int quantizedSignal = -1;
         if (outputSignal >= 0.0)
         {
            quantizedSignal = 1;
         }
         return quantizedSignal;
      }

      Game* lastGame;
      unsigned int gamesWon;
      unsigned int gamesPlayed; // but not tied

      CompIntel::Adaline adaptivePlayer;
   };
}

#endif
