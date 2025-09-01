#include <stdio.h>
#include "s21_graph.h"

int main(){
s21_graph g = graph_init();
g.load_graph_from_file("test/test_file/t_1_load.txt", &g);
printf("size graph %d\n", g.size);
g.print_graph(&g);
g.del_graph(&g);
printf("size graph %d\n", g.size);
//printf("elem %d\n", g.matrix[0][0]);
return 0;

}

