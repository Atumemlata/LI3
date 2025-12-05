#ifndef AIRPORT_MANAGER_H
#define AIRPORT_MANAGER_H

#include "entidades/airport.h"
#include "data_structures/list.h"

typedef struct {
    List* airports;
    int valid_count;
    int error_count;
} AirportManager;

AirportManager* create_airport_manager();
void load_airports_from_csv(AirportManager* manager, const char* filename);
Airport* find_airport_by_code(AirportManager* manager, const char* code);
void free_airport_manager(AirportManager* manager);

#endif