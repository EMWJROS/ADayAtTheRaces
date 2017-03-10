#ifndef __STUD_FARM_H
#define __STUD_FRAM_H

#include <string>
#include "Horse.h"
#define MAX_NUM_OF_HORSES 125

class StudFarm
{
 public: 
 StudFarm() :
  horseIndex(0),
  horseArray{107,47,102,64,50,100,28,91,27,5,
      22,114,23,42,13,3,93,8,92,79,
      53,83,63,7,15,66,105,57,14,65,
      58,113,112,1,62,103,120,72,111,51,
      9,36,119,99,30,20,25,84,16,
      116,98,18,37,108,10,80,101,35,75,
      39,109,17,38,117,60,46,85,31,41,
      12,29,26,74,77,21,4,70,61,88,
      44,49,94,122,2,97,73,69,71,86,
      45,96,104,89,68,40,6,87,115,54,
      123,125,90,32,118,52,11,33,106,95,
      76,19,82,56,121,55,34,24,43,124,
      81,48,110,78,67,59} {};
  Horse* makeHorse(std::string name);

 private:
  int horseArray[MAX_NUM_OF_HORSES];

  int horseIndex ;
};

#endif
