#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include "../../include/comuns.h"

typedef struct {
    char* identifier;
    char* manufacturer;
    char* model;
    int year;
    int capacity;
    int range_km;
} Aircraft;

Aircraft* create_aircraft(const char* csv_line, FILE* error_file);
void free_aircraft(Aircraft* aircraft);

#endif