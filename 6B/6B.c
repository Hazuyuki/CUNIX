#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

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

void MT_encoder() {
    int csvin;
    csvin = open("input.csv", O_RDONLY);
    char c2[5] = "0";
    int counter = 0;
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
            if (c == '\n' || c == '\r') break;
        }
        close(tmpout);
        if (flag <= 0) break;
        if (fork() == 0) {    
            int csvin;
            csvin = open(fn, O_RDONLY);
            int binout;
            char s1[100] = "", *s2 = ".bin";
            binout = open(strcat(strcat(s1, fn), s2), O_WRONLY | O_CREAT | O_TRUNC, 0x0180);
            encode(csvin, binout);
            close(csvin);
            close(binout);
            exit(0);
        } else {
            ++counter;
        }
    }
    close(csvin);
    int i;
    for (i = 0; i < counter; ++i) {
        wait();
    }
    int outfile = open("output.bin", O_WRONLY | O_CREAT | O_TRUNC, 0x0180);
    char num[5] = "0";
    for (i = 0; i < counter; ++i) {
        char s1[30] = "temp/", *s3 = ".csv.bin";
        num[0] += 1;
        int infile = open(strcat(strcat(s1, num), s3), O_RDONLY);
        int flag = 1;
        char c;
        while (flag > 0) {
            flag = read(infile, &c, 1);
            if (flag > 0)
                write(outfile, &c, 1);
        }
        close(infile);
    }
    close(outfile);
    return;
}

void MT_decoder() {
    int csvin;
    csvin = open("output.bin", O_RDONLY);
    char c2[5] = "0";
    int counter = 0;
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
            if (c == '\n' || c == '\r') break;
        }
        close(tmpout);
        if (flag <= 0) break;
        if (fork() == 0) {    
            int csvin;
            csvin = open(fn, O_RDONLY);
            int binout;
            char s1[100] = "", *s2 = ".bin";
            binout = open(strcat(strcat(s1, fn), s2), O_WRONLY | O_CREAT | O_TRUNC, 0x0180);
            decode(csvin, binout);
            close(csvin);
            close(binout);
            exit(0);
        } else {
            ++counter;
        }
    }
    close(csvin);
    int i;
    for (i = 0; i < counter; ++i) {
        wait();
    }
    int outfile = open("output.csv", O_WRONLY | O_CREAT | O_TRUNC, 0x0180);
    char num[5] = "0";
    for (i = 0; i < counter; ++i) {
        char s1[30] = "temp/", *s3 = ".csv.bin";
        num[0] += 1;
        int infile = open(strcat(strcat(s1, num), s3), O_RDONLY);
        int flag = 1;
        char c;
        while (flag > 0) {
            flag = read(infile, &c, 1);
            if (flag > 0)
                write(outfile, &c, 1);
        }
        close(infile);
    }
    close(outfile);
    return;
}

int main()
{
    MT_encoder();
    MT_decoder();
    return 0;
}