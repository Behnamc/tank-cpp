#include <iostream>
#include <thread>
#include <time.h>
#include <chrono>
#include <future>
using namespace std;



// void f() {

//         for (int i = 0; i < 100000; i++) {
//             cout << "i : " << i << '\n';
//         }
// }


// void g() {
//     for (int i = 0; i < 10; i++) {
//         cout << ">>>j : " << i << '\n';
//     }
//     //delete &t1;
//     //throw 0;

//         //exit(0);
//     //terminate();
// }

int a, b;
void solve() {
    for (long long i = 0; i < 100; i++) {
        cout << "i :" << i << endl;
    }
    a = 5;
    //return 1;
}

void solve2() {
    for (long long i = 0; i < 100; i++) {
        cout << "j :" << i << endl;
    }
    b = 5;
    terminate_handler();
    //return 1;
}


void mysleep() {
    this_thread::sleep_for(chrono::milliseconds(1000));
    cout << "done\n";
}

void m() {
    thread t1(solve);
    thread t2(solve2);
    thread t3(mysleep);
    t1.detach();
    t2.detach();
    t3.join();
    cout << "m bye ------\n";
}

int main() {
    thread t(m);
    t.join();
    cout << "done\n" << a << ' ' << b;
}

/*
void threadFunction(std::future<void> futureObj)
{
    std::cout << "Starting the thread" << std::endl;
    while (futureObj.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout)
    {
        std::cout << "work done" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    std::cout << "Ending Thread" << std::endl;
}
int main()
{
     std::promise<void> exitSignal; // Create a std::promise object
     std::future<void> futureObj = exitSignal.get_future();//Fetch std::future object associated with promise
     std::thread th(&threadFunction, std::move(futureObj));// Starting Thread & move the future object in lambda function by reference
    std::this_thread::sleep_for(std::chrono::seconds(10)); //Waiting for 10 seconds
    std::cout << "Asking the thread to stop" << std::endl;
    exitSignal.set_value(); //Set the value
     th.join(); //Waiting for thread to be joined.
    std::cout << "Exit the Main Function" << std::endl;
    return 0;
}
*/
