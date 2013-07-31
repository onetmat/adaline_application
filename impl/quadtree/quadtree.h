#ifndef QUADTREE_H_
#define QUADTREE_H_

namespace CompGeo
{
   // Define a quadtree in the simplest possible term
   // a rootNodeLength.
   class Quadtree
   {
   public:
      //typedef double LengthType;
      typedef unsigned long LengthType;
      Quadtree() { rootNodeLength = 0; }
      ~Quadtree() {}
      Quadtree(const Quadtree& rhs) { rootNodeLength = rhs.rootNodeLength; }

      // The rootNodeLength variable can be read/written
      // as appropriate based on user input.
      LengthType GetLengthOfRootNode() const { return rootNodeLength; }
      inline void SetLengthOfRootNode(LengthType newValue)
      {
         rootNodeLength = newValue;
      }

   private:
      LengthType rootNodeLength;
   };
}

#endif
