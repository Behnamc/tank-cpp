// wall tank

#include <iostream>
#include "Pos.h"
using namespace std;

bool start = false;
Pos mov = Pos(1, 0);
int p = 0;
Pos moves[4] = {Pos(1, 0), Pos(0, 1), Pos(-1, 0), Pos(0, -1)};


pair<bool, Pos> // isfire, (0, 1)
update(Pos pos, Pos epos, Pos ori, bool isfire, bool reload, int health)
{
    if (pos.x > 0 && !start)
        return {false, Pos(-1, 0)};
    if (pos.y > 0 && !start)
        return {false, Pos(0, -1)};
    start = true;
    if (equalx(pos, epos) && reload)
    {
        Pos fire = Pos(0, -1);
        if (epos.y > pos.y)
        {
            fire = Pos(0, 1);
        }
        return {true, fire};
    }
    else if (equaly(pos, epos) && reload)
    {
        Pos fire = Pos(-1, 0);
        if (epos.x > pos.x)
        {
            fire = Pos(1, 0);
        }
        return {true, fire};
    }
    if ((mov + pos).isvalid())
    {
        return {false, mov};
    }
    else
    {
        p < 3 ? p++ : p = 0;
        mov = moves[p];
        return {false, mov};
    }
}
