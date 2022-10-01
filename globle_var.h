#include <vector>

using namespace std;

#ifndef globle_var_h
#define globle_var_h

extern vector<int> target_pattern;		//存放目标九宫格
extern vector<vector<int>> path;		//存放路径
extern vector<vector<int>> lookuptable; //存放曾经查找过的pattern

#endif