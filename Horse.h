#ifndef __HORSE_H
#define __HORSE_H

#include "globalDefines.h"
#include <string>
#include <vector>
#include <array>

class Horse
{
 public:
  Horse(std::string s, int rt) : name(s), raceTime(rt) {};
  std::string name;

private:
  int raceTime;

/* Declare friend function that are entrusted to look at the raceTime.*/
friend bool race( std::vector<Horse*> &contestants);
friend void displayResults(std::array<Horse*, MAX_NUM_OF_HORSES> &raceHorses);

};

#endif
