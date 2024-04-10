#include <iostream>
#include <fstream>
#include <set>

using namespace std;

int main()
{
    ifstream input("input");
    set<int16_t> inset;

    int16_t i;
    while (input >> i)
    {
        if (inset.contains(2020 - i))
        {
            cout << i * (2020 - i);
            break;
        }
        else
        {
            inset.insert(i);
        }
    }
    return 0;
}