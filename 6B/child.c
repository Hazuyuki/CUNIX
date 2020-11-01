#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(char *arg)
{
    int csvin;
    csvin = open(arg, O_RDONLY);
    int binout;
    
    return 0;
}