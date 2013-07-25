#ifndef SHAPES_H_
#define SHAPES_H_

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
}
#endif
