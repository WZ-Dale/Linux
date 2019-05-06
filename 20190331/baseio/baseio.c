/*标准库IO接口*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int ret;
    FILE *fp = NULL;
    fp = fopen("./tmp.txt", "r+");
    if (fp == NULL) {
        perror("fopen error");
        return -1;
    }
    fseek(fp, 10, SEEK_END);

    char *ptr = "nihao ~~!!\n";
    //size_t fwrite(void *ptr, size_t size, size_t nmemb,FILE *stream);
    ret = fwrite(ptr, strlen(ptr), 1, fp);
    printf("write item:%d\n", ret);

    fseek(fp, 0, SEEK_SET);
    char buf[1024] = {0};

    //size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
    ret = fread(buf, 1023, 1, fp);
    perror("fread error");
    printf("read buf:[%s]-ret:[%d]\n", buf, ret);

    fclose(fp);
    return 0;
}
