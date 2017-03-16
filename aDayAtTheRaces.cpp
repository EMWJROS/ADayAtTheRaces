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

void displayResults(array<Horse*, MAX_NUM_OF_HORSES> &raceHorses)
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

void horseracing(array<Horse*, MAX_NUM_OF_HORSES> &raceHorses, 
	  int firstIndex, int lastIndex)
{
  if (lastIndex - firstIndex < 5)
    {
      // copy to vector and race
      vector<Horse*> lineup;
      for (int i=firstIndex; i<=lastIndex; ++i)
	{
	  lineup.push_back(raceHorses[i]);
	}
      race(lineup);

      // put back
      for (int i=0; i<lineup.size(); ++i)
	{
	  raceHorses[firstIndex + i] = lineup[i];
	}
      // done
    }
  else
    {
      int pivotHorse = (lastIndex + firstIndex)/2;
      vector<Horse*> fastBin;
      vector<Horse*> slowBin;

      int contestant = firstIndex;
      int numberInRace = 0;
      vector<Horse*> testLineup;
      testLineup.push_back(raceHorses[pivotHorse]);

      while (contestant <= lastIndex)
	{
	  if (contestant != pivotHorse)
	    {
	      testLineup.push_back(raceHorses[contestant]);
	      numberInRace++;
	    }
	  contestant++;
	  
	  /* Every fourth horse we add, we race them against the pivot. */
	  if (numberInRace == 4)
	    {
	      race(testLineup);

	      int fastHorse = 0;
	      while (testLineup[fastHorse]->name !=
					  raceHorses[pivotHorse]->name)
		{
		  fastBin.push_back(testLineup[fastHorse++]);
		}

	      int slowHorse = fastHorse+1;
	      while(slowHorse < testLineup.size())
		{
		  slowBin.push_back(testLineup[slowHorse++]);
		}
	      testLineup.clear();
	      testLineup.push_back(raceHorses[pivotHorse]);
	      numberInRace = 0;
	    }

        }
	    /* Do we have any un-raced horses left in the pen? */
	    if (testLineup.size() != 1)
	      {
		race(testLineup);

		int fastHorse = 0;
		while (testLineup[fastHorse]->name !=
					    raceHorses[pivotHorse]->name)
		  {
		    fastBin.push_back(testLineup[fastHorse++]);
		  }

		int slowHorse = fastHorse+1;
		while(slowHorse < testLineup.size())
		  {
		    slowBin.push_back(testLineup[slowHorse++]);
		  }
	      }

	  // put bins back into stable, and race again

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

	  horseracing(raceHorses, firstIndex, pivotHorse-1);
	  horseracing(raceHorses, pivotHorse+1, lastIndex);
    }

}

void quicksort(array<Horse*, MAX_NUM_OF_HORSES> raceHorses)
{
  horseracing(raceHorses, 0, MAX_NUM_OF_HORSES-1);
  displayResults(raceHorses);

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

  quicksort(stable);
  return 0;
}
