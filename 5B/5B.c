#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/stat.h>

void encode(int csvin, int binout) {
    while (1) {
        char c;
        int flag;
        flag = read(csvin, &c, 1);
        if (flag == 0) break;
        if (c == ',') c = 1;
        write(binout, &c, 1);
    }
    return;
}

void decode(int binout, int csvout) {
    while (1) {
        char c;
        int flag;
        flag = read(binout, &c, 1);
        if (flag == 0) break;
        if (c == 1) c = ',';
        write(csvout, &c, 1);
    }
    return; 
}

int main()
{
    int csvin;
    csvin = open("input.csv", O_RDONLY);
    int binout;
    binout = open("output.bin", O_WRONLY | O_CREAT | O_TRUNC, 0x0180);
    encode(csvin, binout);
    close(csvin); close(binout);

    binout = open("output.bin", O_RDONLY);
    int csvout;
    csvout = open("output.csv", O_WRONLY | O_CREAT | O_TRUNC, 0x0180);
    decode(binout, csvout);
    close(binout); close(csvout);

    return 0;
}