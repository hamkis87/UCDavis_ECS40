#ifndef UTILITIES_H
#define UTILITIES_H

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string.h>

int getNumberOfFlights(std::ifstream &inputFileStream);
void printMenuHeader();
void mapRowSeat(std::string const &rowSeat, int &row, int &seat);
int getFirstUserInput();
int getNumber(std::string line);
char getSeatLetter();
int getRow();
void printPlaneHeader(int width);
std::string getPassengerName();

#endif