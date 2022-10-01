#include <iostream>
#include <vector>
#include "globle_var.h"
#include "move_to.h"

using namespace std;

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

vector<int> bfs(vector<vector<int>> upper_layer) {
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
	vector<int> temp = bfs(lower_layer);
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