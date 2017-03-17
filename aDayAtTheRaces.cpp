#include "globalDefines.h"
#include "Horse.h"
#include "StudFarm.h"
#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

/** Contains a fixed number of Horses.*/
typedef array<Horse*, MAX_NUM_OF_HORSES> Stable;
/** Contains a number of horses.*/
typedef vector<Horse*> HorsePen;
/** Counts how many races we've actually run.*/
int raceCounter = 0;

/******************************************************************************
 * Sorts a vector of pointers to Horse objects
 *
 * Friend of the Horse class
 * @param contestants Vector of Horse pointers
 * @return True if the vector already was in order
 *****************************************************************************/
bool race(HorsePen &contestants)
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

/*****************************************************************************
 * Displays the outcome of the race
 * 
 * If compiled with ALL_RESULTS, it shows the placement of the horses.
 * Declared as friend of the Horse class so it can show the race time.
 * @param raceHorses Reference to the stable
 ****************************************************************************/
void displayResults(Stable &raceHorses)
{
  /* Display the results. */
#ifdef ALL_RESULTS
  int position = 1;

  for (auto a : raceHorses)
    {
      cout << "Position " << position++ << " Horse #" << a->raceTime << endl;
    }
#endif

  cout << "In total " << raceCounter << " races were run." << endl;
  cout << "(It might have been easier to buy a stop watch ...)" << endl;
}

/****************************************************************************
 * Races a group of horses against each other
 * 
 * Slower and faster horses are added to vectors.
 *
 * @param testLineup A vector of pointers to horses
 * @param name       The name of the pivot horse
 * @param fastBin    A vector to put fast horses in
 * @param slowBin    A vector to put slow horses in
 ***************************************************************************/
void raceAgainstPivot(HorsePen &testLineup, 
		      string name,
		      HorsePen &fastBin,
		      HorsePen &slowBin)
{
  race(testLineup);

  int fastHorse = 0;
  while (testLineup[fastHorse]->name != name)
    {
      fastBin.push_back(testLineup[fastHorse++]);
    }

  int slowHorse = fastHorse+1;
  while(slowHorse < testLineup.size())
    {
      slowBin.push_back(testLineup[slowHorse++]);
    }
}

/*****************************************************************************
 * Implements a quicksort algorithm on a portion of an array of Horses
 *
 * @param raceHorses The stable to sort
 * @param firstIndex Index of first horse to include in sorting
 * @param lastIndex  Index of last horse to iclude
 ****************************************************************************/
void quicksort(Stable &raceHorses, 
	       int firstIndex, int lastIndex)
{
  if (lastIndex - firstIndex < NUM_OF_HORSES_IN_RACE)
    {
      /* Copy to vector and race.*/
      HorsePen lineup;
      for (int i=firstIndex; i<=lastIndex; ++i)
	{
	  lineup.push_back(raceHorses[i]);
	}
      race(lineup);

      /* Put back. */
      for (int i=0; i<lineup.size(); ++i)
	{
	  raceHorses[firstIndex + i] = lineup[i];
	}

    }
  else
    {
      /* Pick a horse in the middle as pivot.
	 This poor horse has to race against all others.
	 Fortunately, in this world, horses don't get tired.*/
      int pivotHorse = (lastIndex + firstIndex)/2;

      /* We need to separate faster and slower horses after having
	 raced them.*/
      HorsePen fastBin;
      HorsePen slowBin;

      int contestant = firstIndex;
      int numberInRace = 0;
      HorsePen testLineup;
      /* Put the pivot on the starting line.*/
      testLineup.push_back(raceHorses[pivotHorse]);

      while (contestant <= lastIndex)
	{
	  /* We've already got the pivotHorse on the starting line.*/
	  if (contestant != pivotHorse)
	    {
	      testLineup.push_back(raceHorses[contestant]);
	      numberInRace++;
	    }
	  contestant++;
	  
	  /* For every fourth horse we add, we race them against the pivot.
	     Horses that are faster are put in the fastBin and slower
	     ones in the slowBin.*/
	  if (numberInRace == (NUM_OF_HORSES_IN_RACE -1))
	    {
	      raceAgainstPivot(testLineup, raceHorses[pivotHorse]->name,
			       fastBin, slowBin);

	      testLineup.clear();
	      testLineup.push_back(raceHorses[pivotHorse]);
	      numberInRace = 0;
	    }

        }

      /* Do we have any un-raced horses left on the starting line. */
      if (testLineup.size() != 1)
	{
	  /* Race them.*/
	  raceAgainstPivot(testLineup, raceHorses[pivotHorse]->name,
			   fastBin, slowBin);
	}

      /* Put horses back into stable.*/
      Horse* pivotHorse_p = raceHorses[pivotHorse];
      int horse = firstIndex;
      for (int i=0; i < fastBin.size(); ++i)
	{
	  raceHorses[horse++] = fastBin[i];
	}

      pivotHorse = horse;
      raceHorses[horse++] = pivotHorse_p;

      for (int i=0; i < slowBin.size(); ++i)
	{
	  raceHorses[horse++] = slowBin[i];
	}

      /* Race the ones that came from the fastBin.*/
      quicksort(raceHorses, firstIndex, pivotHorse-1);

      /* And their slower fellows ... */
      quicksort(raceHorses, pivotHorse+1, lastIndex);
    }

}

/*****************************************************************************
 * Races horses using quicksort
 *
 * @param raceHorse The stable
 ****************************************************************************/
void horseracingByQuicksort(Stable raceHorses)
{
  quicksort(raceHorses, 0, raceHorses.size()-1);
  displayResults(raceHorses);

}

main()
{
  StudFarm stuteri;
  Stable stable;

  /* Fill our stable with horses from the stud farm */
  for(int i=0; i<MAX_NUM_OF_HORSES; ++i)
    {
      string number = to_string(i);
      stable[i] = stuteri.makeHorse(number);
    }

  horseracingByQuicksort(stable);
  return 0;
}
