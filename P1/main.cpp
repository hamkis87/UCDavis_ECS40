#include <iostream>
#include <iomanip>
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
void printFlights(const Flight *flights, const int numFlights);
int interactWithUser(Flight *flights, const int numFlights);
void printMenuHeader();
int getFirstUserInput();
int getUserFlightNo(Flight *flights);
bool addUserPassenger(Flight *flights, const int numFlights);
bool isValidFlightNo(const Flight *flights, int flightNo, int numFlights, int &flightIndex);
bool isValidRow(Flight *flight, int row);
void addPassengerInfo(Flight *flight);
bool reserveSeat(Flight *flight, int *seat, char *letter);
bool hasVacantSeat(Flight *flight, int row);
bool isValidSeatLetter(Flight *flight, int row, char letter);
bool isVacantSeat(Flight *flight, int row, char letter);
char getSeatLetter();
int getRow();
int getNumber(std::string line);
std::string getPassengerName();
void printFlightsInfo(const Flight *flights, const int numFlights);
void printFlightSeating(Flight *flight);
void printPlaneHeader(int width);

int main()
{
    std::ifstream inputFileStream("reservations.txt");
    int numFlights = getNumberOfFlights(inputFileStream);
    Flight *flights = new Flight[numFlights]; // free memory before main returns
    getFlightInfo(inputFileStream, flights, numFlights);
    // printFlights(flights, numFlights);
    interactWithUser(flights, numFlights);
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
        // std::cout << "No. of flights is " << numFlights << std::endl;
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

int interactWithUser(Flight *flights, const int numFlights)
{
    printMenuHeader();
    int firstUserInput = getFirstUserInput();
    // std::cout << "firstUserInput: " << firstUserInput << std::endl;
    if (firstUserInput == 1)
    {
        printFlightsInfo(flights, numFlights);
        if (addUserPassenger(flights, numFlights))
        {
        }
    }
    return firstUserInput;
}

void printMenuHeader()
{
    std::cout << "ECS Flight Reservation Menu" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "1. Add Passenger." << std::endl
              << std::endl;
}

int getFirstUserInput()
{
    while (true)
    {
        std::cout << "Please enter your choice: ";
        std::string line;
        std::getline(std::cin, line);
        int choice = getNumber(line);
        if (choice == 0 || choice == 1)
            return choice;
        else if (choice == -1)
        {
            std::cout << "Your number is invalid." << std::endl;
        }
        else
        {
            std::cout << choice << " is not an available choice." << std::endl;
        }
        std::cout << "Please try again." << std::endl
                  << std::endl;
    }
}

int getUserFlightNo(Flight *flights, const int flightNo)
{
    return 221;
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
            std::cout << "flight index " << flightIndex << " has number " << choice << std::endl;
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

void addPassengerInfo(Flight *flight)
{
    std::string passenger = getPassengerName();
    printFlightSeating(flight);
    while (true)
    {
        int seat;
        char letter;
        if (reserveSeat(flight, *seat, *letter)) // if(isFullyBooked() || reserveSeat(flight))
        {
            addPassengerAt(flight, passenger, seat, letter);
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
}

int getNumber(std::string line)
{
    std::stringstream stringStream(line);
    int number;
    char c;
    if (stringStream >> number && !(stringStream >> c))
        return number;
    return -1;
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

std::string getPassengerName()
{
    std::string passengerName;
    std::cout << "Please enter the name of the passenger: ";
    std::getline(std::cin, passengerName);
    return passengerName;
}

bool reserveSeat(Flight *flight, int *seat, char *letter)
{
    int row = getRow();
    if (!isValidRow(flight, row))
    {
        std::cout << "There is no row #" << row << " on this flight.";
    }
    else if (!hasVacantSeat(flight, row))
    {
        std::cout << "Row #" << row << " is full!";
    }
    else
    {
        char letter = getSeatLetter();
        if (!isValidSeatLetter(flight, row, letter))
        {
            std::cout << "Letter #" << letter << " does not exist";
        }
        else if (!isVacantSeat(flight, row, letter))
        {
            std::cout << " That seat is already occupied.";
        }
        else
            return true;
    }
    std::cout << std::endl;
    std::cout << "Please try again." << std::endl;
    return false;
}

int getRow()
{
    std::cout << "Please enter the row of the seat you wish to reserve: ";
    std::string rowStr;
    std::getline(std::cin, rowStr);
    return getNumber(rowStr);
}

bool isValidFlightNo(const Flight *flights, int flightNo,
                     int numFlights, int &flightIndex)
{
    bool result = false;
    for (int i = 0; i < numFlights; ++i)
    {
        if (flights[i].flightNum == flightNo)
        {
            flightIndex = i;
            return true;
        }
    }
    return result;
}

void printPlaneHeader(int width)
{
    std::cout << std::left << std::setw(5) << "Row#";
    char ch = 'A';
    for (int i = 0; i < width; ++i)
    {
        std::cout << ch++;
    }
    std::cout << std::endl;
}