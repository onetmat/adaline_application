#include <iostream>

#include "shapes.h"
#include "adaline.h"

using namespace Shapes;

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

   while (doAnotherIteration)
   {
      doAnotherIteration = false;
   }
}
