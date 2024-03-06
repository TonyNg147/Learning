#include <thread>
#include <iostream>
#include <semaphore.h>

int j = 0;

sem_t sem;

void increase(int id)
{
    sem_wait(&sem);
    for (int i=0; i < 10; ++i)
    {
        ++j;
        printf("Thread id %d increase value %d\n", id, j);
    }
    sem_post(&sem);
    
}


int main()
{
    if (sem_init(&sem, 0, 1) == -1)
    {
        fprintf(stderr, "Init failed\n");
        exit(EXIT_FAILURE);
    }

    std::thread p1(&increase, 1);

    std::thread p2(&increase, 2);

    p1.join();

    p2.join();
}