#ifndef VIEWERCRITIC_H_
#define VIEWERCRITIC_H_

#include <cmath>
#include <limits>

#define DEBUG_VIEW_CRITIC

namespace CompGeo
{
   // Define a "critic" for Quadtrees
   // This critic is meant to be taken as a proxy
   // for the third-party viewing program that would
   // utilize the output of the top-down map created
   // from the geospatial data.
   inline bool IsQuadtreeSuitable(const Quadtree& which)
   {
      bool suitable = false;
      // first condition, length must be an even power of two
      Quadtree::LengthType length = which.GetLengthOfRootNode();
      Quadtree::LengthType typeEpsilon =
         std::numeric_limits<Quadtree::LengthType>::epsilon();
      
      // no guarantees as to data type, so we loop
      // total amount we have to loop is equal to number of possible
      // bits
      unsigned int loopStop = sizeof(Quadtree::LengthType) * 4;

#ifdef DEBUG_VIEW_CRITIC
      std::cout << "Checking for " << length << std::endl;
      std::cout << "type eps: " << typeEpsilon << std::endl;
#endif

      for (unsigned int i = 1; i <= loopStop; ++i)
      {
         Quadtree::LengthType lengthInterval = pow(2, i);

         if ((lengthInterval - length) <= typeEpsilon)
         {
#ifdef DEBUG_VIEW_CRITIC
            std::cout << "Suitable at " << length << std::endl;
#endif
            suitable = true;
         }
         // Don't let this loop go on if not necessary
         if (suitable || (lengthInterval > length))
         {
            i = loopStop + 1;
         }
         
      }
      return suitable;
   }
}

#endif
