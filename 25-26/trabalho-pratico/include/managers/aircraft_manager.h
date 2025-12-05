#ifndef AIRCRAFT_MANAGER_H
#define AIRCRAFT_MANAGER_H

#include "entidades/aircraft.h"
#include "data_structures/list.h"

typedef struct {
    List* aircrafts;
    int valid_count;
    int error_count;
} AircraftManager;

AircraftManager* create_aircraft_manager();
void load_aircrafts_from_csv(AircraftManager* manager, const char* filename);
Aircraft* find_aircraft_by_id(AircraftManager* manager, const char* aircraft_id);
void free_aircraft_manager(AircraftManager* manager);

#endif