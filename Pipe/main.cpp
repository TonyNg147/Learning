#include <stdlib.h>
#include <unistd.h>
#include <thread>
#include <string.h>
#include <error.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
int main()
{
    int pipeFd[2] = {}; 
    if (pipe(pipeFd) == -1)
    {
        perror("Cannot Pipe\n");
        exit(EXIT_FAILURE);
    }
    switch(fork())
    {
        case -1:
        {
            perror("Cannot Fork process. Terminate\n");
            exit(EXIT_FAILURE);
            break;
        }
        case 0:
        {
            close(pipeFd[0]);
            if (dup2(pipeFd[1],STDOUT_FILENO) == -1)
            {
                fprintf(stderr, "Cannot duplicate fd. Error is %s\n",strerror(errno));
                exit(EXIT_FAILURE);
            }
            printf("Working on Child process %d. Parent process is %d\n", getpid(), getppid());
            printf("Good bye\n");
            close(pipeFd[1]);
            break;
        }
        default:
        {
            printf("Working on Parent process %d\n", getpid());
            int demoFile = open("/home/as/Desktop/Learning/Pipe/demo.txt", O_TRUNC | O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
            printf("%d\n", __LINE__);
            if (demoFile < 0)
            {
                perror("Cannot open file\n");
                exit(EXIT_FAILURE);
            }
            printf("%d\n", __LINE__);
            char buffer[4096];
            close(pipeFd[1]);
            ssize_t nbytes = -1;
            printf("%d\n", __LINE__);
            do
            {
                /* code */
                nbytes = read(pipeFd[0],buffer, 4096);
                if (nbytes < 0)
                {
                    fprintf(stderr, "Read error. Error is %s\n",strerror(errno));
                    exit(EXIT_FAILURE);
                }
                nbytes = write(demoFile, buffer, nbytes);
                if (nbytes < 0)
                {
                    fprintf(stderr, "Write error %s\n",strerror(errno));
                    exit(EXIT_FAILURE);
                }
                printf("Read nByte  %ld %d\n",nbytes,  __LINE__);
            } while (nbytes >0 );
            printf("%d\n", __LINE__);
            wait(nullptr);
            close(pipeFd[1]);
            close(demoFile);
            break;
        }
    }
    


    
    
}