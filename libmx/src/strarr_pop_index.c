#include "../inc/libmx.h"

void strarr_pop_index(char ***arr, int index, int size) {
    if(index >= size) return;
    if(size == 1) {
        mx_del_strarr(arr);
        return;
    }
    char **new_arr = malloc(sizeof(char*) * size);
    for(int i = 0, k = 0; i < size; i++) {
        if(i == index) continue;
        new_arr[k] = mx_strdup((*arr)[i]); 
        k++;
    }
    new_arr[size - 1] = NULL;
    mx_del_strarr(arr);
    (*arr) = new_arr;
}
