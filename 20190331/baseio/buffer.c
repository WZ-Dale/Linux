/*缓冲区*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    printf("printf");
    fwrite("fwrite", 6, 1, stdout);
    fprintf(stdout, "fprintf");
    write(STDOUT_FILENO, "write", 5);
    sleep(3);
    return 0;
}
