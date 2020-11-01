#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int csvin;
    csvin = open("input.csv", O_RDONLY);
    char c2[5] = "0";
    while (1) {
        ++(c2[0]);
        int flag;
        char s1[100] = "temp/", *s3 = ".csv";
        char *fn = strcat(strcat(s1, c2), s3);
        int tmpout;
        tmpout = open(fn, O_WRONLY | O_CREAT | O_TRUNC, 0x0180);
        while (1) {
            char c;
            flag = read(csvin, &c, 1);
            write(tmpout, &c, 1);
            if (flag <= 0) break;
            if (fork() == 0) {
                execl("child", fn);
                exit(0);
            }
            if (c == '\n' || c == '\r') break;
        }
        close(tmpout);
        if (flag <= 0) break;
    }
    close(csvin);

    return 0;
}