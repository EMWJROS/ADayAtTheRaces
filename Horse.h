#ifndef __HORSE_H
#define __HORSE_H

#include "globalDefines.h"
#include <string>
#include <vector>
#include <array>

class Racetrack;

class Horse
{
 public:
  Horse(std::string s, int rt) : name(s), raceTime(rt) {};
  std::string name;

private:
  int raceTime;

/* Declare friend function that are entrusted to look at the raceTime.*/
friend class Racetrack;
friend void displayResults(std::array<Horse*, MAX_NUM_OF_HORSES> &raceHorses);

};

/** Contains a fixed number of Horses.*/
typedef std::array<Horse*, MAX_NUM_OF_HORSES> Stable;
/** Contains a number of horses.*/
typedef std::vector<Horse*> HorsePen;


#endif
