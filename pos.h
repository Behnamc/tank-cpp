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

    Pos(const Pos &a)
    {
        this->x = a.x;
        this->y = a.y;
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

    void operator*=(const int a)
    {
        this->x *= a;
        this->y *= a;
    }

    bool isvalid()
    {
        return (this->x >= 0 && this->x < N && this->y >= 0 && this->y < N);
    }

    bool have(int a)
    {
        return (this->x == a || this->y == a);
    }

    friend bool equaljustx(Pos a, Pos b)
    {
        return (a.x == b.x && a.y != b.y);
    }

    friend bool equaljusty(Pos a, Pos b)
    {
        return (a.x != b.x && a.y == b.y);
    }

    friend std::ostream &operator<<(std::ostream &os, Pos const &m)
    {
        return os << m.x << ' ' << m.y << ' ';
    }

    pair<string, Pos> fire_enemy(Pos epos) throw(int)
    {
        Pos angle_pos[4] = {Pos(1, 1), Pos(-1, 1), Pos(-1, -1), Pos(1, -1)};
        if (this->x == epos.x)
        {
            if (this->y > epos.y)
            {
                return {"fire", Pos(0, -1)};
            }
            else if (this->y < epos.y)
            {
                return {"fire", Pos(0, 1)};
            }
            else
            {
                throw 1;
            }
        }
        else if (this->y == epos.y)
        {
            if (this->x > epos.x)
            {
                return {"fire", Pos(-1, 0)};
            }
            else if (this->x < epos.x)
            {
                return {"fire", Pos(1, 0)};
            }
            else
            {
                throw 1;
            }
        }
        else
        {
            // check enemy is in th angels?
            for (int i = 0; i < 4; i++)
            {
                Pos t(*this);
                while (true)
                {
                    t += angle_pos[i];
                    if (!t.isvalid())
                        break;
                    if (epos == t)
                    {
                        return {"fire", angle_pos[i]};
                    }
                }
            }
        }
        throw 1;
    }
};

const Pos all_pos[4] = {Pos(0, -1), Pos(-1, 0), Pos(0, 1), Pos(1, 0)};

// returns one of : Pos(0, 1) , Pos(1, 0), Pos(-1, 0), Pos(0, -1)
Pos random_ori_move()
{
    return all_pos[rand() % 4];
}
