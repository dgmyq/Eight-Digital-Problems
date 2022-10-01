﻿#include <iostream>
#include <stack>
#include <vector>
#include <String>

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

vector<int> target_pattern;		//存放目标九宫格
vector<vector<int>> path;		//存放路径
vector<vector<int>> lookuptable; //存放曾经查找过的pattern


/*
* @pattern	移动前的九宫格
* @mode		向上、下、左、右移动
* 
* 可以移动的话就返回移动后的pattern
* 不能移动的话就返回一个空的vector<int>
*/
vector<int> move_to(vector<int> pattern,string mode) {
	int space = 0;			//存放空格的位置
	for (int i = 0; i < 9; i++) {	//查找空格的位置
		if (pattern[i] == 0) {
			space = i;
			break;
		}
	}

	vector<int> result;			//存放移动后的pattern
	if (mode.compare("up") == 0) {
		if ((space == 0) || (space == 1) || (space == 2)) {		//如果是0，1，2位置则不能向上移动
			return result;
		}
		else {
			pattern[space] = pattern[space - 3];		//其余的位置可以向上移动
			pattern[space - 3] = 0;
			result = pattern;
			return result;
		}
	}
	else if (mode.compare("down") == 0) {
		if ((space == 6) || (space == 7) || (space == 8)) {		//如果是6，7，8位置则不能向下移动
			return result;
		}
		else {
			pattern[space] = pattern[space + 3];		//其余的位置可以向下移动
			pattern[space + 3] = 0;
			result = pattern;
			return result;
		}
	}
	else if (mode.compare("left") == 0) {
		if ((space == 0) || (space == 3) || (space == 6)) {		//如果是0，3，6位置则不能向左移动
			return result;
		}
		else {
			pattern[space] = pattern[space - 1];		//其余的位置可以向左移动
			pattern[space - 1] = 0;
			result = pattern;
			return result;
		}
	}
	else if (mode.compare("right") == 0) {
		if ((space == 2) || (space == 5) || (space == 8)) {		//如果是2，5，8位置则不能向下移动
			return result;
		}
		else {
			pattern[space] = pattern[space + 1];		//其余的位置可以向右移动
			pattern[space + 1] = 0;
			result = pattern;
			return result;
		}
	}
}


/*
* @pattern当前要比较的pattern
* 
* 
* 将当前pattern与目标pattern进行比较
*/
bool pattern_compare(vector<int> pattern) {
	if (pattern.size() == 0) {	//如果pattern长度为0的话说明该pattern在上一步不能向所要移动的方向移动
		return false;
	}
	else
	{
		if (target_pattern == pattern) {	//如果该pattern和target_pattern匹配的话
			return true;
		}
		else {
			return false;
		}
	}
}

/*
* 
* 如果在lookuptable里面有的话就不添加
* 如果在lookuptable里面没有的话就添加
*/
void add_to_lower_layer(vector<vector<int>>& lower_layer, vector<int> pattern) {
	if (pattern.size() == 0) return;
	for (int i = 0; i < lookuptable.size(); i++) {
		if (lookuptable[i] == pattern) {
			return;
		}
	}
	lookuptable.push_back(pattern);
	lower_layer.push_back(pattern);
}

vector<int> BFS(vector<vector<int>> upper_layer) {
	cout << upper_layer.size() << endl;
	vector<vector<int>> lower_layer;
	for (int i = 0; i < upper_layer.size(); i++) {
		//向上移动
		vector<int> up = move_to(upper_layer[i], "up");
		if (pattern_compare(up)) {
			path.push_back(up);
			return upper_layer[i];
		}
		add_to_lower_layer(lower_layer, up);

		//向下移动
		vector<int> down = move_to(upper_layer[i], "down");
		if (pattern_compare(down)) {
			path.push_back(down);
			return upper_layer[i];
		}
		add_to_lower_layer(lower_layer, down);

		//向左移动
		vector<int> left = move_to(upper_layer[i], "left");
		if (pattern_compare(left)) {
			path.push_back(left);
			return upper_layer[i];
		}
		add_to_lower_layer(lower_layer, left);

		//向右移动
		vector<int> right = move_to(upper_layer[i], "right");
		if (pattern_compare(right)) {
			path.push_back(right);
			return upper_layer[i];
		}
		add_to_lower_layer(lower_layer, right);
	}


	//第二次
	vector<int> temp = BFS(lower_layer);
	if (temp.size() == 0) {
		vector<int> notfound;
		return notfound;
	}
	else {
		//溯源
		for (int i = 0; i < upper_layer.size(); i++) {
			vector<int> up = move_to(upper_layer[i], "up");
			if (up == temp) { 
				path.push_back(up);
				return upper_layer[i];
			}
			vector<int> down = move_to(upper_layer[i], "down");
			if (down == temp) {
				path.push_back(down);
				return upper_layer[i];
			}
			vector<int> left = move_to(upper_layer[i], "left");
			if (left == temp) {
				path.push_back(left);
				return upper_layer[i];
			}
			vector<int> right = move_to(upper_layer[i], "right");
			if (right == temp) {
				path.push_back(right);
				return upper_layer[i];
			}
		}
	}
}

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
	pattern.push_back(1);
	pattern.push_back(2);
	pattern.push_back(3);
	pattern.push_back(8);
	pattern.push_back(0);
	pattern.push_back(4);
	pattern.push_back(7);
	pattern.push_back(6);
	pattern.push_back(5);

	target_pattern.push_back(1);
	target_pattern.push_back(2);
	target_pattern.push_back(3);
	target_pattern.push_back(4);
	target_pattern.push_back(5);
	target_pattern.push_back(6);
	target_pattern.push_back(7);
	target_pattern.push_back(8);
	target_pattern.push_back(0);

	//pattern.push_back(1);
	//pattern.push_back(2);
	//pattern.push_back(3);
	//pattern.push_back(4);
	//pattern.push_back(5);
	//pattern.push_back(6);
	//pattern.push_back(7);
	//pattern.push_back(0);
	//pattern.push_back(8);

	//target_pattern.push_back(1);
	//target_pattern.push_back(3);
	//target_pattern.push_back(0);
	//target_pattern.push_back(4);
	//target_pattern.push_back(2);
	//target_pattern.push_back(6);
	//target_pattern.push_back(7);
	//target_pattern.push_back(5);
	//target_pattern.push_back(8);

	vector<vector<int>> temp;
	temp.push_back(pattern);
	lookuptable.push_back(pattern);
	vector<int> temp2 = BFS(temp);
	if (temp2.size() == 0) {
		cout << "未找到路径！！" << endl;
	}
	else {
		path.push_back(pattern);
		printPath();
	}
	return 0;
}
