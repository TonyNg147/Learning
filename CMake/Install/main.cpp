#include <iostream>
#include <unistd.h>
#include <string>

#ifdef NGUYEN
int i = 1;
#else
int i = 2;
#endif
int main()
{
    std::cout<<"I " << i<<"\n";
}