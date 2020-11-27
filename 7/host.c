#include <sys/types.h> 
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main() 
{
    int s;
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        printf("socket failed\n");
    struct sockaddr_in myaddr, caddr;
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(43210);
    myaddr.sin_addr.s_addr = INADDR_ANY;
    fd_set readfds;
    if (bind(s, (struct sockaddr*)&myaddr, sizeof(myaddr)) == -1)
        printf("bind failed\n");
    if (listen(s, 3) == -1)
        printf("listen failed\n");

    int max_c = 20, max_sd = 0;
    int client_socket[20];
    int i;
    for (i = 0; i < max_c; ++i)
        client_socket[i] = 0;
    char buffer[200];
    char buffer2[20][200];

    for (i = 0; i < max_c; ++i) {
        char buffer_temp[20] = "User";
        char temp[3] = {(char)(i + 'A'), ':'};
        strcpy(buffer2[i], strcat(buffer_temp, temp));
    }
    while (1) {
        FD_ZERO(&readfds);
        FD_SET(s, &readfds);
        max_sd = s;
        for (i = 0 ; i < max_c; ++i) {   
            int c = client_socket[i];
            if(c > 0)   
                FD_SET(c, &readfds);   
            if(c > max_sd)   
                max_sd = c;   
        }   
        int activity = select(max_sd + 1, &readfds, 0, 0, 0);  
        int c;
        if (FD_ISSET(s, &readfds)) {
            c = accept(s, 0, 0);
            for (i = 0; i < max_c; i++) {   
                if( client_socket[i] == 0) {   
                    client_socket[i] = c;   
                    break;   
                }   
            }   
        }
        for (i = 0; i < max_c; ++i) {
            int c = client_socket[i];
            if (FD_ISSET(c, &readfds)) {
                if (recv(c, buffer, sizeof(buffer), 0) == 0) {
                    close(c);
                    client_socket[i] = 0;
                    continue;
                }
                if (buffer[0] == 'E' && buffer[1] == 'X' && buffer[2] == 'I' && buffer[3] == 'T') {
                    close(c);
                    client_socket[i] = 0;
                    continue;
                }
                if (buffer[0] == 'N' && buffer[1] == 'A' && buffer[2] == 'M' && buffer[3] == 'E' && buffer[4] == ':') {
                    memset(buffer2[i], 0, sizeof(buffer2[i]));
                    int j;
                    for (j = 5; j < sizeof(buffer); ++j)
                        buffer2[i][j - 5] = buffer[j];
                    strcat(buffer2[i], ":");
                    continue;
                }
                int j;
                for (j = 0; j < max_c; ++j) {
                    int cl = client_socket[j];
                    if (cl > 0) {
                        char btemp[200];
                        strcat(strcpy(btemp, buffer2[i]), buffer);
                        printf("%s\n", btemp);
                        send(cl, btemp, strlen(btemp), 0);
                    }
                }
            }
        }
    }
    for (i = 0; i < max_c; ++i) {
        int c = client_socket[i];
        if (c != 0) 
            close(c);
    }
    close(s);
}