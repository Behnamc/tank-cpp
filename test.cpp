#include <thread>
#include <iostream>
#include <thread>
#include <chrono>
#include "pos.h"
using namespace std;
using namespace std::chrono;

const int sibl = 50;
int sleep_time = 10;

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
        // return_[0] = tank1::update(
        //     pos[0],
        //     pos[1],
        //     ori[1],
        //     isfire[0],
        //     (reload[0] >= RELOAD_SIZE),
        //     health[0]
        // );
        end_++;
    };

    auto g = [&]()
    {
        // return_[1] = tank2::update(
        //     pos[1],
        //     pos[0],
        //     ori[0],
        //     isfire[1],
        //     (reload[1] >= RELOAD_SIZE),
        //     health[1]
        // );
        end_++;
    };

    thread t1(f);
    thread t2(g);
    thread keeper_(keeper);
    t1.detach();
    t2.detach();
    keeper_.join();
}


int main()
{
    run_tanks();
    // use return0, return1
}