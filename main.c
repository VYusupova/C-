#include "s21_graph.h"
void main(){
s21_graph g = graph_init();
g.load_graph_from_file("t_1_load", &g);
printf("size graph %d\n", g.size);
g.print_graph(&g);
g.del_graph(&g);
printf("size graph %d\n", g.size);
//printf("elem %d\n", g.matrix[0][0]);

}
