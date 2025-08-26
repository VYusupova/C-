#include <stdio.h>

#define _ERR_OPEN = "ошибка открытия файла"
#define _ERR_READ_SIZE = "ошибка чтения из файла размера графа"
#define _ERR_READ_GRAPH = "ошибка чтения из файла значений графаф"
#define _ERR_CREATE_GRAPH = "ошибка выделения памяти под граф"

// общедоступный метод

void read_graph_el(FILE *f,  matrix_t *graph){
    for (int i = 0; i < graph->row; i++)
            for (int j = 0; j < graph->row; j++)
                if (1 != fscanf(f, "%d", &graph[i][j]))
                { // если будет ошибка чтения освободить память вернуть ошибку 
                     s21_remove_matrix(graph);
                     perror(_ERR_READ_GRAPH);
                     return NULL;
                }
}

matrix_t * load_graph_from_file(char * filename) {
    
    FILE f = open(filename, "r");
    if (f == NULL)
    {
        perror(_ERR_OPEN);
        return NULL;
    }
    int size_graph = 0;
    if (1 != fscanf(f, "%d", & size_graph))
    {
        perror(_ERR_READ_SIZE);
        return NULL;
    }
    matrix_t graph = NULL;
    if (OK_MATRIX == s21_create_matrix(size_graph, size_graph, graph))
    {
            read_graph_el(f, graph);
    }
    else  {
        perror(_ERR_CREATE_GRAPH);
    }

    return graph;
    fclose(f);
}




export_graph_to_dot(char * filename);

