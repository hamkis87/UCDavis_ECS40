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
    Flight *flights = new Flight[numFlights]; // free memory before main returns
    getFlightsInfo(inputFileStream, flights, numFlights);
    std::cout << "main: flight 0 address: " << &(flights[0]) << std::endl;
    std::cout << "main: flight 1 address: " << &(flights[1]) << std::endl;
    std::cout << "main: flight 2 address: " << &(flights[2]) << std::endl;
    std::cout << "main: flight 3 address: " << &(flights[3]) << std::endl;
    while (interactWithUser(flights, numFlights))
        ;
    putFlightsInfo(outputFileStream, flights, numFlights);
    deallocateFlights(&flights, numFlights);
    return 0;
}