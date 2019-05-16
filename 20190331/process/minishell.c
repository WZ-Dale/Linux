/*minishell实现*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    while(1) {
        printf("[wangze@localhost]$ ");
        fflush(stdout);// 刷新缓冲区
        char buf[1024] = {0};// 缓冲
        if (scanf("%[^\n]%*c", buf) != 1) {// scanf的返回值为正确匹配参数的个数
            getchar();// [^\n]正则表达式,*c忽略字符前的所有
        }
        // 解析流程：取出空白字符，获取程序名称和参数
        char *argv[32];
        int argc = 0;
        char *ptr = buf;
        while(*ptr != '\0') {
            // 当前位置非空白字符
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

        int pid = fork();
        if (pid < 0) {
            exit(-1);
        }else if (pid == 0) {
            execvp(argv[0], argv);// argv[0]中存放的是可执行文件的文件名,argv指向参数 
            //防止子进程替换失败
            exit(0);
        }
        wait(NULL);
    }
    return 0;
}
