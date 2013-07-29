#include <cstdlib> // for srand and rand
#include <ctime>

#include "adaline.h"

using namespace CompIntel;

Adaline::Adaline(unsigned int numSignals)
{
   // the number of signals and weights must be equal
   // and the total number will be +1 whatever is passed to this method
   // to include a "bias" value of +1
   numberOfInputs = numSignals+1;
   inputSignals = new char[numberOfInputs];
   weights = new double[numberOfInputs];
   SetRandomWeights();
   outputSignal = 0.0;
   learningRate = 1.0;
   inputSignals[0] = 1;
}

Adaline::~Adaline()
{
   delete[] inputSignals;
   delete[] weights;
}

void Adaline::SetInputSignal(unsigned int signalIndex, char value)
{
   unsigned int actualIndex = signalIndex + 1;
   if (CheckSignalBounds(actualIndex))
   {
      inputSignals[actualIndex] = value;
   }
}

void Adaline::WeighInputs()
{
   // the output signal is the summation of each input signal
   // multiplied by its correpsonding weight.
   outputSignal = 0.0;
   for(unsigned int i = 0; i < numberOfInputs; ++i)
   {
      outputSignal += inputSignals[i] * weights[i];
   }
}

void Adaline::Learn(double desiredOutput)
{
   // Weights are adjusted by a fraction of the output
   // e(k) = d(k) - outputSignal
   // W(k+1) = W(k) + (learning rate/(n+1)) * e(k)*X(k)
   double errorSignal = desiredOutput - outputSignal;

   // sans +1 since bias weight is included in numberOfInputs.
   double learningRateFactor =
      learningRate/numberOfInputs;

   double learningRateFractionOfError =
      learningRateFactor * errorSignal;

   for (unsigned int i = 0; i < numberOfInputs; ++i)
   {
      weights[i] = weights[i]
         + learningRateFractionOfError * inputSignals[i];
   }
}

void Adaline::SetRandomWeights()
{
   srand(time(NULL));
   for (unsigned int i = 0; i < numberOfInputs; ++i)
   {
      weights[i] = (double)rand() / rand();
   }
}
