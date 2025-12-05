#ifndef RESERVATION_H
#define RESERVATION_H

#include "../../include/comuns.h"

typedef struct {
    char* reservation_id;
    char** flight_ids;
    int flight_count;
    char* document_number;
    char* seat;
    float price;
    bool extra_luggage;
    bool priority_boarding;
    char* qr_code;
} Reservation;

Reservation* create_reservation(const char* csv_line, FILE* error_file);
void free_reservation(Reservation* reservation);

#endif