airline.out: main.o plane.o flight.o utilities.o
	g++ -Wall -o airline.out main.o utilities.o plane.o flight.o -I.

main.o: main.cpp
	g++ -Wall -c main.cpp -I.
	
plane.o: plane.cpp plane.h
	g++ -Wall -c plane.cpp -I.

flight.o: flight.cpp flight.h
	g++ -Wall -c flight.cpp -I.

utilities.o: utilities.cpp utilities.h
	g++ -Wall -c utilities.cpp -I.

clean:
	rm *.o airline.out