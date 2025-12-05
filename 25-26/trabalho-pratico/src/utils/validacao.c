#include "../../include/utils/validacao.h"
#include <string.h>
#include <regex.h>

bool validate_date(const char* date) {
    if (!date || strlen(date) != 10) return false;
    if (date[4] != '-' || date[7] != '-') return false;
    
    for (int i = 0; i < 10; i++) {
        if (i != 4 && i != 7 && !isdigit(date[i])) return false;
    }
    
    int year = atoi(date);
    int month = atoi(date + 5);
    int day = atoi(date + 8);
    
    return (year >= 1900 && year <= 2025) &&
           (month >= 1 && month <= 12) &&
           (day >= 1 && day <= 31);
}

bool validate_datetime(const char* datetime) {
    if (!datetime || strlen(datetime) < 16) return false;
    
    // Extrair parte da data
    char date_part[11];
    strncpy(date_part, datetime, 10);
    date_part[10] = '\0';
    
    if (!validate_date(date_part)) return false;
    
    // Verificar formato da hora
    if (datetime[10] != ' ' || datetime[13] != ':') return false;
    
    int hour = atoi(datetime + 11);
    int minute = atoi(datetime + 14);
    
    return (hour >= 0 && hour <= 23) && (minute >= 0 && minute <= 59);
}

bool validate_airport_code(const char* code) {
    if (!code || strlen(code) != 3) return false;
    
    for (int i = 0; i < 3; i++) {
        if (!isupper(code[i])) return false;
    }
    return true;
}

bool validate_flight_id(const char* flight_id) {
    if (!flight_id || strlen(flight_id) < 2) return false;
    
    // Verificar primeiros 2 caracteres são letras
    if (!isalpha(flight_id[0]) || !isalpha(flight_id[1])) return false;
    
    // Resto devem ser dígitos
    for (size_t i = 2; i < strlen(flight_id); i++) {
        if (!isdigit(flight_id[i])) return false;
    }
    
    return true;
}

bool validate_reservation_id(const char* res_id) {
    if (!res_id || strlen(res_id) != 10) return false;
    if (res_id[0] != 'R') return false;
    
    for (int i = 1; i < 10; i++) {
        if (!isdigit(res_id[i])) return false;
    }
    return true;
}

bool validate_document_number(const char* doc) {
    if (!doc || strlen(doc) != 9) return false;
    
    for (int i = 0; i < 9; i++) {
        if (!isdigit(doc[i])) return false;
    }
    return true;
}

bool validate_gender(const char* gender) {
    return gender && (strcmp(gender, "M") == 0 || 
                     strcmp(gender, "F") == 0 || 
                     strcmp(gender, "O") == 0);
}

bool validate_latitude(double lat) {
    return lat >= -90.0 && lat <= 90.0;
}

bool validate_longitude(double lon) {
    return lon >= -180.0 && lon <= 180.0;
}

bool validate_airport_type(const char* type) {
    return type && (strcmp(type, "small_airport") == 0 ||
                   strcmp(type, "medium_airport") == 0 ||
                   strcmp(type, "large_airport") == 0 ||
                   strcmp(type, "heliport") == 0 ||
                   strcmp(type, "seaplane_base") == 0);
}

bool validate_email(const char* email) {
    if (!email) return false;
    
    // Verificação básica
    char* at = strchr(email, '@');
    if (!at) return false;
    
    char* dot = strchr(at, '.');
    if (!dot) return false;
    
    return true;
}