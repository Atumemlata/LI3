#include "../../include/entidades/flight.h"
#include "../../include/utils/validacao.h"
#include "../../include/parser/csv_parser.h"

Flight* create_flight(const char* csv_line, FILE* error_file) {
    if (!csv_line) return NULL;
    
    int num_fields;
    char** fields = parse_csv_line(csv_line, &num_fields);
    if (!fields || num_fields < 12) {
        if (error_file) fprintf(error_file, "%s\n", csv_line);
        if (fields) free_csv_fields(fields, num_fields);
        return NULL;
    }
    
    // Validações básicas
    if (!validate_flight_id(fields[0]) ||
        !validate_airport_code(fields[7]) ||
        !validate_airport_code(fields[8])) {
        if (error_file) fprintf(error_file, "%s\n", csv_line);
        free_csv_fields(fields, num_fields);
        return NULL;
    }
    
    Flight* flight = malloc(sizeof(Flight));
    if (!flight) {
        free_csv_fields(fields, num_fields);
        return NULL;
    }
    
    flight->flight_id = strdup(fields[0]);
    flight->departure = strdup(fields[1]);
    flight->actual_departure = strdup(fields[2]);
    flight->arrival = strdup(fields[3]);
    flight->actual_arrival = strdup(fields[4]);
    flight->gate = strdup(fields[5]);
    flight->status = strdup(fields[6]);
    flight->origin = strdup(fields[7]);
    flight->destination = strdup(fields[8]);
    flight->aircraft = strdup(fields[9]);
    flight->airline = strdup(fields[10]);
    flight->tracking_url = strdup(fields[11]);
    
    free_csv_fields(fields, num_fields);
    return flight;
}

void free_flight(Flight* flight) {
    if (!flight) return;
    
    free(flight->flight_id);
    free(flight->departure);
    free(flight->actual_departure);
    free(flight->arrival);
    free(flight->actual_arrival);
    free(flight->gate);
    free(flight->status);
    free(flight->origin);
    free(flight->destination);
    free(flight->aircraft);
    free(flight->airline);
    free(flight->tracking_url);
    free(flight);
}