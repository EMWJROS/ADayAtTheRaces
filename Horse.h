#ifndef __HORSE_H
#define __HORSE_H

#include <string>
#include <vector>

#define NUM_OF_HORSES_IN_RACE 5

class Horse
{
 public:
  Horse(std::string s, int rt) : name(s), raceTime(rt) {};
  std::string name;
  friend bool race( std::vector<Horse*> &contestants);

private:
  int raceTime;

  

};

#endif
