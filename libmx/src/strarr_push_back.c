#include "../inc/libmx.h"

void strarr_push_back(char ***arr, char *value, int size) {
    if((*arr) == NULL || size == 0) {
        (*arr) = malloc(sizeof(char*) * 2);
        (*arr)[0] = mx_strdup(value);
        (*arr)[1] = NULL; 
    }
    else {
        char **new_arr = malloc(sizeof(char*) * (size + 2));
        for(int i = 0; i < size; i++) new_arr[i] = mx_strdup((*arr)[i]);
        new_arr[size] = mx_strdup(value);
        new_arr[size + 1] = NULL;
        mx_del_strarr(arr);
        (*arr) = new_arr; 
    }
}
