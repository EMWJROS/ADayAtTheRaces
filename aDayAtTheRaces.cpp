#include "Horse.h"
#include "StudFarm.h"
#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <functional>

#define WINDOW 1

using namespace std;

int raceCounter = 0;

/******************************************************************************
 * Sorts a vector of pointers to Horse objects
 *
 * Friend of the Horse class
 * @param contestants Vector of Horse pointers
 * @return True if the vector already was in order
 *****************************************************************************/
bool race( vector<Horse*> &contestants)
  {
    if (contestants.size() > NUM_OF_HORSES_IN_RACE)
      {
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

void bubblesort(array<Horse*, MAX_NUM_OF_HORSES> raceHorses)
{
  int stoppingHorse = 0;
  bool ordered  = false;

  /* Continue racing horses against each other. Quit when no further order
     can be achieved.*/
  while ((stoppingHorse < MAX_NUM_OF_HORSES - NUM_OF_HORSES_IN_RACE) &&
	 !ordered) 
    {
      int startingHorse = MAX_NUM_OF_HORSES - NUM_OF_HORSES_IN_RACE;
      /* Reset order. */
      ordered  = true;

      /* Check that there are enough horses to race against eachother. */
      while (startingHorse + (NUM_OF_HORSES_IN_RACE - WINDOW) > stoppingHorse)
	{

	  int numOfContestants = NUM_OF_HORSES_IN_RACE;

	  /* Adjust the final race. */
	  if (startingHorse < stoppingHorse)
	    {
	      /* We only race stoppingHorse to previous startingHorse. */
	      numOfContestants = startingHorse + NUM_OF_HORSES_IN_RACE - 
		WINDOW - stoppingHorse + 1;
	      startingHorse = stoppingHorse;
	    }

	  /* Pick out our starting lineup */
	  vector<Horse*> lineup;

	  for (int i=0; i < numOfContestants; ++i)
	    {
	      lineup.push_back(raceHorses[i+startingHorse]);
	    }

	  bool lastRaceOrdered = race(lineup);
	  ordered = ordered && lastRaceOrdered;

	  /* Put them back in the stable in order. */
	  for (int i=0; i<lineup.size(); ++i)
	    {
	      raceHorses[startingHorse+i] = lineup[i];
	    }

	  /* Move the window. */
	  startingHorse -= (NUM_OF_HORSES_IN_RACE - WINDOW);
	}

      stoppingHorse += WINDOW;

    } 

  /* Display the results. */
  int position = 1;

  for (auto a : raceHorses)
    {
      cout << "Position " << position++ << " Horse #" << a->raceTime << endl;
    }

  cout << "In total " << raceCounter << " races were run." << endl;
  cout << "(It might have been easier to buy a stop watch ...)" << endl;
}

main()
{
  StudFarm stuteri;
  array<Horse*, MAX_NUM_OF_HORSES> stable;

  /* Fill our stable with horses from the stud farm */
  for(int i=0; i<MAX_NUM_OF_HORSES; ++i)
    {
      string number = to_string(i);
      stable[i] = stuteri.makeHorse(number);
    }

  bubblesort(stable);

  return 0;
}
