#include <vector>
using namespace std;

vector<int> target_pattern;		//存放目标九宫格
vector<vector<int>> path;		//存放路径
vector<vector<int>> lookuptable; //存放曾经查找过的pattern
