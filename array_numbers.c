#include <stdio.h>
#include <stdlib.h>

static int * read_arr(int * len) {
    int capacity = 10;
    int * arr = (int * ) calloc(capacity, sizeof(int));
    if (NULL == arr) return NULL;
    int a, i = 0;
    while (1 == scanf("%d", & a)) {
        if (a == -1) break;
        else {
            arr[i] = a;
            i++;
            // chek size for next element (<=)
            if (capacity <= i) {
                capacity += 5;
                unsigned size = capacity*sizeof(int);
                arr = (int*)realloc((void*)arr, size);
                if (NULL == arr) return NULL;
            }
        }
    }
    * len = i;
    return arr;
}

static void print_arr(const int * arr, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
}

int main() {


    int len = 0;
    int * arr = read_arr( & len);
    if (arr) print_arr(arr, len);
    if (arr != NULL) free(arr);

    printf("GOOD");

}
