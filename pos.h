#define N 10
#include <iostream>
using namespace std;
#pragma once

class Pos
{
public:
    int x;
    int y;

    Pos() {}

    Pos(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    Pos operator+(const Pos a)
    {
        return Pos(this->x + a.x, this->y + a.y);
    }

    void operator+=(const Pos a)
    {
        this->x += a.x;
        this->y += a.y;
    }

    bool operator==(const Pos a)
    {
        return (this->x == a.x && this->y == a.y);
    }

    Pos operator-(const Pos a)
    {
        return Pos(this->x - a.x, this->y - a.y);
    }

    bool isvalid()
    {
        return (this->x >= 0 && this->x < N && this->y >= 0 && this->y < N);
    }

    bool have(int a)
    {
        return (this->x == a || this->y == a);
    }

    friend bool equalx(Pos a, Pos b)
    {
        return (a.x == b.x && a.y != b.y);
    }
    
    friend bool equaly(Pos a, Pos b)
    {
        return (a.x != b.x && a.y == b.y);
    }

    friend std::ostream &operator<<(std::ostream &os, Pos const &m) {
        return os << m.x << ' ' << m.y << ' ';
    }

    // returns one of : Pos(0, 1) , Pos(1, 0), Pos(-1, 0), Pos(0, -1)
    static Pos rand_ori() {
        Pos a[4] = {Pos(0, 1) , Pos(1, 0), Pos(-1, 0), Pos(0, -1)};
        return a[rand() % 4];
    }

    static pair<string, Pos> fire_enemy(Pos pos, Pos epos) throw (int) {
        if (pos.x == epos.x) {
            if (pos.y > epos.y) {
                return {"fire", Pos(0, -1)};
            } else if (pos.y < epos.y) {
                return {"fire", Pos(0, 1)};
            } else {
                throw 1;
            }
        } else if (pos.y == epos.y) {
            if (pos.x > epos.x) {
                return {"fire", Pos(-1, 0)};
            } else if (pos.x < epos.x) {
                return {"fire", Pos(1, 0)};
            } else {
                throw 1;
            }
        } else {
            throw 1;
        }
    }

};
