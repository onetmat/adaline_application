#include <iostream>

#include "shapes.h"
#include "adaline.h"

using namespace Shapes;

// Utility function to submit a shape signal from
// shapes.h into an appropriately sized notional adaline.
void SubmitShape(const char shape[ShapeSignalLength],
   CompIntel::Adaline& adaline)
{
   // first, verify that the adaline is setup to
   // accept the proper number of signals
      // if so, then iterate over the entire signal array
         // and if the character at this index is an X,
         // set the adaline signal to one
         // else, set it to zero
}

// Teach an Adaline circuit to respond to the patterns in shapes.h
// as specified in "Adaptive Linear Circuits" by Widrow and Hoff.
// T => +60
// G => 0
// F => -60
void TeachAllShapes()
{
   // the sum of error^2 from each training run
   double sumOfSquarErrors = 0.0;
   // as in, keep trying to train the adaline
   bool doAnotherIteration = true;
   // the adaline that will be taught to recognize the signals in shapes.h
   CompIntel::Adaline shapeAdaline(ShapeSignalLength);

   // First cut:
   // iterate over all patterns, setting all signals
   // and giving the adaline a go.
   // get the error for each, square it and sum it
   // (square the error from each run first and then add it to the total)
   while (doAnotherIteration)
   {
      doAnotherIteration = false;
   }
}
