#ifndef FLIGHT_H
#define FLIGHT_H
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string.h>

#include "plane.h"

typedef struct
{
    int flightNum;
    char origin[20];
    char destination[20];
    Plane *plane;
} Flight;

bool isValidFlightNo(const Flight *flights, int flightNo, int numFlights, int &flightIndex);
bool putFlightsInfo(std::ofstream &outputFileStream, Flight *flights, int numFlights);
bool getFlightsInfo(std::ifstream &inputFileStream, Flight *flights, int numFlights);
void printFlights(const Flight *flights, const int numFlights);
bool interactWithUser(Flight *flights, const int numFlights);
bool addUserPassenger(Flight *flights, const int numFlights);
void printFlightsInfo(const Flight *flights, const int numFlights);
void addPassengerInfo(Flight *flight);
void printFlightSeating(Flight *flight);
void deallocateFlights(Flight **flightsP, const int numFlights);
void copyStr(Flight *flight, const std::string origin, const std::string destination);
// bool getFlightsInfo(std::ifstream &inputFileStream, Flight *flights, int numFlights);

#endif