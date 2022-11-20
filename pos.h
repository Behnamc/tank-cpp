#define N 10
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

};
