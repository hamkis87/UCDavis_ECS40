#include <iostream>
#include <iomanip>
#include "plane.h"

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
        std::getline(ss, r);
        rs << r;
        rs >> std::ws;
        std::getline(rs, p);
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
    plane->passengers[row][seat] = new char[passenger.length() + 1];
    for (int i = 0; i < passenger.length(); i++)
        plane->passengers[row][seat][i] = passenger.at(i);
    plane->passengers[row][seat][passenger.length()] = '\0';
}

bool putPlaneInfo(std::ofstream &outputFileStream, Plane *plane)
{
    outputFileStream << std::endl
                     << plane->rows << " ";
    outputFileStream << plane->width << " ";
    outputFileStream << plane->reserved;
    for (int i = 0; i < plane->rows; ++i)
    {
        for (int j = 0; j < plane->width; ++j)
        {
            if (plane->passengers[i][j] != nullptr)
            {
                char seat = 'A' + j;
                outputFileStream << std::endl
                                 << i + 1 << seat << " ";
                outputFileStream << plane->passengers[i][j];
            }
        }
    }
    return true;
}

bool isFullyReserved(Plane *plane)
{
    return plane->reserved == plane->rows * plane->width;
}

bool isValidRow(Plane *plane, int row)
{
    return ((0 < row) && (row <= plane->rows));
}

bool hasVacantSeat(Plane *plane, int row)
{
    for (int i = 0; i < plane->width; ++i)
    {
        if (plane->passengers[row - 1][i] == nullptr)
        {
            return true;
        }
    }
    return false;
}

bool isValidSeatLetter(Plane *plane, int row, char letter)
{
    int letterAsInt = letter - 'A';
    return (0 <= letterAsInt) && (letterAsInt < plane->width);
}

bool isVacantSeat(Plane *plane, int row, char letter)
{
    int letterAsInt = letter - 'A';
    return (plane->passengers[row - 1][letterAsInt] == nullptr);
}

bool reserveSeat(Plane *plane, int *row, char *letter)
{
    *row = getRow();
    if (!isValidRow(plane, *row))
    {
        std::cout << "There is no row #" << *row << " on this flight.";
    }
    else if (!hasVacantSeat(plane, *row))
    {
        std::cout << "Row #" << *row << " is full!";
    }
    else
    {
        std::cout << "Please enter the seat letter you wish";
        std::cout << " to reserve on row #" << *row << ": ";
        *letter = getSeatLetter();
        if (!isValidSeatLetter(plane, *row, *letter))
        {
            std::cout << "Input letter does not exist";
        }
        else if (!isVacantSeat(plane, *row, *letter))
        {
            std::cout << "That seat is already occupied.";
        }
        else
        {
            std::cout << std::endl;
            return true;
        }
    }
    std::cout << std::endl;
    std::cout << "Please try again." << std::endl
              << std::endl;
    return false;
}

void deallocatePlane(Plane *plane)
{
    char ***passengers = plane->passengers;
    for (int i = 0; i < plane->rows; ++i)
    {
        for (int j = 0; j < plane->width; ++j)
        {
            // if (passengers[i][j] != nullptr)
            //{
            delete[] passengers[i][j];
            //}
        }
        delete[] passengers[i];
    }
    delete[] passengers;
    delete plane;
}