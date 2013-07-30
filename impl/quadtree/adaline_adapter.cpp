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
   // set the signals to the adaline
   // allow it to weigh the inputs
   // quantize the output
   // and either adjust the size of the quadtree
   // or stop if the adaline thinks all is well
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
   // foreach bit in the length field
      // if the bit is set
         // set that adaline signal
}
