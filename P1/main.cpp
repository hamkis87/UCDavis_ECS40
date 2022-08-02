#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include "flight.h"
#include "plane.h"

int getNumberOfFlights(std::ifstream &inputFileStream);
bool getFlightInfo(std::ifstream &inputFileStream, Flight *flights, int numFlights);
bool getPlaneInfo(std::ifstream &inputFileStream, Plane *plane);
void initializePassengers(Plane *plane);
void addPassenger(Plane *plane, std::string rowSeat, std::string passenger);
void printPassengers(Plane *plane);
void mapRowSeat(std::string const &rowSeat, int &row, int &seat);
int main()
{
    /*
    It may only contain:
        a declaration of Flight* named flights,
        a declaration of an int named numFlights,
        function calls,
        one while loop,
        and a return statement
    */
    std::ifstream inputFileStream("reservations.txt");
    int numFlights = getNumberOfFlights(inputFileStream);
    Flight *flights = new Flight[numFlights]; // free memory before main returns
    getFlightInfo(inputFileStream, flights, numFlights);
    for (int i = 0; i < numFlights; ++i)
    {
        std::cout << "flights at " << i << " :" << std::endl;
        std::cout << "number = " << flights[i].flightNum;
        std::cout << " , origin = " << flights[i].origin;
        std::cout << ", dest = " << flights[i].destination << std::endl;
        printPassengers(flights[i].plane);
    }
    return 0;
}

int getNumberOfFlights(std::ifstream &inputFileStream)
{
    if (!inputFileStream.is_open())
    {
        std::cerr << "Cannot find the file reservations.txt" << std::endl;
        return -1;
    }
    std::string numFlightsAsString;
    std::stringstream stringStream;
    int numFlights;
    if (getline(inputFileStream, numFlightsAsString) &&
        stringStream << numFlightsAsString &&
        stringStream >> numFlights)
    {
        std::cout << "No. of flights is " << numFlights << std::endl;
        return numFlights;
    }
    else
    {
        std::cout << " First line of file is not well-formatted" << std::endl;
        return -1;
    }
}

bool getFlightInfo(std::ifstream &inputFileStream, Flight *flights, int numFlights)
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
        if (!getPlaneInfo(inputFileStream, flight->plane))
        {
            std::cout << "Error reading Plane info." << std::endl;
            return false;
        }
        flights[id] = *flight;
    }

    return true;
}

bool getPlaneInfo(std::ifstream &inputFileStream, Plane *plane)
{
    std::string line;
    std::stringstream stringStream;
    if (!(getline(inputFileStream, line) && (stringStream << line) &&
          (stringStream >> plane->rows) && (stringStream >> plane->width) &&
          (stringStream >> plane->reserved)))
    {
        std::cout << "Error reading Plane rows/width/reserved." << std::endl;
        return false;
    }
    initializePassengers(plane);
    for (int i = 0; i < plane->reserved; ++i)
    {
        std::string s, r, p;
        std::stringstream ss, rs;
        if (!(getline(inputFileStream, line) && (ss << line) && (ss >> s)))
        {
            std::cout << "Error reading Plane rows/width/reserved." << std::endl;
            return false;
        }
        // std::cout << "row and seat letter: " << s << "." << std::endl;
        std::getline(ss, r);
        rs << r;
        rs >> std::ws;
        std::getline(rs, p);
        // std::cout << "passenger name: " << p << "." << std::endl;
        addPassenger(plane, s, p);
    }
    return true;
}

void initializePassengers(Plane *plane)
{
    plane->passengers = new char **[plane->rows];
    for (int i = 0; i < plane->rows; ++i)
    {
        plane->passengers[i] = new char *[plane->width];
        for (int j = 0; j < plane->width; ++j)
        {
            plane->passengers[i][j] = nullptr;
        }
    }
}

void addPassenger(Plane *plane, std::string rowSeat, std::string passenger)
{
    int row, seat;
    mapRowSeat(rowSeat, row, seat);
    plane->passengers[row][seat] = new char[passenger.length()];
    for (int i = 0; i < passenger.length(); i++)
        plane->passengers[row][seat][i] = passenger.at(i);
}

void printPassengers(Plane *plane)
{
    for (int i = 0; i < plane->rows; ++i)
    {
        for (int j = 0; j < plane->width; ++j)
        {
            char *passenger = plane->passengers[i][j];
            if (passenger != nullptr)
                std::cout << passenger << " ***** ";
            else
                std::cout << "EMPTY ***** ";
        }
        std::cout << std::endl;
    }
}

void mapRowSeat(std::string const &rowSeat, int &row, int &seat)
{
    std::stringstream rowSeatStringStream;
    rowSeatStringStream << rowSeat;
    int r;
    char c;
    if (!(rowSeatStringStream >> r && rowSeatStringStream >> c))
    {
        std::cout << "Row/Seat is not well-formatted." << std::endl;
    }
    else
    {
        row = r - 1;
        seat = c - 'A';
    }
}