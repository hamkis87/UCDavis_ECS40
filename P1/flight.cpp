#include <iostream>
#include "flight.h"

bool getFlightsInfo(std::ifstream &inputFileStream, Flight *flights, int numFlights)
{
    for (int id = 0; id < numFlights; ++id)
    {
        Flight *flight = new Flight;
        flight->plane = new Plane;
        std::string flightNumAsString, origin, destination;
        std::stringstream stringStream;
        if (!(getline(inputFileStream, flightNumAsString) &&
              (stringStream << flightNumAsString) &&
              (stringStream >> flight->flightNum)))
        {
            std::cout << "Error reading flight number." << std::endl;
            return false;
        }
        if (!(getline(inputFileStream, origin) &&
              getline(inputFileStream, destination)))
        {
            std::cout << "Error reading flight origin/destination." << std::endl;
            return false;
        }
        strcpy(flight->origin, origin.c_str());
        strcpy(flight->destination, destination.c_str());
        //  copyStr(flight, origin, destination);
        if (!getPlaneInfo(inputFileStream, flight->plane))
        {
            std::cout << "Error reading Plane info." << std::endl;
            return false;
        }
        flights[id] = *flight;
        delete flight;
    }
    inputFileStream.close();
    return true;
}

bool putFlightsInfo(std::ofstream &outputFileStream, Flight *flights, int numFlights)
{
    outputFileStream << numFlights;
    for (int id = 0; id < numFlights; ++id)
    {
        Flight flight = flights[id];
        outputFileStream << std::endl
                         << flight.flightNum;
        outputFileStream << std::endl
                         << flight.origin;
        outputFileStream << std::endl
                         << flight.destination;
        putPlaneInfo(outputFileStream, flight.plane);
    }
    outputFileStream.close();
    return true;
}

void printFlights(const Flight *flights, const int numFlights)
{
    for (int i = 0; i < numFlights; ++i)
    {
        std::cout << "flights at " << i << " :" << std::endl;
        std::cout << "number = " << flights[i].flightNum;
        std::cout << " , origin = " << flights[i].origin;
        std::cout << ", dest = " << flights[i].destination << std::endl;
        printPassengers(flights[i].plane);
    }
}

bool interactWithUser(Flight *flights, const int numFlights)
{
    printMenuHeader();
    int firstUserInput = getFirstUserInput();
    // std::cout << "firstUserInput: " << firstUserInput << std::endl;
    if (firstUserInput == 1)
    {
        printFlightsInfo(flights, numFlights);
        return addUserPassenger(flights, numFlights);
    }
    else
    {
        std::cout << "Goodbye." << std::endl;
        return false;
    }
}

bool addUserPassenger(Flight *flights, const int numFlights)
{
    while (true)
    {
        int flightIndex;
        std::cout << "Flight number (0 = exit): ";
        std::string line;
        std::getline(std::cin, line);
        int choice = getNumber(line);
        if (choice == 0)
            return false;
        else if (choice == -1)
        {
            std::cout << "Your number is invalid." << std::endl;
        }
        else if (isValidFlightNo(flights, choice, numFlights, flightIndex))
        {
            // std::cout << "flight index " << flightIndex << " has number " << choice << std::endl;
            if (isFullyReserved(flights[flightIndex].plane))
                std::cout << "We are sorry but Flight #" << choice << " is full." << std::endl
                          << std::endl;
            else
                addPassengerInfo(&(flights[flightIndex]));
            return true;
        }
        else
        {
            std::cout << "We do not have a flight number ";
            std::cout << choice << "." << std::endl;
        }
        std::cout << "Please try again." << std::endl
                  << std::endl;
    }
}

void printFlightsInfo(const Flight *flights, const int numFlights)
{
    std::cout << std::left << std::setw(6) << "Flt#";
    std::cout << std::left << std::setw(20) << "Origin";
    std::cout << std::left << std::setw(20) << "Destination" << std::endl;
    for (int i = 0; i < numFlights; ++i)
    {
        Flight flight = flights[i];
        std::cout << std::left << std::setw(6) << flight.flightNum;
        std::cout << std::left << std::setw(20) << flight.origin;
        std::cout << std::left << std::setw(20) << flight.destination << std::endl;
    }
    std::cout << std::endl;
}

bool isValidFlightNo(const Flight *flights, int flightNo,
                     int numFlights, int &flightIndex)
{
    for (int i = 0; i < numFlights; ++i)
    {
        if (flights[i].flightNum == flightNo)
        {
            flightIndex = i;
            return true;
        }
    }
    return false;
}

void addPassengerInfo(Flight *flight)
{
    std::string passenger = getPassengerName();
    printFlightSeating(flight);
    // std::cout << "There are #" << flight->plane->reserved;
    // std::cout << " seats reserved." << std::endl;
    while (true)
    {
        int row;
        char letter;
        if (reserveSeat(flight->plane, &row, &letter)) // if(isFullyBooked() || reserveSeat(flight))
        {
            // std::cout << "seat is: row " << row << " letter: " << letter << std::endl;
            std::stringstream seatStream;
            std::string seatStr;
            seatStream << row << letter;
            seatStream >> seatStr;
            addPassenger(flight->plane, seatStr, passenger);
            // printFlightSeating(flight);
            flight->plane->reserved++;
            break;
        }
    }
}

void printFlightSeating(Flight *flight)
{
    Plane *plane = flight->plane;
    int rows = plane->rows;
    int width = plane->width;
    printPlaneHeader(width);
    for (int i = 0; i < rows; ++i)
    {
        std::cout << " ";
        std::cout << std::left << std::setw(4) << i + 1;
        for (int j = 0; j < width; ++j)
        {
            if (plane->passengers[i][j] != nullptr)
                std::cout << "X";
            else
                std::cout << "-";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl
              << "X = reserved." << std::endl
              << std::endl;
}

void deallocateFlights(Flight **flightsP, const int numFlights)
{
    Flight *flights = *flightsP;
    for (int i = 0; i < numFlights; ++i)
    {
        Flight *flight = &(flights[i]);
        deallocatePlane(flight->plane);
    }
    delete[] flights;
}