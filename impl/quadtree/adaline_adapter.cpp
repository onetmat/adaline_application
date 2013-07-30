#include <iostream>

#include "../adaline.h"
#include "adaline_adapter.h"

#define DEBUG_QUADTREE_ADAPTER

using namespace CompGeo;

static const int BitsPerByte = 8;

// The number of input lines to the adaline
// will be equal to the word size of the data type
// used to represent the length of the quadtree
AdalineAdapter::AdalineAdapter()
   : quadtreeJudge(sizeof(Quadtree::LengthType) * BitsPerByte)
{
#ifdef DEBUG_QUADTREE_ADAPTER
   std::cout << "Setting number of input signals to "
      << sizeof(Quadtree::LengthType) * BitsPerByte << std::endl;
#endif
   // to complete acq. and init. set th length of the quadtree to 0
   currentQuadtree.SetLengthOfRootNode(0);
}

void AdalineAdapter::Reset(Quadtree::LengthType initialRootNodeLength)
{
   // clear the history and
   lengthHistory.clear();
   // set the quadtree to the specified length.
   currentQuadtree.SetLengthOfRootNode(initialRootNodeLength);
}

void AdalineAdapter::PunishAdaline()
{
   if (lengthHistory.size() > 0)
   {
      TeachAdaline(true);
   }
}

void AdalineAdapter::RewardAdaline()
{
   if (lengthHistory.size() > 0)
   {
      TeachAdaline(false);
   }
}

void AdalineAdapter::AdjustQuadtree()
{
   // 1 => extend the quadtree border by 1
   // -1 => stop
   int quantizedOutput = 1;
   int iters = 0;

   while (quantizedOutput == 1 && iters < 1000)
   {
      // set the signals to the adaline
      SetAdalineInputs();
      // allow it to weigh the inputs
      quadtreeJudge.WeighInputs();
#ifdef DEBUG_QUADTREE_ADAPTER
      std::cout << "Output signal from adaline: "
         << quadtreeJudge.GetOutputSignal() << std::endl;

#endif
      // quantize the output
      int quantizedOutput
         = QuantizeAdalineOutput(quadtreeJudge.GetOutputSignal());

      // save the current length in the history
      Quadtree::LengthType currentLength =
         currentQuadtree.GetLengthOfRootNode();

      lengthHistory.push_back(currentLength);
      // and either adjust the size of the quadtree
      if (quantizedOutput == 1)
      {
         currentQuadtree.SetLengthOfRootNode(currentLength + 1);
#ifdef DEBUG_QUADTREE_ADAPTER
         std::cout << "Set new length to " << currentLength + 1
            << std::endl;
#endif
      }
      // or stop if the adaline thinks all is well

      // update the number of iterations just in case.
      ++iters;
   }
#ifdef DEBUG_QUADTREE_ADAPTER
   std::cout << "Quit after " << iters << " iterations." << std::endl;
#endif
}

void AdalineAdapter::TeachAdaline(bool punishing)
{
   // for each length in the history
      // set the signals to the adaline
      // allow it to weigh the inputs
      // quantize the output
      // and if we're punishing
         // invert the quantized output
      // feed the quantized output as the desired output
}

void AdalineAdapter::SetAdalineInputs()
{
   // clear all signals to the adaline
   quadtreeJudge.ClearInputSignals();

   // store the quadtree length for easy access
   Quadtree::LengthType rootNodeLen
      = currentQuadtree.GetLengthOfRootNode();
   // foreach bit in the length field
   for (int i = 0; i < quadtreeJudge.GetNumberOfInputs(); ++i)
   {
      // if the bit is set
      if (rootNodeLen >> i & 0x1)
      {
         // set that adaline signal
         quadtreeJudge.SetInputSignal(i, 1);
#ifdef DEBUG_QUADTREE_ADAPTER
         std::cout << "Setting signal " << i << std::endl;
#endif
      }
   }
}
