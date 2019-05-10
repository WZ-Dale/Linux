/*  命名管道的基本使用
 *  int mkfifo(const char *pathname, mode_t mode);
 *      pathname:   管道文件名
 *      mode：  创建权限  0664
 *  返回值：0       失败：-1
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

int main()
{
    char *file = "./test.fifo";
    umask(0);
    int ret = mkfifo(file, 0664);
    if (ret < 0) {
        if (errno != EEXIST) {// 判断错误并不是由文件存在引起的
            perror("mkfifo error");
            return -1;
        }
    }
    printf("open file\n");
    int fd = open(file, O_WRONLY);
    if (fd < 0) {
        perror("open error");
        return -1;
    }
    printf("open success!!\n");
    while(1) {
        char buf[1024] = {0};
        scanf("%s", buf);
        write(fd, buf, strlen(buf));
    }
    close(fd);
    return 0;
}
