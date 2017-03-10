#include "Horse.h"
#include "StudFarm.h"
#include <iostream>
#include <array>
#include <algorithm>
#include <functional>

#define WINDOW 1

using namespace std;

int raceCounter = 0;

/******************************************************************************
 * Sorts an array of pointers to Horse objects
 *
 * Friend of the Horse class
 * @param contestants Array of Horse pointers
 * @return True if the array already was in order
 *****************************************************************************/
bool race( array<Horse*, NUM_OF_HORSES_IN_RACE> &contestants)
  {
    bool inOrder = true;

    for (int i=0; i < NUM_OF_HORSES_IN_RACE-1; ++i)
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

main()
{
  StudFarm stuteri;
  array<Horse*, MAX_NUM_OF_HORSES> raceHorses;

  /* Fill our stable with horses from the stud farm */
  for(int i=0; i<MAX_NUM_OF_HORSES; ++i)
    {
      string number = to_string(i);
      raceHorses[i] = stuteri.makeHorse(number);
    }

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
	  /* Adjust the final race. */
	  if (startingHorse < stoppingHorse)
	    {
	      startingHorse = stoppingHorse;
	    }

	  /* Pick out our starting lineup */
	  array<Horse*, NUM_OF_HORSES_IN_RACE> lineup;

	  for (int i=0; i < NUM_OF_HORSES_IN_RACE; ++i)
	    {
	      lineup[i] = raceHorses[i+startingHorse];
	    }

	  bool lastRaceOrdered = race(lineup);
	  ordered = ordered && lastRaceOrdered;

	  /* Put them back in the stable in order. */
	  for (int i=0; i<NUM_OF_HORSES_IN_RACE; ++i)
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

  return 0;
}
