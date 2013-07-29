#include <iostream>

#include "tablestate.h"
#include "adaline_adapter.h"

using namespace Blackjack;

static const int SignalsForBlackjackPlayer = 20;

AdalineAdapter::AdalineAdapter()
   : adaptivePlayer(SignalsForBlackjackPlayer)
{
   gamesWon = 0;
   gamesPlayed = 0;
   lastGame = 0;
}

void AdalineAdapter::PlayGameWithAcesAsEleven()
{
   lastGame = new Game(true);
}

void AdalineAdapter::PlayGameWithAcesAsOne()
{
   lastGame = new Game(false);
}

void AdalineAdapter::PunishOrRewardPlayer()
{
}
