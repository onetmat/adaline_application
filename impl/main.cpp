#include <iostream>

#include "adaline.h"
#include "shapes.h"

void TeachAdalineT();

int main(int argc, char **argv)
{
   Shapes::TeachAllShapes();
   return 0;
}

void PrintWeightVector(const CompIntel::Adaline& adaline)
{
   const double* weightVector = adaline.GetWeightVector();

   for (unsigned int i = 0;
      i < adaline.GetNumberOfWeights();
      ++i)
   {
      std::cout << "Weight " << i << ": " << weightVector[i] << std::endl;
   }

   char ch;
   std::cout << "Press..." << std::endl;
   std::cin >> ch;
}

// This method demonstrates an Adaline learning to recognize a T
// shaped signal.
void TeachAdalineT()
{

   static char tShapeOne[17] =
      "XXX "
      " X  "
      " X  "
      "    "
   ;

   CompIntel::Adaline tAdaline(16);

   double desiredOutput = 60.0; // trying to set output of adaline to 60
      // when a T is "seen"

   for (int tmp = 0; tmp < 100; ++tmp)
   {
      // for inspection purposes, pring the weights
      // of the adaline.
      PrintWeightVector(tAdaline);
      // first attach all input signals
      for (int sig = 0; sig < 16; ++sig)
      {
         if (tShapeOne[sig] == 'X')
         {
            tAdaline.SetInputSignal(sig, 1);
         }
         else
         {
            tAdaline.SetInputSignal(sig, 0);
         }
      }
      tAdaline.WeighInputs();
      tAdaline.Learn(desiredOutput);
      std::cout << "Output signal: " << tAdaline.GetOutputSignal()
         << std::endl;
   }
}
