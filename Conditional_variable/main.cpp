
#include <mutex>
#include <memory>
#include <iostream>
#include <chrono>
#include <thread>
#include <condition_variable> 
static bool isReady = false;
static std::mutex mtx;
static std::condition_variable cv;
void producer()
{
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::lock_guard<std::mutex> lock(mtx);
    std::cout<<"Producer\n";
    isReady = true;
    cv.notify_all();
}

void consumer()
{
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock,[]{return isReady;});
    std::cout<<"Consumer\n";

}

int main()
{
    std::cout<<"Start thread\n";
    std::thread p1(producer);
    std::thread p2(consumer);
    p1.join();
    p2.join();
}