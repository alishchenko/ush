#include "../inc/libmx.h"

void arr_push_back(int **arr, int value, int size) {
    if((*arr) == NULL || size == 0) {
        (*arr) = malloc(sizeof(int) * 1);
        (*arr)[0] = value;
    }
    else {
        *arr = realloc(*arr, size + 1);
        (*arr)[size] = value;
    }
}
