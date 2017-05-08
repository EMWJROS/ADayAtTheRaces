#ifndef __HORSE_H
#define __HORSE_H

#include "globalDefines.h"
#include <string>
#include <vector>
#include <array>
#include <map>

enum SpeedRelation
{ UNDETERMINED,
  FASTER,
  EQUAL,
  SLOWER};

class Racetrack;

class Horse
{
 public:
  Horse(std::string s, int rt) : name(s), raceTime(rt) {};
  std::string name;
  void isSlowerThan(std::string competitor);
  void isFasterThan(std::string competitor);
  SpeedRelation comparedTo(std::string competitor);

private:
  int raceTime;
  std::map<std::string, SpeedRelation> relations;


/* Declare friend function that are entrusted to look at the raceTime.*/
friend class Racetrack;
friend void displayResults(std::array<Horse*, MAX_NUM_OF_HORSES> &raceHorses);

};

/** Contains a fixed number of Horses.*/
typedef std::array<Horse*, MAX_NUM_OF_HORSES> Stable;
/** Contains a number of horses.*/
typedef std::vector<Horse*> HorsePen;


#endif
