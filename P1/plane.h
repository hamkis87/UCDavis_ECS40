#ifndef PLANE_H
#define PLANE_H
#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>
#include "utilities.h"

typedef struct
{
    int rows;
    int width;
    int reserved;
    char ***passengers; // 2-dimensional
} Plane;

bool reserveSeat(Plane *plane, int *row, char *letter);
bool isFullyReserved(Plane *plane);
void printPassengers(Plane *plane);
bool putPlaneInfo(std::ofstream &outputFileStream, Plane *plane);
void addPassenger(Plane *plane, std::string rowSeat, std::string passenger);
void initializePassengers(Plane *plane);
bool getPlaneInfo(std::ifstream &inputFileStream, Plane *plane);
bool isValidRow(Plane *plane, int row);
bool hasVacantSeat(Plane *plane, int row);
bool isValidSeatLetter(Plane *plane, int row, char letter);
bool isVacantSeat(Plane *plane, int row, char letter);

#endif