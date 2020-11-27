#include <sys/types.h> 
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <fcntl.h>

int main() 
{
    int s;
    char buffer[200];
    s = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in myaddr, caddr;
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(43210);
    myaddr.sin_addr.s_addr = INADDR_ANY;
    connect(s, (struct sockaddr*)&myaddr, sizeof(myaddr));
    if (fork() == 0) {
        while (1) {
            memset(buffer, 0, sizeof(buffer));
            if (recv(s, buffer, sizeof(buffer), 0) == 0)
                exit(0);
            printf("%s\n", buffer);
        }
    }
    while (1) {
        scanf("%s", &buffer);
        send(s, buffer, sizeof(buffer), 0);
        if (buffer[0] == 'E' && buffer[1] == 'X' && buffer[2] == 'I' && buffer[3] == 'T')
            break;
    }
    close(s);
}