#ifndef __RACETRACK_H
#define __RACETRACK_H
#include <vector>
#include "globalDefines.h"
#include "Horse.h"

class Racetrack
{
  /** Counts how many races we've actually run.*/
  static int raceCounter;

 public:
  static bool race(std::vector<Horse*> &lineup);
  static int getNumberOfRaces();

};

#endif
