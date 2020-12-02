#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>

void encode(char *buffer) {
    int i;
    for (i = 0; i < strlen(buffer); ++i)
        if (buffer[i] == ',')
            buffer[i] = 1;
    return;
}

int main()
{
    int P[2];
    pipe(P);
    if (fork() == 0) {
        char buffer[256];
        close(P[1]);
        int binout = open("output.bin", O_WRONLY | O_CREAT | O_TRUNC, 0x0180);
        while (read(P[0], buffer, 256) > 0)
            write(binout, buffer, strlen(buffer));
        exit(0);
    } else {
        int csvin = open("input.csv", O_RDONLY);
        while (1) {
            char buffer[256] = {0};
            int flag;
            int counter = 0;
            while (1) {
                char c[1];
                flag = read(csvin, c, 1);
                if (flag <= 0) break;
                //printf("%s\n", c);
                buffer[counter] = c[0];
                ++counter;
                if (c[0] == '\n' || c[0] == '\r') break;
                //strcat(buffer, c);
            }
            buffer[counter] = '\0';
            if (flag <= 0) break;
            int chd[2], par[2];
            pipe(chd); pipe(par);
            if (fork() == 0) {
                char buffer2[256];
                close(par[1]);
                read(par[0], buffer2, 256);
                encode(buffer2);
                close(chd[0]);
                write(chd[1], buffer2, 256);
                exit(0);
            } else {
                close(par[0]);
                write(par[1], buffer, 256);
                char buffer2[256];
                close(chd[1]);
                read(chd[0], buffer2, 256);
                close(P[0]);
                write(P[1], buffer2, 256);
            }
            
        }
        
    }

}