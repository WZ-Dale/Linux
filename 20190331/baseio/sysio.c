/*系统调用接口使用*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main()
{
    //mode_t umask(mode_t mask);
    //修改调用进程的文件创建权限掩码
    umask(0);
    //int open(const char *pathname, int flags, mode_t mode);
    //  pathname：  文件路径名
    //  flags：     选项标志
    //      必选项：必选其一
    //          O_RDONLY    只读
    //          O_WRONLY    只写 
    //          O_RDWR      可读可写
    //      可选项：
    //          O_CREAT     文件不存在则创建，存在则打开
    //          O_EXCL      与O_CREAT同用时，若文件存在则报错
    //          O_TRUNC     打开文件同时截断文件长度为0
    //          O_APPEND    写追加模式
    //  mode：创建文件时给定权限（八进制数字）
    //      mode & (~umask)
    //  返回值：文件描述符-正整数       错误：-1
    int fd = open("./tmp.txt", O_RDWR | O_CREAT | O_APPEND, 0777);
    if (fd < 0) {
        perror("open error");
        return -1;
    }
    //ssize_t write(int fd, const void *buf, size_t count);
    //  fd: 打开文件所返回的文件描述符
    //  buf：要向文件写入的数据
    //  count：要写入的数据长度
    //  返回值：实际的写入字节数，  错误：-1
    char buf[1024] = "nihao~~~!!\n";
    int ret = write(fd, buf, strlen(buf));
    if (ret < 0) {
        perror("write error");
        return -1;
    }
    //off_t lseek(int fd, off_t offset, int whence);
    //  fd: 打开文件所返回的文件描述符
    //  offset: 偏移量
    //  whence：偏移位置
    //      SEEK_SET
    //      SEEK_CUR
    //      SEEK_END
    //  返回值：返回当前位置到文件起始位置的偏移量
    lseek(fd, 0, SEEK_SET);
    //ssize_t read(int fd, void *buf, size_t count);
    //  fd: 打开文件所返回的文件描述符
    //  buf：对读取到的数据进行存储的位置
    //  count：要读取的数据长度
    //  返回值：实际的读取字节数，  错误：-1
    memset(buf, 0x00, 1024);
    ret = read(fd, buf, 1023);
    if (ret < 0) {
        perror("read error");
        return -1;
    }
    printf("read buf:[%s]\n", buf);

    //int close(int fd);
    close(fd);
}
