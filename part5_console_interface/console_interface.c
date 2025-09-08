#include "console_define.h"

static void question_print(graph *g) {
  PRINT_QUESTION;
  int user_input;
  scanf("%d", &user_input);
  switch (user_input) {
  case 1:
    print_matrix(g);
    break;
  case 2:
    print_dot(g);
    break;
  default:
    ERR_INPUT;
    break;
  }
}

static graph load_grap() {
  PRINT_LOAD_GRAP;
  graph g = graph_init();
  char filename[100];
  int c = scanf("%s", filename);
  printf("\n");
  if (1 == c) {
     printf("start load\n");
    
    g = g.load_graph_from_file(filename);
    printf("size : %d\n", g.size);
    if (g.size == 0){
      ERR_PRINT_LOAD_GRAP;
      
      }
    else{
      question_print(&g);
      }
  } else{
    ERR;}
    return g;

}

static void export_infile_dot(graph *g) {
  PRINT_OUT_GRAP;
  char filename[256];
  int c = scanf("%s", filename);
  printf("\n");
  if (1 == c) {
    if (g->size == 0)
      ERR_PRINT_LOAD_GRAP;
    else
      g->export_graph_to_dot(filename, g);
  } else
    ERR;
}

static void print_DFS(graph *g) {
  int *visit;
  if (g->size == 0)
    ERR_GRAF_EMPTY;
  else {
    printf("введите чиcло от 0 до %d вершину с которой надо начать обход :",
           g->size);
    int vertex = 0;
    if (1 != scanf("%d", &vertex))
      ERR_INPUT_DOT;
    else {
      if (vertex > g->size || vertex < 0)
        ERR_INPUT_DOT;
      else
        visit = depth_first_search(g, vertex);
    }
    printf("обход графа { ");
    for (int i = 0; i < g->size; i++)
      printf("%d  ", visit[i]);
    printf(" }\n");
  }
}

static void print_Dijkstra(graph *g) {
  int short_path = 0;
  if (g->size == 0)
    ERR_GRAF_EMPTY;
  else {
    printf(
        "введите pair vertex от 0 до %d вершину с которой надо начать обход :",
        g->size);
    int start = 0;
    int end = g->size;
    if (2 != scanf("%d %d", &start, &end))
      ERR_INPUT_DOT;
    else {
      if (start > g->size || start < 0 || end > g->size || end < 0)
        ERR_INPUT_DOT;
      else {
        short_path = get_shortest_path_between_vertices(g, start, end);
      }
    }
    printf("shortest way is %d \n", short_path);
  }
}

static void out_matrix(int size, int **m){
	for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      printf(" %2d", m[i][j]);
    }
    printf("\n");
  }
}

static void print_Floyd(graph *g) {
  int **short_dist = 0;
  if (g->size == 0)
    ERR_GRAF_EMPTY;
  else {
    short_dist = get_shortest_paths_between_all_vertices(g);
  }
  printf("\t\tshortest dist \n");
  out_matrix(g->size, short_dist);
}

static void print_least_spanning_tree(graph *g){
    printf("мин. остов. дерев результ. матр. смежности :\n");
    int **mst = get_least_spanning_tree(g);
    if (mst != NULL ) {
     out_matrix(g->size, mst);
	for(int i = 0; i<g->size; i++)
		free(mst[i]);
	free(mst);
    }
    else printf("not valid graph from PRIM\n");
    
}

static void analitic_solve_traviling(graph *g){
    if (g->size > 1) {
    tsm_result *t = greedy_tsp(g);
    printf("solve traveling = { ");
    for (int i = 0; i < g->size; i++)
    	printf("%d ", t->vertices[i]);
    printf(" } distance = %f\n", t->distance);
    }
    else {
        printf("not valid graph from solve traveling\n");
    }

}

int main() {
     printf("start\n");
  graph g ;//= graph_create();
  int user_input;

  int break_flag = 0;

  while (!break_flag) {
    PRINT_CHOOSE;
    scanf("%d", &user_input);
    switch (user_input) {
    case 0:
          break_flag = 1;
          break;
    case 1:

      g = load_grap();
      break;
    case 2:

      break;
    case 3:
      print_DFS(&g);
      break;
    case 4:
      print_Dijkstra(&g);
      break;
    case 5:
      print_Floyd(&g);
      break;
    case 6:
      print_least_spanning_tree(&g);
      break;
    case 7:
      break;
    case 8:
      export_infile_dot(&g);
    case 9:
      analitic_solve_traviling(&g);
      break;
    default:
      ERR_INPUT;
      break;
    }
  }

  return 0;
}


