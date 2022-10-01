#include <iostream>
#include <stack>
#include <vector>
#include <String>
#include "globle_var.h"
#include "generate_pattern.h"
#include "print_pattern.h"
#include "BFS.h"
#include "move_to.h"

using namespace std;

/*
* 思路：
* 遍历二维数组的下一层
* 有两个for循环
* for(upper_layer的节点){
*	for(upper_layer节点的子节点){
*		判断是不是要匹配的pattern，是的话就返回，不是的话就下一步
*		if(子节点在lookuptable里面)	不用去检查
*		else(子节点不在lookuptable里面)
*			去hash，把子节点添加到lookuptable里面
*			将该子节点添加到lower_layer
*	}
* }
* 先去hash，如果hash里面没有的话添加到hash里面然后去判断符不符合要匹配的pattern
* 如果有的话就不用去检查该pattern，转到下一个pattern去检查
*
*/

void printPath() {
	//for (int i = 0; i < path.size(); i++) {
	//	path.pop();
	//	cout << " ";
	//	if (i % 3 == 0)	cout << endl;
	//	if (i % 9 == 0) cout << endl;
	//}
	for (int i = 0; i < path.size(); i++) {
		for (int j = 1; j <=path[i].size(); j++) {
			if (path[i][j - 1] == 0) {
				cout << "  ";
			}
			else {
				cout << path[i][j - 1] << " ";
			}
			if (j % 3 == 0)	cout << endl;
		}
		cout << endl;
	}
}

int main() {
	vector<int> pattern;
	generate_pattern(pattern, target_pattern);	//generate original pattern and target pattern
	print_pattern(pattern);
	print_pattern(target_pattern);

	vector<vector<int>> upper_layer;
	upper_layer.push_back(pattern);
	lookuptable.push_back(pattern);
	vector<int> temp2 = bfs(upper_layer);

	if (temp2.size() == 0) {
		cout << "未找到路径！！" << endl;
	}
	else {
		path.push_back(pattern);
		printPath();
	}
	return 0;
}
