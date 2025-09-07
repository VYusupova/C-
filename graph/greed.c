tsm_result *greedy_tsp(graph *g) {
  if (!g || g->size < 2) return NULL;
  tsm_result *res = calloc_tsm(res, g->size); 
  int *visited = calloc(g->size, sizeof(int));
  int current = 0;
  res->vertices[0] = 1;  // Стартовая вершина: Фиксирована (вершина 1 в коде).
  visited[0] = 1;
  for (int i = 1; i < g->size; i++) {
    int next = -1;
    int min_dist = INT_MAX;
    for (int j = 0; j < g->size; j++) {
      int edge =  g->matrix[current][j];
      if (!visited[j] && edge > 0 && edge < min_dist) {
        min_dist = edge;
        next = j;
      }
    }
    if (next == -1) {
      free(res);
      break;
    }
    res->vertices[i] = next + 1;
    res->distance += min_dist;
    visited[next] = 1;
    current = next;
  }
  if (res) {
    // проверяем существует ли обратное ребро
    if (g->matrix[current][0] <= 0) {
    free(res);
    } else {
      res->vertices[g->size] = 1;
      res->distance += g->matrix[current][0];
    }
  }
  free(visited);
  return res;
}

int not_visit_and_min(int node){
 return
   }

static void free_tsm(tsm_result *t){
      free(res->vertices);
      free(res);
      res = NULL;
}

static tsm_result * calloc_tsm(tsm_result *t, int size){
  tsm_result *tsm = malloc(sizeof(tsm_result));
  tsm->vertices = malloc((size + 1) * sizeof(int));
  tsm->distance = 0;
  return tsm;
}
