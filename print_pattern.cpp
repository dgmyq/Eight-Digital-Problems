#include <iostream>
#include <vector>

using namespace std;

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