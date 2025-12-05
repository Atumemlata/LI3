#include "../../include/entidades/aircraft.h"
#include "../../include/parser/csv_parser.h"

Aircraft* create_aircraft(const char* csv_line, FILE* error_file) {
    if (!csv_line) return NULL;
    
    int num_fields;
    char** fields = parse_csv_line(csv_line, &num_fields);
    if (!fields || num_fields < 6) {
        if (error_file) fprintf(error_file, "%s\n", csv_line);
        if (fields) free_csv_fields(fields, num_fields);
        return NULL;
    }
    
    Aircraft* aircraft = malloc(sizeof(Aircraft));
    if (!aircraft) {
        free_csv_fields(fields, num_fields);
        return NULL;
    }
    
    aircraft->identifier = strdup(fields[0]);
    aircraft->manufacturer = strdup(fields[1]);
    aircraft->model = strdup(fields[2]);
    aircraft->year = atoi(fields[3]);
    aircraft->capacity = atoi(fields[4]);
    aircraft->range_km = atoi(fields[5]);
    
    free_csv_fields(fields, num_fields);
    return aircraft;
}

void free_aircraft(Aircraft* aircraft) {
    if (!aircraft) return;
    
    free(aircraft->identifier);
    free(aircraft->manufacturer);
    free(aircraft->model);
    free(aircraft);
}