#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    int fd12[2];
    int fd24[2];
    pipe(fd12);
    pipe(fd24);
    
    if (fork() == 0) {  //p1
        close(fd24[0]);
        


        if (fork() == 0) { //p2
            close(fd12[1]);
            dup2(fd12[0], 0);
            close(fd12[0]);
            dup2(fd24[1], 1);
            close(fd12[1]);
            
            execlp(argv[3], argv[3], NULL);
        } else {
            close(fd24[1]);
            close(fd12[0]);

            int32_t count = atoi(argv[1]);
            int32_t modulo = atoi(argv[2]);
            int32_t i;
            int32_t x;
            for (i = 0; i <= count; ++i) {
                x = (i*i) % modulo;
                write(fd12[1], &x, sizeof(int32_t));
            }
            close(fd12[1]);


        }
    } else if (fork() == 0) { //p3
            close(fd12[1]);
            close(fd12[0]);
            close(fd24[1]);
            if (fork() == 0) { //p4

                //close(fd24[1]);
                int32_t x;
                while (read(fd24[0], &x, sizeof(int32_t)) > 0) 
                    printf("%d\n", x);
            } else
                    close(fd24[0]);
            } else { //p0
                close(fd12[0]);
                close(fd12[1]);
                close(fd24[0]);
                close(fd24[1]);
                wait(0);
                wait(0);
                wait(0);
                wait(0);
            }
    return 0;
}
