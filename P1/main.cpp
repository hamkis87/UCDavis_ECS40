#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string.h>
#include "utilities.h"
#include "flight.h"
#include "plane.h"

int main()
{
    std::ifstream inputFileStream("reservations.txt");
    std::ofstream outputFileStream("reservations2.txt");
    int numFlights = getNumberOfFlights(inputFileStream);
    Flight *flights = new Flight[numFlights];
    getFlightsInfo(inputFileStream, flights, numFlights);
    while (interactWithUser(flights, numFlights))
        ;
    putFlightsInfo(outputFileStream, flights, numFlights);
    deallocateFlights(&flights, numFlights);
    return 0;
}