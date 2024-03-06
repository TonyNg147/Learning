#include <iostream>
#include <unistd.h>
#include <wait.h>
#include <mutex>
#include <memory>
#include <sys/mman.h>
int main()
{
    // std::mutex mtx;

    int j = 0;

    void* shared_ptr = mmap(nullptr, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED| MAP_ANON, 0, 0);

    void* shared_mtx = mmap(nullptr, sizeof(std::mutex), PROT_READ | PROT_WRITE, MAP_SHARED| MAP_ANON, 0, 0);



    if (shared_ptr == MAP_FAILED || shared_mtx == MAP_FAILED)
    {
        printf("Map Failed\n");
        exit(EXIT_FAILURE);
    }

    printf("Success\n");

    int* ptr = (int*)shared_ptr;

    std::mutex* mtx = (std::mutex*)shared_mtx;

    *ptr = 0;

    switch(fork())
    {
        case -1:
        {
            break;
        }
        case 0:
        {
            for (int i=0;i < 10; ++i)
            {
                std::lock_guard<std::mutex> lock(*mtx);
                ++(*ptr); 
                printf("In Child Process %d\n", (*ptr));
            }
            break;
        }
        default:
        {
            
            for (int i=0;i < 10; ++i)
            {
                std::lock_guard<std::mutex> lock(*mtx);
                ++(*ptr); 
                printf("In Parent Process %d\n", (*ptr));
            }
            wait(nullptr);
            
            break;
        }
    }
}