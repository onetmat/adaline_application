#ifndef QUADTREE_ADAPTER_H_
#define QUADTREE_ADAPTER_H_

#include <vector>

#include "quadtree.h" // necessary for the length type member variable

namespace CompIntel
{
   class Adaline;
}

namespace CompGeo
{
   // The adaline adapter will track a quadtree
   // and will iteratively make changes to it,
   // storing the historical state as necessary.
   class AdalineAdapter
   {
   public:
      AdalineAdapter();
      ~AdalineAdapter() {}

      // Reset the adapter to allow the Adaline to judge
      // and modify a quadtree with a given root node length.
      void Reset(Quadtree::LengthType initialRootNodeLength);

      // This will execute the learning process until the
      // Adaline believes that the quadtree is suitable
      // for submission to the viewer critic.
      void AdjustQuadtree();

      // If in training mode, this method will punish
      // the adaline based on the history required to
      // get to the current state of the quadtree
      void PunishAdaline();

      // Similar to punish, but rewards the Adaline.
      void RewardAdaline();

      // Retrieve the number of iterations required to get
      // to the current Quadtree state
      inline std::vector<Quadtree::LengthType>::size_type
         GetNumItersToCurrentState() const
      {
         return lengthHistory.size();
      }

      // Retrieve the state of the quadtree as it stands.
      inline const Quadtree& GetQuadtree() const
      {
         return currentQuadtree;
      }

   private:
      // Actual implementation of teach routine.
      void TeachAdaline(bool punishing);

      // Converts the length to appropriate adaline input
      void SetAdalineInputs();

      // Quantize the Adaline output using the function from
      // "Punish/Reward..."
      inline int QuantizeAdalineOutput(double outputSignal)
      {
         int quantizedSignal = -1;
         if (outputSignal >= 0.0)
         {
            quantizedSignal = 1;
         }
         return quantizedSignal;
      }      

      // this adaline will examine the length of the root node
      // and determine if this length will produce a quadtree
      // suitable for the map viewer.
      CompIntel::Adaline quadtreeJudge;

      // store the current state of the Quadtree
      Quadtree currentQuadtree;

      // the adaline will affect the length of the quadtree
      // we need only track the length here.
      std::vector<Quadtree::LengthType> lengthHistory;
   };
}

#endif
