#include "../../include/entidades/reservation.h"
#include "../../include/utils/validacao.h"
#include "../../include/parser/csv_parser.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Função auxiliar para parse de lista de flight_ids
char** parse_flight_ids(const char* flight_ids_str, int* count) {
    if (!flight_ids_str || strlen(flight_ids_str) < 2) return NULL;
    
    // Verificar se começa com [ e termina com ]
    if (flight_ids_str[0] != '[' || flight_ids_str[strlen(flight_ids_str)-1] != ']') {
        return NULL;
    }
    
    // Remover os []
    char* clean_str = malloc(strlen(flight_ids_str) - 1);
    if (!clean_str) return NULL;
    strncpy(clean_str, flight_ids_str + 1, strlen(flight_ids_str) - 2);
    clean_str[strlen(flight_ids_str) - 2] = '\0';
    
    // Contar vírgulas para saber quantos flights
    *count = 1;
    for (char* p = clean_str; *p; p++) {
        if (*p == ',') (*count)++;
    }
    
    // Alocar array para flight_ids
    char** flight_ids = malloc(*count * sizeof(char*));
    if (!flight_ids) {
        free(clean_str);
        return NULL;
    }
    
    // Parse dos IDs individuais
    char* token = strtok(clean_str, ",");
    int i = 0;
    while (token && i < *count) {
        // Remover espaços em branco
        while (*token == ' ') token++;
        char* end = token + strlen(token) - 1;
        while (end > token && *end == ' ') end--;
        *(end + 1) = '\0';
        
        flight_ids[i] = malloc(strlen(token) + 1);
        strcpy(flight_ids[i], token);
        i++;
        token = strtok(NULL, ",");
    }
    
    free(clean_str);
    return flight_ids;
}

Reservation* create_reservation(const char* csv_line, FILE* error_file) {
    if (!csv_line) return NULL;
    
    int num_fields;
    char** fields = parse_csv_line(csv_line, &num_fields);
    if (!fields || num_fields < 8) {
        if (error_file) fprintf(error_file, "%s\n", csv_line);
        if (fields) free_csv_fields(fields, num_fields);
        return NULL;
    }
    
    // Validações básicas
    if (!validate_reservation_id(fields[0]) ||
        !validate_document_number(fields[2])) {
        if (error_file) fprintf(error_file, "%s\n", csv_line);
        free_csv_fields(fields, num_fields);
        return NULL;
    }
    
    // Parse da lista de flight_ids
    int flight_count;
    char** flight_ids = parse_flight_ids(fields[1], &flight_count);
    if (!flight_ids || flight_count == 0 || flight_count > 2) {
        if (error_file) fprintf(error_file, "%s\n", csv_line);
        free_csv_fields(fields, num_fields);
        if (flight_ids) {
            for (int i = 0; i < flight_count; i++) free(flight_ids[i]);
            free(flight_ids);
        }
        return NULL;
    }
    
    // Validar cada flight_id individualmente
    for (int i = 0; i < flight_count; i++) {
        if (!validate_flight_id(flight_ids[i])) {
            if (error_file) fprintf(error_file, "%s\n", csv_line);
            free_csv_fields(fields, num_fields);
            for (int j = 0; j < flight_count; j++) free(flight_ids[j]);
            free(flight_ids);
            return NULL;
        }
    }
    
    Reservation* reservation = malloc(sizeof(Reservation));
    if (!reservation) {
        free_csv_fields(fields, num_fields);
        for (int i = 0; i < flight_count; i++) free(flight_ids[i]);
        free(flight_ids);
        return NULL;
    }
    
    // Preencher a estrutura
    reservation->reservation_id = malloc(strlen(fields[0]) + 1);
    strcpy(reservation->reservation_id, fields[0]);
    
    reservation->flight_ids = flight_ids;
    reservation->flight_count = flight_count;
    
    reservation->document_number = malloc(strlen(fields[2]) + 1);
    strcpy(reservation->document_number, fields[2]);
    
    reservation->seat = malloc(strlen(fields[3]) + 1);
    strcpy(reservation->seat, fields[3]);
    
    reservation->price = atof(fields[4]);
    
    // Converter booleanos
    reservation->extra_luggage = (strcmp(fields[5], "true") == 0);
    reservation->priority_boarding = (strcmp(fields[6], "true") == 0);
    
    reservation->qr_code = malloc(strlen(fields[7]) + 1);
    strcpy(reservation->qr_code, fields[7]);
    
    free_csv_fields(fields, num_fields);
    return reservation;
}

void free_reservation(Reservation* reservation) {
    if (!reservation) return;
    
    free(reservation->reservation_id);
    
    // Libertar array de flight_ids
    if (reservation->flight_ids) {
        for (int i = 0; i < reservation->flight_count; i++) {
            free(reservation->flight_ids[i]);
        }
        free(reservation->flight_ids);
    }
    
    free(reservation->document_number);
    free(reservation->seat);
    free(reservation->qr_code);
    free(reservation);
}