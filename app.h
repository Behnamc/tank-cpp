#include <iostream>
#include <cstdlib>
#include <time.h>
#include <thread>
#include <chrono>
#include "pos.h"
#define F first
#define S second
using namespace std;
using namespace std::chrono;

#define N 10
#define MAX_HEALTH 10
#define RELOAD_SIZE 2
#define SLEEP_TIME 500

const int sibl = 50;

char chart[N][N];
char fire_sign[2] = {'+', '*'};
Pos pos[2]; // set in two_rand_pos()
Pos ori[2] = {Pos(0, 0), Pos(0, 0)};
int health[2] = {MAX_HEALTH, MAX_HEALTH};
int reload[2] = {2, 2};
bool isfire[2] = {false, false};
int sleep_time = 20;

namespace tank1
{
#include "tank1.cpp"
}

namespace tank2
{
#include "tank2.cpp"
}

int end_;
pair<string, Pos> return_[2];

void keeper()
{
    this_thread::sleep_for(milliseconds(sleep_time * sibl));
    for (int i = 0; i < 20 - sleep_time; i++)
    {
        if (end_ == 2)
            return;
        this_thread::sleep_for(milliseconds(sibl));
    }
}

// void running(function f, int millisecond, int default)
void run_tanks()
{
    // set default
    end_ = 0;
    return_[0] = {"move", Pos(0, 0)};
    return_[1] = {"move", Pos(0, 0)};

    auto f = [&]()
    {
        return_[0] = tank1::update(
            pos[0],
            pos[1],
            ori[1],
            isfire[0],
            (reload[0] >= RELOAD_SIZE),
            health[0]);
        end_++;
    };

    auto g = [&]()
    {
        return_[1] = tank2::update(
            pos[1],
            pos[0],
            ori[0],
            isfire[1],
            (reload[1] >= RELOAD_SIZE),
            health[1]);
        end_++;
    };

    thread t1(f);
    thread t2(g);
    thread keeper_(keeper);
    t1.detach();
    t2.detach();
    keeper_.join();
}

class Game
{
private:
    pair<Pos, Pos>
    two_rand_pos()
    {
        Pos pos1 = Pos(rand() % N, rand() % N);
        Pos pos2 = Pos(rand() % N, rand() % N);
        if (pos1 == pos2)
            return two_rand_pos();
        return {pos1, pos2};
    }

    pair<bool, Pos>
    check_ori(pair<string, Pos> ans, int p)
    {
        if (ans.F == "fire") // isfire
        {
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    if (ans.S.x == i && ans.S.y == j && !(i == 0 && j == 0) && reload[p] >= RELOAD_SIZE)
                        return {ans.F == "fire", ans.S};
                }
            }
        }
        else if (ans.F == "move") // is move
        {
            for (Pos i : {Pos(0, 1), Pos(1, 0), Pos(-1, 0), Pos(0, -1)})
            {
                if (i == ans.S && (pos[p] + i).isvalid())
                    return {ans.F == "fire", ans.S};
            }
        } // default
        return {false, Pos(0, 0)};
    }

    void set_reload_and_move()
    {
        for (int i = 0; i < 2; i++)
        {
            if (isfire[i])
            {
                reload[i] = 0;
            }
            else
            {
                if (reload[i] < RELOAD_SIZE)
                    reload[i]++;
                pos[i] += ori[i];
            }
        }
    }

    void set_newchart_and_fire()
    {
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                chart[i][j] = '.';
        // fire
        for (int i = 0; i < 2; i++)
        {
            if (isfire[i])
            {
                for (Pos p = pos[i] + ori[i]; p.isvalid(); p += ori[i])
                {
                    chart[p.x][p.y] = fire_sign[i];
                    if (p == pos[1 - i])
                    {
                        health[1 - i] -= 1;
                    }
                }
            }
        }

        // push A & B
        if (pos[0] == pos[1])
        {
            chart[pos[0].x][pos[0].y] = '&';
        }
        else
        {
            chart[pos[0].x][pos[0].y] = 'A';
            chart[pos[1].x][pos[1].y] = 'B';
        }
    }

    bool gameover()
    {
        if (health[0] == 0 && health[1] == 0) 
        {
            cout << "Equal\n";
            return false;
        }
        else if (health[0] <= 0)
        {
            cout << "B is winner\n";
            return false;
        }
        else if (health[1] <= 0)
        {
            cout << "A is winner\n";
            return false;
        }
        else
        {
            return true;
        }
    }

    void get_inf_update()
    {
        run_tanks();
        pair<bool, Pos> t[2] = {
            check_ori(return_[0], 0),
            check_ori(return_[1], 1)};
        // set new fire and move
        for (int i = 0; i < 2; i++)
        {
            isfire[i] = t[i].F;
            ori[i] = t[i].S;
        }
    }

public:
    Game()
    {
        srand(time(0));
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                chart[i][j] = '.';
        auto poss = two_rand_pos();
        pos[0] = poss.F;
        pos[1] = poss.S;
    }

    void update()
    {
        get_inf_update();
        set_reload_and_move();
        set_newchart_and_fire();
        show();
    }

    void show()
    {
        for (int j = 0; j < N; j++)
        {
            cout << "-----------------------------------------\n|";
            for (int i = 0; i < N; i++)
            {
                if (chart[i][j] == fire_sign[0])
                    cout << "@ @|";
                else
                    cout << " " << chart[i][j] << " |";
            }
            cout << endl;
        }
        cout << "-----------------------------------------\n";
        for (int i = 0; i < 2; i++)
        {
            cout << char('A' + i) << " healh: ";
            for (int j = 0; j < health[i]; j++)
                cout << '+';
            for (int j = 0; j < MAX_HEALTH - health[i]; j++)
                cout << '-';
            cout << '\n';
        }
    }

    void run_game()
    {
        while (gameover())
        {
            update();
        }
    }

    void run()
    {
    }
};

Game game;

void sleep_handler()
{
    while (true)
    {
        cin >> sleep_time;
    }
}

void run_game()
{
    game.run_game();
}

void running()
{
    thread th1(sleep_handler);
    thread th2(run_game);
    th1.join();
    th2.join();
}