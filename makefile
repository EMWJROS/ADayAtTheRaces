all: aDayAtTheRaces.exe

aDayAtTheRaces.exe: aDayAtTheRaces.o StudFarm.o Racetrack.o
	g++ -o aDayAtTheRaces.exe -g aDayAtTheRaces.o StudFarm.o Racetrack.o

aDayAtTheRaces.o: aDayAtTheRaces.cpp
	gcc -c -std=gnu++0x aDayAtTheRaces.cpp

StudFarm.o: StudFarm.cpp
	gcc -c -std=gnu++0x StudFarm.cpp

Racetrack.o: Racetrack.cpp
	gcc -c -std=gnu++0x Racetrack.cpp
clean:
	rm -f *.o *.exe 
	rm -f *~

