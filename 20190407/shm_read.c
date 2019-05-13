/*共享内存使用流程：
 *1. 创建/打开共享内存            shmget
    key_t ftok(const char *pathname, int proj_id);
        pathname:   文件名
        proj_id：   数字
        通过文件的inode节点号和proj_id共同得出一个key值
    int shmget(key_t key, size_t size, int shmflg);
        key:    共享内存标识符
        size：  共享内存大小
        shmflg：打开方式/创建权限
            IPC_CREAT   共享内存不存在则创建，存在则打开
            IPC_EXCL    与IPC_CREAT同用，若存在则报错，不存在则创建
            mode_flags  权限
    返回值：操作句柄shmid   失败：-1
 *2. 将共享内存映射到虚拟地址空间 shmat
    void *shmat(int shmid, const void *shmaddr, int shmflg);
        shmid:  创建共享内存返回的操作句柄
        shmaddr： 用于指定映射在虚拟地址空间的首地址；通常置NULL
        shmflg：    0--可读可写
    返回值：映射首地址（通过这个地址对共享内存进行操作） 失败：(void*)-1
 *3. 对共享内存进行基本的内存操作 memcpy.....
 *4. 解除映射关系                 shmdt
    int shmdt(const void *shmaddr);
        shmaddr:    映射返回的首地址
 *5. 删除共享内存                 shmctl
    int shmctl(int shmid, int cmd, struct shmid_ds *buf);
      shmid:  操作句柄
      cmd:    
          IPC_RMID    删除共享内存
      buf:    设置或者获取共享内存信息，用不着则置NULL
      共享内存并不是立即删除的，只是拒绝后续映射连接，当共享内存
      映射连接数为0时，则删除共享内存
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/shm.h>
#define IPC_KEY 0x12345678
#define PROJ_ID 12345
#define SHM_SIZE    4096
int main()
{
    int shmid;
    //1. 创建共享内存
    //key_t key = ftok(".", PROJ_ID);
    shmid = shmget(IPC_KEY, SHM_SIZE, IPC_CREAT|0666);
    if (shmid < 0) {
        perror("shmget error");
        return -1;
    }
    //2. 将共享内存映射到虚拟地址空间
    char *shm_start = (char *)shmat(shmid, NULL, 0);
    if (shm_start == (void*)-1) {
        perror("shmat error");
        return -1;
    }
    int i = 0;
    while(1) {
        printf("%s\n", shm_start);
        sleep(1);
    }
    //4. 解除映射
    shmdt(shm_start);
    //5. 删除共享内存
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
