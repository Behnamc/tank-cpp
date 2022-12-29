//* wall tank

#include <iostream>
#include "Pos.h"
using namespace std;

int pos_ptr = 0;
bool start = false;
Pos last_move = all_pos[0];

Pos new_ori() {
    pos_ptr >= 3 ? pos_ptr = 0 : pos_ptr++;
    return all_pos[pos_ptr];
}


pair<string, Pos> // example return {"move", Pos(1, 0)};
update(Pos pos, Pos epos, Pos ori, bool isfire, bool reload, int health)
{
    if (reload) {
        try {
            return pos.fire_enemy(epos);
        } catch (...) {}
    }
    
    if (!start) {
        if (pos.x == N - 1) {
            start = true;
        } else {
            return {"move", Pos(1, 0)};
        }
    }
    cout << "im out\n";

    if ((pos + last_move).isvalid()) {
        return {"move", last_move};
    } else {
        last_move = new_ori();
        return {"move", last_move};
    }





}

