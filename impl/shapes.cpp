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

   // submit the shape to the adaline
   SubmitShape(shape, adaline);
   // W * I
   adaline.WeighInputs();
   // retrieve the output signal, stored in a temp
   // and calculate the error term (desired - actual output)
   errorSquared = desiredOutputSignal - adaline.GetOutputSignal();
   // adjust the weights
   adaline.Learn(desiredOutputSignal);
   // and returned the squared result of the error
   errorSquared *= errorSquared;

   return errorSquared;
}

// Teach an Adaline circuit to respond to the patterns in shapes.h
// as specified in "Adaptive Linear Circuits" by Widrow and Hoff.
void Shapes::TeachAllShapes()
{
   // the sum of error^2 from each training run
   double sumOfSquareErrors = 0.0;
   // the error term^2 from the last learning
   double squareError = 0.0;
   // as in, keep trying to train the adaline
   bool doAnotherIteration = true;
   // Track the number of iterations in counting numbers
   unsigned int iteration = 1;
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
      sumOfSquareErrors = 0.0;
      std::cout << "Iteration: " << iteration++ << std::endl;

      std::cout << "FOR THE F SHAPES: " << std::endl;
      squareError = PerformShapeLearningIteration(fShapeTwo,
                     shapeAdaline,
                     FDesiredOutput);
      sumOfSquareErrors += squareError;
      std::cout << "Output signal: " << shapeAdaline.GetOutputSignal()
         << std::endl;
      std::cout << "Square Error: " << squareError << std::endl;

      squareError = PerformShapeLearningIteration(fShapeOne,
                     shapeAdaline,
                     FDesiredOutput);
      sumOfSquareErrors += squareError;
      std::cout << "Output signal: " << shapeAdaline.GetOutputSignal()
         << std::endl;
      std::cout << "Square Error: " << squareError << std::endl;


      std::cout << std::endl << "FOR THE T SHAPES: " << std::endl;
      squareError = PerformShapeLearningIteration(tShapeOne,
                     shapeAdaline,
                     TDesiredOutput);
      sumOfSquareErrors += squareError;
      std::cout << "Output signal: " << shapeAdaline.GetOutputSignal()
         << std::endl;
      std::cout << "Square Error: " << squareError << std::endl;

      squareError = PerformShapeLearningIteration(tShapeTwo,
                     shapeAdaline,
                     TDesiredOutput);
      sumOfSquareErrors += squareError;
      std::cout << "Output signal: " << shapeAdaline.GetOutputSignal()
         << std::endl;
      std::cout << "Square Error: " << squareError << std::endl;

      std::cout << std::endl << "FOR THE G SHAPES: " << std::endl;

      squareError = PerformShapeLearningIteration(gShapeOne,
                     shapeAdaline,
                     GDesiredOutput);
      sumOfSquareErrors += squareError;
      std::cout << "Output signal: " << shapeAdaline.GetOutputSignal()
         << std::endl;
      std::cout << "Square Error: " << squareError << std::endl;

      squareError = PerformShapeLearningIteration(gShapeTwo,
                     shapeAdaline,
                     GDesiredOutput);
      sumOfSquareErrors += squareError;
      std::cout << "Output signal: " << shapeAdaline.GetOutputSignal()
         << std::endl;
      std::cout << "Square Error: " << squareError << std::endl;

      std::cout << "Sum of Square Errors: " << sumOfSquareErrors
         << std::endl;
      std::cout << "Continue (y/n)? : " << std::endl;
      std::cin >> ch;
      doAnotherIteration = ch == 'y';
   }
}
