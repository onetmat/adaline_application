#ifndef ADALINE_H_
#define ADALINE_H_

#include <iostream>

namespace CompIntel
{
   // Implements Widrow and Hoff's ADALINE circuit
   // from their paper, "Adaptive Switching Circuits"
   class Adaline
   {
   public:
      Adaline(unsigned int numSignals);
      ~Adaline();

      // Set all signals to 0
      inline void ClearInputSignals()
      {
         // start at 1, zero is the bias
         for (int i = 1; i < numberOfInputs; ++i)
         {
            inputSignals[i] = 0;
         }
      }

      // Allows individual signals to be set.
      void SetInputSignal(unsigned int signalIndex, char value);

      // Allow variation of the learning rate
      // Note: According to the literature, this value must range (0, 0.2]
      inline void SetLearningRate(double newRate)
      {
         learningRate = newRate;
      }

      // Read access to all member variables
      // Note: Facilitates logging during iterative learning.
      inline const double* GetWeightVector() const
      {
         return weights;
      }

      inline const char* GetInputSignalVector() const
      {
         return inputSignals;
      }

      inline double GetOutputSignal() const
      {
         return outputSignal;
      }

      inline const unsigned int GetNumberOfWeights() const
      {
         return numberOfInputs;
      }
      inline const unsigned int GetNumberOfInputs() const
      {
         // Only return the number of inputs that can be controlled
         // (directly set)
         return numberOfInputs - 1;
      }

      // Calculate the output signal based on the current input
      // and weight vectors.
      void WeighInputs();

      // Apply the learning algorithm detailed in Widrow and Hoff's
      // "Adaptive Switching Circuits"
      void Learn(double desiredOutput);

      // Print headers that correspond to the "detail" outputs
      // Input 0, input 1, ... input X, weight 0, weight 1, ... weight X
      // ending with Output signal
      void PrintCSVHeaders(std::ostream& stream) const;

      // Print the state of the current input vector
      // the current weight vector
      // and the current output signal value
      // in a format consistent with the CSV format.
      void PrintDetailsCSV(std::ostream& stream) const;

   private:
      // Seed the random number generator and assign random
      // weights into the vector.
      void SetRandomWeights();

      // Check a passed index to avoid over or under flow
      // returns true if the index is valid
      inline bool CheckSignalBounds(unsigned int index)
      {
         return (index >= 0 && index < numberOfInputs);
      }

      // Store the number of inputs for boundary checking
      // This includes the bias input.
      unsigned int numberOfInputs;

      // The input signals' representation will depend
      // on the modeling of the problem being solved by
      // the [M]?ADALINE system
      char *inputSignals;
      // Weights can be randomized with no side effects according
      // to Widrow and Hoff.
      double *weights;
      // The output signal literally is the dot product of the inputSignals
      // and weights vectors.
      double outputSignal;
      // Variable (mu) that determines how much of the error
      // and old weight values will change.
      double learningRate; // Defaults to 1
      // Store the last calculated error term
   };
}

#endif
