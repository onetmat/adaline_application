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
      Game* lastGame;
      unsigned int gamesWon;
      unsigned int gamesPlayed; // but not tied

      CompIntel::Adaline adaptivePlayer;
   };
}

#endif
