all: aDayAtTheRaces.exe

aDayAtTheRaces.exe: aDayAtTheRaces.o StudFarm.o
	g++ -o aDayAtTheRaces.exe -g aDayAtTheRaces.o StudFarm.o

aDayAtTheRaces.o: aDayAtTheRaces.cpp
	gcc -c -std=gnu++0x aDayAtTheRaces.cpp

StudFarm.o: StudFarm.cpp
	gcc -c -std=gnu++0x StudFarm.cpp

clean:
	rm -f *.o *.exe 
	rm -f *~

