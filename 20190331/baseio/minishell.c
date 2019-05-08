/*minishell实现*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

char buf[1024] = {0};
char *argv[32];
int argc = 0;

void do_face() {
    printf("[wangze@localhost]$ ");
    fflush(stdout);           //刷新缓冲区
    memset(buf, 0x00, 1024);  //初始化buf
    if (scanf("%[^\n]%*c", buf) != 1) {
        getchar();// [^\n]获取数据直到遇到\n,*c忽略字符前的所有
    }
    return ;
}
// 解析流程: 取出空白字符,获取程序名称和参数
void do_parse()
{
    char *ptr = buf;
    argc = 0;
    while(*ptr != '\0') {
        //当前位置非空白字符
        if (!isspace(*ptr)) {
            argv[argc++] = ptr;
            while(!isspace(*ptr) && *ptr != '\0') {
                ptr++;// 跳过
            }
        }else {
            *ptr = '\0';
            ptr++;
        }
    }
    argv[argc] = NULL;// 尾置空
    return;
}
int main()
{
    // ls >> > a.txt
    // int fd = open(a.txt);
    // dup2(fd, 1);
    // 将原先要写入到标准输出1中的数据，写入到指定文件中
    while(1) {
        do_face();
        //ls  >> a.txt
        int redirect = 0;
        char *file = NULL;
        char *ptr = buf;// 指令和参数都在buf中呢
        while(*ptr != '\0') {
            if (*ptr == '>') {
                redirect = 1;// 清空重定向
                *ptr++ = '\0';
                if (*ptr == '>') {
                    redirect = 2;// 追加重定向
                    *ptr++ = '\0';
                }
                while(isspace(*ptr) && *ptr != '\0') {// 找参数
                   ptr++; 
                }
                file = ptr;// 重定向符后的参数(参数应该是文件)地址
                while(!isspace(*ptr) && *ptr != '\0') {// 找尾
                   ptr++; 
                }
                *ptr = '\0';// 尾部设为'\0'
            }
            ptr++;
        }
        do_parse();
        int pid = fork();
        if (pid < 0) {
            exit(-1);
        }else if (pid == 0) {
            //重定向必须在子进程当中完成
            if (redirect == 1) {
                int fd = open(file, O_CREAT|O_WRONLY|O_TRUNC, 0664);// 打开文件,截断文件长度为0
                dup2(fd, 1);
            }else if (redirect == 2) {
                int fd = open(file, O_CREAT|O_WRONLY|O_APPEND, 0664);// 写追加模式
                dup2(fd, 1);
            }
            
            execvp(argv[0], argv);
            //防止子进程替换失败
            exit(0);
        }
        wait(NULL);
    }
    return 0;
}
