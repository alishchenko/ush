#include "../inc/libmx.h"

void arr_pop_back(int **arr, int size) {
    if(size == 1) {
        free(*arr);
        (*arr) = NULL;
        return;
    }
    int *new_arr = malloc(sizeof(int) * (size - 1));
    for(int i = 0; i < size - 1; i++) {
        new_arr[i] = (*arr)[i];
    }
    free((*arr));
    (*arr) = new_arr;
}
