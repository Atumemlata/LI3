#ifndef FLIGHT_H
#define FLIGHT_H

#include "../../include/comuns.h"

typedef struct {
    char* flight_id;
    char* departure;
    char* actual_departure;
    char* arrival;
    char* actual_arrival;
    char* gate;
    char* status;
    char* origin;
    char* destination;
    char* aircraft;
    char* airline;
    char* tracking_url;
} Flight;

Flight* create_flight(const char* csv_line, FILE* error_file);
void free_flight(Flight* flight);

#endif