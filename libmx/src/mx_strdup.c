#include "../inc/libmx.h"

char *mx_strdup(const char *s1){
    if (!s1) return NULL;
    char* copy = mx_strnew(mx_strlen(s1));
    mx_strcpy(copy, s1);
    return copy;
}

