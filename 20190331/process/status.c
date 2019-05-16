/*状态切换*/

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

int main()
{
    uint64_t a = 0;
    fork();
    while(1) {
        a++;
        usleep(1000);
    }
    return 0;
}
