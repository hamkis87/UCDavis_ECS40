#include "utilities.h"

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

int getNumber(std::string line)
{
    std::stringstream stringStream(line);
    int number;
    char c;
    if (stringStream >> number && !(stringStream >> c))
        return number;
    return -1;
}

char getSeatLetter()
{
    std::string line;
    std::stringstream stringStream;
    char letter, remaining;
    if (getline(std::cin, line) && (stringStream << line) && (stringStream >> letter) && !(stringStream >> remaining))
    {
        return letter;
    }
    return 'a';
}

int getRow()
{
    std::cout << "Please enter the row of the seat you wish to reserve: ";
    std::string rowStr;
    std::getline(std::cin, rowStr);
    return getNumber(rowStr);
}

std::string getPassengerName()
{
    std::string passengerName;
    std::cout << "Please enter the name of the passenger: ";
    std::getline(std::cin, passengerName);
    return passengerName;
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