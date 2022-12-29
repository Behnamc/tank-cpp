//* zaloo tank
// targets: go to enemy and just fire from each side

#include <iostream>
#include "Pos.h"
using namespace std;

bool fight = false;

pair<string, Pos>
goto_enemy(Pos pos, Pos epos, bool reload) {
    if (fight && reload) {
        try {
            return pos.fire_enemy(epos);
        } catch (...) {}
    }
    if (pos.x > epos.x)
        return {"move", Pos(-1, 0)};
    if (pos.x < epos.x)
        return {"move", Pos(1, 0)};
    if (pos.y > epos.y)
        return {"move", Pos(0, -1)};
    if (pos.y < epos.y)
        return {"move", Pos(0, 1)};
    fight = true;
    return {"move", random_ori_move()};

}

pair<string, Pos> // example return {"move", Pos(1, 0)};
update(Pos pos, Pos epos, Pos ori, bool isfire, bool reload, int health)
{

    return goto_enemy(pos, epos, reload);
}
