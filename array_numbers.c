#include <stdio.h>

#include <stdlib.h>

#define N 100

int * read_arr(int * len) {
    int capacity = 10;
    int * arr = (int * ) calloc(capacity, sizeof(int));
    if (NULL == arr) return NULL;
    int a, i = 0;
    while (1 == scanf("%d", & a)) {
        if (a == -1) break;
        else {
            arr[i] = a;
            i++;
            if (capacity < i) {
                capacity += 5;
                int *new_arr = (int*)realloc((void*)arr, (size_t)(15*sizeof(int)));
                if (NULL == new_arr) return NULL;
                arr = new_arr;
                printf("realloc %d ", capacity);
            }
        }
    }
    * len = i;
    return arr;
}

void print_arr(int * arr, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
}

int main() {


    int len = 0;
    int * arr = read_arr( & len);
    if (arr) print_arr(arr, len);
    //if (arr != NULL) free(arr);

    printf("GOOD");

}