#include "../inc/libmx.h"

void arr_pop_index(int **arr, int index, int size) {
    if(index >= size) return;
    if(size == 1) {
        free(*arr);
        (*arr) = NULL;
        return;
    }
    int *new_arr = malloc(sizeof(int) * (size - 1));
    for(int i = 0, k = 0; i < size; i++) {
        if(i == index) continue;
        new_arr[k] = (*arr)[i]; 
        k++;
    }
    free((*arr));
    (*arr) = new_arr;
}
