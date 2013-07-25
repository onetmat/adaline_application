#ifndef SHAPES_H_
#define SHAPES_H_

namespace CompIntel
{
   class Adaline;
}

namespace Shapes
{
   const static int ShapeSignalLength = 17;
   static char tShapeOne[ShapeSignalLength] =
      "XXX "
      " X  "
      " X  "
      "    "
   ;

   static char tShapeTwo[ShapeSignalLength] =
      "    "
      " XXX"
      "  X "
      "  X "
   ;

   static char gShapeOne[ShapeSignalLength] =
      "XXX "
      "X   "
      "XXX "
      "XXX "
   ;

   static char gShapeTwo[ShapeSignalLength] =
      " XXX"
      " X  "
      " XXX"
      " XXX"
   ;

   static char fShapeOne[ShapeSignalLength] =
      "XXX "
      "XX  "
      "X   "
      "X   "
   ;

   static char fShapeTwo[ShapeSignalLength] =
      " XXX"
      " XX "
      " X  "
      " X  "
   ;

   // Attempt to a notional ADALINE to respond to all of the above shapes
   // using the following as desired output:
   // T => 60
   // G => 0
   // F => -60
   void TeachAllShapes();

   // Utility method to simplify setting the ADALINE signals from
   // the pre-defined shapes above.
   void SubmitShape(const char shape[ShapeSignalLength],
      CompIntel::Adaline& adaline);

   // Utility method that will set the ADALINE signals from the specified
   // pattern, will churn the Adaline, and then calculate and return
   // the square error from that run.
   double PerformShapeLearningIteration(const char shape[ShapeSignalLength],
      CompIntel::Adaline& adaline,
      double desiredOutputSignal);
}

#endif
