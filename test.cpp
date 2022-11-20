#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <math.h>
#include <set>

#include "Pos.h"

using namespace std;

pair<bool, Pos>
fire_enemy(Pos pos, Pos epos)
{
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i!=0 || j!=0)
            {
                for (Pos k = pos; k.isvalid(); k += Pos(i, j))
                {
                    if (k == epos)
                    {
                        return {true, Pos(i, j)};
                    }
                }
            }
        }
    }
    return {false, Pos(0, 0)};
}

int main()
{
    pair<bool, Pos> ans = fire_enemy(Pos(3, 0), Pos(3, 6));
    cout << ans.first << ' ' << ans.second << endl;
}
