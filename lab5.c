#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>

void sigf(int);

int main() {

    pid_t currentPID;
    pid_t forkPID;
    DIR* directory;
    time_t T;
    struct dirent *entry;
    struct tm *tm;
    int i;
    int x, c, f;
    
    currentPID = getpid();
    printf("PARENT PID: %d\n\n", currentPID);

    directory = opendir(".");
    forkPID = fork();

    c = 0;
    while(c >= 0) {
        if (forkPID > 0) {
            /* parent process */
            for (f = 0; f <= 65; f++) { 
                    signal(f, sigf);
                }
            wait(0);
            forkPID = fork();
        }
        if (forkPID == 0) {
            /* child process*/
            i = 0;
            while(i >= 0) {
                for (f = 0; f <= 65; f++) { 
                    signal(f, sigf);
                }

                time(&T);
                tm = localtime(&T);

                printf("CURRENT TIME: %s", asctime(tm));
                x = 0;
                while ((entry = readdir(directory)) != NULL) {
                    x++;
                    printf("FILE %d: %s\n", x, entry->d_name);
                }
                directory = opendir(".");
                sleep(10);
                printf("\n");
            }
        }
    }
    return 0;
}

void sigf(int sig) {
    printf(" -> signal #%d failed\n", sig);
}
