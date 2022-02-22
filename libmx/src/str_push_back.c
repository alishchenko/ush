#include "../inc/libmx.h"

void str_push_back(char **str, char value, int size) {
    if((*str) == NULL || size == 0) {
        (*str) = mx_strnew(size + 1);
        (*str)[0] = value; 
    }
    else {
        char *new_str = mx_strnew(size + 1);
        for(int i = 0; i < size; i++) new_str[i] = (*str)[i];
        new_str[size] = value;
        mx_strdel(str);
        (*str) = new_str; 
    }
}
