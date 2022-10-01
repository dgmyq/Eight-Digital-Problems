#include <vector>
#include <ctime>
#include <cmath>

using namespace std;

void generate_pattern(vector<int>& pattern, vector<int>& targert_pattern)
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
        swap(pattern[rand() % 9], pattern[rand() % 9]);
    }

    count = rand() % 10 + 10;
    for (int i = 0; i < count; i++)
    {
        swap(targert_pattern[rand() % 9], targert_pattern[rand() % 9]);
    }
}