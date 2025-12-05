#ifndef QUERIES_H
#define QUERIES_H

#include "managers/airport_manager.h"
#include "managers/flight_manager.h"
#include "managers/aircraft_manager.h"

void execute_query1(const char* airport_code, AirportManager* am, FILE* output);
void execute_query2(int N, const char* manufacturer, FlightManager* fm, AircraftManager* acm, FILE* output);
void execute_query3(const char* start_date, const char* end_date, FlightManager* fm, AirportManager* am, FILE* output);

#endif