#include <iostream>
#include <queue>
#include <vector>
#include <utility>
#include <map>
#include <ctime>
#include <cmath>

using namespace std;

struct from_greatest_to_smallest
{
    bool operator()(pair<vector<int>, double> a, pair<vector<int>, double> b)
    {
        return a.second > b.second; //小顶堆
    }
};

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

double heuristic(vector<int> current_pattern, vector<int> target_pattern) {
    int temp = 0;
    if (temp == 1) {
        //第一个启发函数
        double distance = 0;
        for (int i = 0; i < current_pattern.size(); i++) {
            int j = 0;
            for (; j < target_pattern.size(); j++);
            distance += abs(i - j);
        }
        return distance;
    }
    else if (temp == 0) {
        //第二个启发函数
        double distance = 0;
        for (int i = 0; i < current_pattern.size(); i++) {
            int j = 0;
            for (; j < target_pattern.size(); j++);
            int a_x, a_y, b_x, b_y;
            a_x = i / 3 + 1;
            a_y = i % 3;
            b_x = j / 3 + 1;
            b_y = j % 3;
            distance += sqrt(pow((a_x - b_x), 2) + pow((a_y - b_y), 2));
        }
        return distance;
    }

}

map<vector<int>, vector<int>> came_from;

void heuristic_algorithm(vector<int> pattern, vector<int> target_pattern)
{
    priority_queue<pair<vector<int>, double>,
        vector<pair<vector<int>, double>>,
        from_greatest_to_smallest>
        frontier; //边界
    frontier.push(make_pair(pattern, 0));
    map<vector<int>, double> cost_so_far;
    vector<int> nothing;
    came_from.insert(make_pair(pattern, nothing));
    cost_so_far.insert(make_pair(pattern, 0));

     while (!frontier.empty())
     {
         cout << frontier.size() << endl;
         vector<int> current_pattern = frontier.top().first;
         frontier.pop();
         if (current_pattern == target_pattern)
         {
             break;
         }

         vector<int> up = move_to(current_pattern, "up");
         if (up.size() != 0)
         {
             map<vector<int>, double>::iterator iter = cost_so_far.find(current_pattern);
             double new_cost = iter->second + 1; // 1 stands for the cost from the current graph to the next graph
             if (cost_so_far.find(up) == cost_so_far.end() || new_cost < cost_so_far.find(up)->second)
             {
                 cost_so_far.insert(make_pair(up, new_cost));
                 double priority = new_cost + heuristic(up, target_pattern);
                 frontier.push(make_pair(up, priority));
                 came_from.insert(make_pair(up, current_pattern));
             }
         }

         vector<int> down = move_to(current_pattern, "down");
         if (down.size() != 0)
         {
             map<vector<int>, double>::iterator iter = cost_so_far.find(current_pattern);
             double new_cost = iter->second + 1; // 1 stands for the cost from the current graph to the next graph
             if (cost_so_far.find(down) == cost_so_far.end() || new_cost < cost_so_far.find(down)->second)
             {
                 cost_so_far.insert(make_pair(down, new_cost));
                 double priority = new_cost + heuristic(down, target_pattern);
                 frontier.push(make_pair(down, priority));
                 came_from.insert(make_pair(down, current_pattern));
             }
         }

         vector<int> left = move_to(current_pattern, "left");
         if (left.size() != 0)
         {
             map<vector<int>, double>::iterator iter = cost_so_far.find(current_pattern);
             double new_cost = iter->second + 1; // 1 stands for the cost from the current graph to the next graph
             if (cost_so_far.find(left) == cost_so_far.end() || new_cost < cost_so_far.find(left)->second)
             {
                 cost_so_far.insert(make_pair(left, new_cost));
                 double priority = new_cost + heuristic(left, target_pattern);
                 frontier.push(make_pair(left, priority));
                 came_from.insert(make_pair(left, current_pattern));
             }
         }

         vector<int> right = move_to(current_pattern, "right");
         if (right.size() != 0)
         {
             map<vector<int>, double>::iterator iter = cost_so_far.find(current_pattern);
             double new_cost = iter->second + 1; // 1 stands for the cost from the current graph to the next graph
             if (cost_so_far.find(right) == cost_so_far.end() || new_cost < cost_so_far.find(right)->second)
             {
                 cost_so_far.insert(make_pair(right, new_cost));
                 double priority = new_cost + heuristic(right, target_pattern);
                 frontier.push(make_pair(right, priority));
                 came_from.insert(make_pair(right, current_pattern));
             }
         }
     }
}

bool inversion(vector<int>& pattern, vector<int>& target_pattern)
{
    cout << "checking..." << endl;
    int count = 0;
    for (int i = 0; i < pattern.size(); i++) //取出一个数判断它的逆序数量
    {
        int j = 0;
        for (; target_pattern[j] != pattern[i]; j++)
            ; //查找这个数在原序列中的位置
        for (int n = i - 1; n >= 0; n--)
        {
            for (int m = j + 1; m < 9; m++)
            {
                if (target_pattern[m] == 0 || pattern[i] == 0)
                    continue;
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

void generate_pattern(vector<int>& pattern, vector<int>& targert_pattern)
{
    double a = 123456708;
    double b = 413026758;

    srand((unsigned)time(NULL));
    pattern = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    targert_pattern = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };

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
    } while (inversion(pattern, targert_pattern) == false);
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

int main()
{
    vector<int> pattern;
    vector<int> target_pattern;
    generate_pattern(pattern, target_pattern);
    //pattern = { 1, 2, 3, 4, 0, 5, 6, 7, 8 };
    //target_pattern = { 1, 3, 0, 4, 2, 5, 6, 7, 8 };
    print_pattern(pattern);
    print_pattern(target_pattern);
    system("pause");

    heuristic_algorithm(pattern, target_pattern);
    for (vector<int> temp = target_pattern; temp.size() != 0;) {
        print_pattern(temp);
        map<vector<int>, vector<int>>::iterator iter = came_from.find(temp);
        temp = iter->second;
    }
    system("pause");
}