#include "StudFarm.h"

Horse* StudFarm::makeHorse(std::string name)
{
  Horse* horse = new Horse(name, horseArray[horseIndex++]);
  return horse;
}


