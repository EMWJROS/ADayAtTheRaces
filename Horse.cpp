#include "Horse.h"

void Horse::isSlowerThan(std::string competitor)
{
  relations[competitor] = SLOWER;
}
  
void Horse::isFasterThan(std::string competitor)
{
  relations[competitor] = FASTER;
}

SpeedRelation Horse::comparedTo(std::string competitor)
{
  auto it = relations.find(competitor);

  if (it == relations.end())
    {
      return UNDETERMINED;
    }
  else
    {
      return it->second;
    }
}
