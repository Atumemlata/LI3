#include "../../include/entidades/passenger.h"
#include "../../include/parser/csv_parser.h"

Passenger* create_passenger(const char* csv_line, FILE* error_file) {
    if (!csv_line) return NULL;
    
    int num_fields;
    char** fields = parse_csv_line(csv_line, &num_fields);
    if (!fields || num_fields < 10) {
        if (error_file) fprintf(error_file, "%s\n", csv_line);
        if (fields) free_csv_fields(fields, num_fields);
        return NULL;
    }
    
    Passenger* passenger = malloc(sizeof(Passenger));
    if (!passenger) {
        free_csv_fields(fields, num_fields);
        return NULL;
    }
    
    passenger->document_number = strdup(fields[0]);
    passenger->first_name = strdup(fields[1]);
    passenger->last_name = strdup(fields[2]);
    passenger->dob = strdup(fields[3]);
    passenger->nationality = strdup(fields[4]);
    passenger->gender = strdup(fields[5]);
    passenger->email = strdup(fields[6]);
    passenger->phone = strdup(fields[7]);
    passenger->address = strdup(fields[8]);
    passenger->photo = strdup(fields[9]);
    
    free_csv_fields(fields, num_fields);
    return passenger;
}

void free_passenger(Passenger* passenger) {
    if (!passenger) return;
    
    free(passenger->document_number);
    free(passenger->first_name);
    free(passenger->last_name);
    free(passenger->dob);
    free(passenger->nationality);
    free(passenger->gender);
    free(passenger->email);
    free(passenger->phone);
    free(passenger->address);
    free(passenger->photo);
    free(passenger);
}