#include "../inc/libmx.h"

bool is_in_arr(int *arr, int el, int size) {
    if(arr) {
        for(int i = 0; i < size; i++) {
            if(arr[i] == el)
                return true;
        }
    }
    return false;
}
