#include "../inc/libmx.h"

void strarr_pop_back(char ***arr, int size) {
    if(size == 1) {
        mx_del_strarr(arr);
        return;
    }
    char **new_arr = malloc(sizeof(char*) * (size));
    for(int i = 0; i < size - 1; i++) {
        new_arr[i] = mx_strdup((*arr)[i]);
    }
    new_arr[size - 1] = NULL;
    mx_del_strarr(arr);
    (*arr) = new_arr;
}
