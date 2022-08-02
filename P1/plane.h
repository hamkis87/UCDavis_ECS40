#ifndef PLANE_H
#define PLANE_H

typedef struct
{
    int rows;
    int width;
    int reserved;
    char ***passengers; // 2-dimensional
} Plane;

#endif