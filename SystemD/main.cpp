#ifndef MAIN_CPP
#define MAIN_CPP
#include <iostream>
#include <thread>
#include <chrono>
int main()
{
    while(1)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout<<"Nguyen pro\n";
    }
}
#endif //MAIN_CPP