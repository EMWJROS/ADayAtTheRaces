#include <iostream>
#include <algorithm>
#include "Racetrack.h"

using namespace std;

int Racetrack::raceCounter = 0;

/******************************************************************************
 * Sorts a vector of pointers to Horse objects
 *
 * Friend of the Horse class
 * @param contestants Vector of Horse pointers
 * @return True if the vector already was in order
 *****************************************************************************/
bool Racetrack::race(HorsePen &contestants)
  {
    if (contestants.size() <= 1)
      {
	return true;
      }

    if (contestants.size() > NUM_OF_HORSES_IN_RACE)
      {
	cout << "Trying to race too many horses!" << endl;
	return false;
      }

    bool inOrder = true;

    for (int i=0; i < contestants.size()-1; ++i)
      {
	inOrder &= (contestants[i]->raceTime < contestants[i+1]->raceTime);
      }

    if (!inOrder)
      {
	struct winner{
	  inline bool operator()(Horse* a, Horse* b)
	  {
	    return a->raceTime < b->raceTime;
	  }
	};

	sort(contestants.begin(), contestants.end(), winner());
      }
    raceCounter++;
    return inOrder;
  }

int Racetrack::getNumberOfRaces()
{
  return raceCounter;
}
