#ifndef S21_GRAPH_C
#define S21_GRAPH_C

#include "s21_graph.h"

void print(s21_graph * g) {
    printf("size graph %02d\n", g -> size);
    if (g -> matrix == NULL) {
        printf("ERROR\n");
    }
    else {
        for (int i = 0; i < g -> size; i++) {
            for (int j = 0; j < g -> size; j++)
            {
                printf(" %2d", g -> matrix[i][j]);
            }
            printf("\n");
        }
    }
}

int ** calloc_matrix(int size) {
    int ** result;
    if (size < 1)
        perror(_ERR_SIZE);
    else {
        result = (int ** ) calloc(size, sizeof(int * ));
        if (!result) {
            perror(_ERR_CALLOC);
        }
        else {
            for (int i = 0; i < size; i++) {
                result[i] = (int * ) calloc(size, sizeof(int));
                if (!result[i]) {
                    while (i--) free(result[i]);
                    free(result);
                    perror(_ERR_CALLOC);
                }
            }
        }
    }
    return result;
}

void remove_graph(s21_graph * g) {
    if (g -> matrix != NULL) {
        for (int i = 0; i < g -> size; i++) free(g -> matrix[i]);
        free(g -> matrix);
        g -> matrix = NULL;
        g -> size = 0;
    }
}

static void read_graph_el(FILE * f, s21_graph * graph) {
    if (graph->matrix != NULL) {
        for (int i = 0; i < graph -> size; i++) {
            for (int j = 0; j < graph -> size; j++) {
                int el = 0;
                if (1 != fscanf(stdin, "%d", & el)) {
                    remove_graph( & graph);
                    perror(_ERR_READ_GRAPH);
                }
                else {
                    graph->matrix[i][j] = el;
                }
            }
        }
    }
    else {
        perror(_ERR_CREATE_GRAPH);
    }
}

s21_graph load_graph_from_file(char * filename) {
    s21_graph graph;
    FILE * f = fopen(filename, "r");
    if (f == NULL) {
        //perror(_ERR_OPEN);
    }
    else {
        int size_graph = 0;
        if (1 != fscanf(stdin, "%d", & size_graph)) {
            perror(_ERR_READ_SIZE);
        }
        else {
            graph.size = size_graph;
            graph.matrix = calloc_matrix(size_graph);
            read_graph_el(f, &graph);
        }
    }
    return graph;
    fclose(f);
}

/*
s21_graph export_graph_to_dot(char *filename) {

}
*/

#endif
