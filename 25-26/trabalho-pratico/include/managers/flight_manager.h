#ifndef FLIGHT_MANAGER_H
#define FLIGHT_MANAGER_H

#include "entidades/flight.h"
#include "data_structures/list.h"

typedef struct {
    List* flights;
    int valid_count;
    int error_count;
} FlightManager;

FlightManager* create_flight_manager();
void load_flights_from_csv(FlightManager* manager, const char* filename);
Flight* find_flight_by_id(FlightManager* manager, const char* flight_id);
void free_flight_manager(FlightManager* manager);

#endif