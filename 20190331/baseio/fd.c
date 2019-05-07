/*文件描述符*/
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main()
{
    int fd = open("./tmp.txt", O_RDWR);// 可读可写方式打开文件

    //让1也指向了fd所指向的文件
    //int dup2(int oldfd, int newfd);
    //  将newfd重定向到oldfd所指向的文件
    //  若newfd本身已有打开文件，重定向时则关闭已打开文件
    dup2(fd, 1);// 将1号进程,即把标准输出重定向到fd所指文件
    // 先定向,再做后续操作
    printf("%d\n", fd);//此处本应该会打印3,即句柄fp,但由于标准
    // 输出已经重定向到文件,所以3会写入tnp.txt文件,而不是打印到屏幕
    fflush(stdout);
    close(fd);
    return 0;
}
