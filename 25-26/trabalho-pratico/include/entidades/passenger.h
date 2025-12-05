#ifndef PASSENGER_H
#define PASSENGER_H

#include "../../include/comuns.h"

typedef struct {
    char* document_number;
    char* first_name;
    char* last_name;
    char* dob;
    char* nationality;
    char* gender;
    char* email;
    char* phone;
    char* address;
    char* photo;
} Passenger;

Passenger* create_passenger(const char* csv_line, FILE* error_file);
void free_passenger(Passenger* passenger);

#endif