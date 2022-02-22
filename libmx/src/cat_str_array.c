#include "../inc/libmx.h"

char *cat_str_array(char **array, char *delim) {
    size_t len = 0;
    char * string;
    for (int i = 0; array[i] != NULL; ++i)
        len += mx_strlen(array[i] + (array[i + 1] != NULL ? mx_strlen(delim) : 0));
    
    string = malloc(len + 1);
    if(string) {
        *string = '\0';
        for (int i = 0; array[i] != NULL; ++i) {
            mx_strcat(string, array[i]);
            if(array[i + 1] != NULL) mx_strcat(string, delim);
        }
    }
    return string;
}
