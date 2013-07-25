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

   void TeachAllShapes();

   void SubmitShape(const char shape[ShapeSignalLength],
      CompIntel::Adaline& adaline);
}
#endif
