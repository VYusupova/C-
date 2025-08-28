#include "s21_graph.h"
void main(){
s21_graph g = load_graph_from_file("t_1_load");
printf("element graph %d\n", g.matrix[1][1]);
s21_graph *g1 = &g; 
print_m(g1->row, g1->matrix);
}
