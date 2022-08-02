#ifndef FLIGHT_H
#define FLIGHT_H
#include "plane.h"

typedef struct
{
    int flightNum;
    char origin[20];
    char destination[20];
    Plane *plane;
} Flight;

#endif