#include <iostream>
#include <stack>
#include <vector>
#include <String>
#include <ctime>
#include <cmath>

using namespace std;

vector<int> target_pattern;      //存放目标九宫格
vector<vector<int>> path;        //存放路径
vector<vector<int>> lookuptable; //存放曾经查找过的pattern

/*
 * @pattern	移动前的九宫格
 * @mode		向上、下、左、右移动
 *
 * 可以移动的话就返回移动后的pattern
 * 不能移动的话就返回一个空的vector<int>
 */
vector<int> move_to(vector<int> pattern, string mode)
{
    int space = 0; //存放空格的位置
    for (int i = 0; i < 9; i++)
    { //查找空格的位置
        if (pattern[i] == 0)
        {
            space = i;
            break;
        }
    }

    vector<int> result; //存放移动后的pattern
    if (mode.compare("up") == 0)
    {
        if ((space == 0) || (space == 1) || (space == 2))
        { //如果是0，1，2位置则不能向上移动
            return result;
        }
        else
        {
            pattern[space] = pattern[space - 3]; //其余的位置可以向上移动
            pattern[space - 3] = 0;
            result = pattern;
            return result;
        }
    }
    else if (mode.compare("down") == 0)
    {
        if ((space == 6) || (space == 7) || (space == 8))
        { //如果是6，7，8位置则不能向下移动
            return result;
        }
        else
        {
            pattern[space] = pattern[space + 3]; //其余的位置可以向下移动
            pattern[space + 3] = 0;
            result = pattern;
            return result;
        }
    }
    else if (mode.compare("left") == 0)
    {
        if ((space == 0) || (space == 3) || (space == 6))
        { //如果是0，3，6位置则不能向左移动
            return result;
        }
        else
        {
            pattern[space] = pattern[space - 1]; //其余的位置可以向左移动
            pattern[space - 1] = 0;
            result = pattern;
            return result;
        }
    }
    else if (mode.compare("right") == 0)
    {
        if ((space == 2) || (space == 5) || (space == 8))
        { //如果是2，5，8位置则不能向下移动
            return result;
        }
        else
        {
            pattern[space] = pattern[space + 1]; //其余的位置可以向右移动
            pattern[space + 1] = 0;
            result = pattern;
            return result;
        }
    }
}

void printPath()
{
    for (int i = 0; i < path.size(); i++)
    {
        for (int j = 1; j <= path[i].size(); j++)
        {
            if (path[i][j - 1] == 0)
            {
                cout << "  ";
            }
            else
            {
                cout << path[i][j - 1] << " ";
            }
            if (j % 3 == 0)
                cout << endl;
        }
        cout << endl;
    }
}

bool inversion(vector<int> &pattern, vector<int> &target_pattern)
{
	cout << "checking..." << endl;
	int count = 0;
	for (int i = 0; i < pattern.size(); i++)
	{
		int j = 0;
		for (; target_pattern[j] != pattern[i]; j++)
			;
		for (int n = i - 1; n >= 0; n--)
		{
			for (int m = j + 1; m < 9; m++)
			{
				if (pattern[n] == target_pattern[m])
				{
					count++;
				}
			}
		}
	}
	if (count % 2 == 0)
		return true;
	return false;
}

void generate_pattern(vector<int> &pattern, vector<int> &targert_pattern)
{
	double a = 123456708;
	double b = 413026758;

	srand((unsigned)time(NULL));
	pattern = {0, 1, 2, 3, 4, 5, 6, 7, 8};
	targert_pattern = {0, 1, 2, 3, 4, 5, 6, 7, 8};

	//打乱数组

	int count = rand() % 10 + 10;
	for (int i = 0; i < count; i++)
	{
		swap(targert_pattern[rand() % 9], targert_pattern[rand() % 9]);
	}

	do
	{
		count = rand() % 10 + 10;
		for (int i = 0; i < count; i++)
		{
			swap(pattern[rand() % 9], pattern[rand() % 9]);
		}
	}while(inversion(pattern, targert_pattern) == false);
}

void print_pattern(vector<int> pattern)
{
    for (int i = 1; i <= pattern.size(); i++)
    {
        if (pattern[i - 1] == 0)
        {
            cout << "  ";
        }
        else
        {
            cout << pattern[i - 1] << " ";
        }
        if (i % 3 == 0)
            cout << endl;
    }
    cout << endl;
}

bool lookup_lookuptable(vector<int> pattern)
{
    for (int i = 0; i < lookuptable.size(); i++)
    {
        if (lookuptable[i] == pattern)
        {
            return true;
        }
    }
    return false;
}

bool DFS(vector<int> root, double& a)
{
    cout << a << "-";
    if (a > 200)    return false;
    //cout << "into" << endl;
    if (root == target_pattern)
    {
        path.push_back(root);
        return true;
    }
    else
    {
        if (lookup_lookuptable(root) == true)
            return false;
        lookuptable.push_back(root);
        vector<int> up = move_to(root, "up");
        if (up.size() != 0)
        {
            a++;
            if (DFS(up, a))
            {
                path.push_back(root);
                return true;
            }
            a--;
        }

        vector<int> down = move_to(root, "down");
        if (down.size() != 0)
        {
            a++;
            if (DFS(down, a))
            {
                path.push_back(root);
                return true;
            }
            a--;
        }

        vector<int> left = move_to(root, "left");
        if (left.size() != 0)
        {
            a++;
            if (DFS(left, a))
            {
                path.push_back(root);
                return true;
            }
            a--;
        }

        vector<int> right = move_to(root, "right");
        if (right.size() != 0)
        {
            a++;
            if (DFS(right, a))
            {
                path.push_back(root);
                return true;
            }
            a--;
        }
    }
    return false;
}

int main()
{
    vector<int> pattern;
    generate_pattern(pattern, target_pattern);	//generate original pattern and target pattern
    //pattern = {2, 0, 3, 1, 8, 4, 7, 6, 5};
    //target_pattern = {2, 8, 3, 0, 6, 4, 1, 7, 5};
    print_pattern(pattern);
    print_pattern(target_pattern);
    system("pause");

    double a = 1;
    DFS(pattern, a);
    cout << endl;
    if (path.size() != 0) {
        printPath();
    }
    else {
        cout << "fail to find the path" << endl;
    }

    system("pause");
    return 0;
}