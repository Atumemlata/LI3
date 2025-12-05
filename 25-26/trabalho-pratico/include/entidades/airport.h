#ifndef AIRPORT_H
#define AIRPORT_H

#include "../../include/comuns.h"

typedef struct {
    char* code;
    char* name;
    char* city;
    char* country;
    double latitude;
    double longitude;
    char* icao;
    char* type;
} Airport;

Airport* create_airport(const char* csv_line, FILE* error_file);
void free_airport(Airport* airport);

#endif