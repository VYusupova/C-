#include "s21_graph.h"
void main(){
s21_graph g = graph_init();
g = load_graph_from_file("t_1_load");
//printf("element graph %d\n", g.matrix[1][1]);
//s21_graph *g1 = &g; 
g.print_graph(&g);
}
