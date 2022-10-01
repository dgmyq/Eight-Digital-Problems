#include <vector>
#include <String>

using namespace std;

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