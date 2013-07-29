#include <iostream>
#include <cstdlib> // for srand

#include "tablestate.h"
#include "adaline_adapter.h"

#undef DEBUG_ADAPTER

using namespace Blackjack;

static const int SignalsForBlackjackPlayer = 20;

AdalineAdapter::AdalineAdapter()
   : adaptivePlayer(SignalsForBlackjackPlayer)
{
   gamesWon = 0;
   gamesPlayed = 0;
}

void AdalineAdapter::PlayGameWithAcesAsEleven()
{
   lastGame.Reset(true);
   RunGameKernel();
}

void AdalineAdapter::PlayGameWithAcesAsOne()
{
   lastGame.Reset(true);
   RunGameKernel();
}

void AdalineAdapter::RunGameKernel()
{
   // while the game is in progress
   while (lastGame.GameInProgress())
   {
      // feed the inputs to the adaline
      const TableState& table = lastGame.GetCurrentTableState();

      table.SetAdalineInputs(adaptivePlayer);

      // weigh the options an quantize the adaline's response
      adaptivePlayer.WeighInputs();

      // quantize the adaline's output
      int decision
         = QuantizeAdalineOutput(adaptivePlayer.GetOutputSignal());

      // if decision = 1 then hit
      // if decision = -1 then stand
      if (decision == 1)
      {
         lastGame.PlayerHits();
      }
      else if (decision == -1)
      {
         lastGame.PlayerStands();
      }
   } // while the game is in progress
}

void AdalineAdapter::PunishOrRewardPlayer()
{
   // punish if the player lost
   bool shouldPunish = lastGame.PlayerLostGame();

   // make sure neither dealer nor player got Blackjack
   bool canPunishOrReward = 
          (lastGame.GetTableStateHistory().size() > 0)
          && (shouldPunish || lastGame.PlayerWonGame());

   if (canPunishOrReward)
   {
      // Get the history
      const std::vector<TableState>& tableHistory =
         lastGame.GetTableStateHistory();

      std::vector<TableState>::const_iterator tableIter;

      // then foreach entry
      for (tableIter = tableHistory.begin();
         tableIter != tableHistory.end();
         ++tableIter)
      {
         // replay the situation to the adaline
         tableIter->SetAdalineInputs(adaptivePlayer);
         // re-weigh the weights
         adaptivePlayer.WeighInputs();
         // re-quantize this output
         int reQuantizedOutput =
            QuantizeAdalineOutput(adaptivePlayer.GetOutputSignal());

         // and if we're punishing, negate it
         if (shouldPunish)
         {
#ifdef DEBUG_ADAPTER
            std::cout << "Punishing... sending -1 * "
               << reQuantizedOutput << std::endl;
#endif
            reQuantizedOutput *= -1;
         }
#ifdef DEBUG_ADAPTER
         else
         {
            std::cout << "Rewarding..." << std::endl;
         }

#endif
         // then submit it to the Adaline as desired output
         adaptivePlayer.Learn(reQuantizedOutput);
#ifdef DEBUG_ADAPTER
         std::cout << "Next table state... " << std::endl;
#endif
      } // foreach table state
      // update games won vs games played
      if (!shouldPunish)
      {
         gamesWon += 1;
      }
      gamesPlayed += 1;
   } // no one got a "natural"
#ifdef DEBUG_ADAPTER
   else
   {
      std::cout << "Not considering last game because someone got 21."
         << std::endl;
   }
   std::cout << "END GAME" << std::endl;
#endif
}
