#include "../../include/entidades/airport.h"
#include "../../include/utils/validacao.h"
#include "../../include/parser/csv_parser.h"

Airport* create_airport(const char* csv_line, FILE* error_file) {
    if (!csv_line) return NULL;
    
    int num_fields;
    char** fields = parse_csv_line(csv_line, &num_fields);
    if (!fields || num_fields < 8) {
        if (error_file) fprintf(error_file, "%s\n", csv_line);
        if (fields) free_csv_fields(fields, num_fields);
        return NULL;
    }
    
    // Validações
    if (!validate_airport_code(fields[0]) ||
        !validate_latitude(atof(fields[4])) ||
        !validate_longitude(atof(fields[5])) ||
        !validate_airport_type(fields[7])) {
        if (error_file) fprintf(error_file, "%s\n", csv_line);
        free_csv_fields(fields, num_fields);
        return NULL;
    }
    
    Airport* airport = malloc(sizeof(Airport));
    if (!airport) {
        free_csv_fields(fields, num_fields);
        return NULL;
    }
    
    airport->code = strdup(fields[0]);
    airport->name = strdup(fields[1]);
    airport->city = strdup(fields[2]);
    airport->country = strdup(fields[3]);
    airport->latitude = atof(fields[4]);
    airport->longitude = atof(fields[5]);
    airport->icao = strdup(fields[6]);
    airport->type = strdup(fields[7]);
    
    free_csv_fields(fields, num_fields);
    return airport;
}

void free_airport(Airport* airport) {
    if (!airport) return;
    
    free(airport->code);
    free(airport->name);
    free(airport->city);
    free(airport->country);
    free(airport->icao);
    free(airport->type);
    free(airport);
}