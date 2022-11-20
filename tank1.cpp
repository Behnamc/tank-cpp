// empty tank

#include <iostream>
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


pair<bool, Pos> // isfire, (0, 1)
update(Pos pos, Pos epos, Pos ori, bool isfire, bool reload, int health)
{
    return fire_enemy(pos, epos);
}
