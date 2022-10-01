#include "globle_var.h"
#ifndef BFS_h
#define BFS_h

bool pattern_compare(vector<int> pattern);
void add_to_lower_layer(vector<vector<int>>& lower_layer, vector<int> pattern);
vector<int> bfs(vector<vector<int>> upper_layer);

#endif