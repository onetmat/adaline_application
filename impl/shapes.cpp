#include <iostream>

#include "shapes.h"
#include "adaline.h"

using namespace Shapes;

// Utility function to submit a shape signal from
// shapes.h into an appropriately sized notional adaline.
void Shapes::SubmitShape(const char shape[ShapeSignalLength],
      CompIntel::Adaline& adaline)
{
   // first, verify that the adaline is setup to
   // accept the proper number of signals
   if (adaline.GetNumberOfWeights() >= ShapeSignalLength)
   {
      // if so, then iterate over the entire signal array
      for (int i = 0; i < ShapeSignalLength; ++i)
      {
         // and if the character at this index is an X,
         if (shape[i] == 'X')
         {
            // set the adaline signal to one
            adaline.SetInputSignal(i, 1);
         }
         else
         {
            // else, set it to zero
            adaline.SetInputSignal(i, 0);
         }
      }
   }
}

double Shapes::PerformShapeLearningIteration(
   const char shape[ShapeSignalLength],
   CompIntel::Adaline& adaline,
   double desiredOutputSignal)
{
   double errorSquared = 0.0;

   return errorSquared;
}

// Teach an Adaline circuit to respond to the patterns in shapes.h
// as specified in "Adaptive Linear Circuits" by Widrow and Hoff.
// T => +60
// G => 0
// F => -60
void Shapes::TeachAllShapes()
{
   // the sum of error^2 from each training run
   double sumOfSquarErrors = 0.0;
   // as in, keep trying to train the adaline
   bool doAnotherIteration = true;
   // the adaline that will be taught to recognize the signals in shapes.h
   CompIntel::Adaline shapeAdaline(ShapeSignalLength);

   // character input from user indicating "continue"
   char ch = 'n';

   // First cut:
   // iterate over all patterns, setting all signals
   // and giving the adaline a go.
   // get the error for each, square it and sum it
   // (square the error from each run first and then add it to the total)
   while (doAnotherIteration)
   {
      SubmitShape(fShapeTwo, shapeAdaline);
      shapeAdaline.WeighInputs();
      shapeAdaline.Learn(-60.0);
      std::cout << "Output signal: " << shapeAdaline.GetOutputSignal()
         << std::endl;
      std::cout << "Continue (y/n)? : " << std::endl;
      std::cin >> ch;
      doAnotherIteration = ch == 'y';
   }
}
