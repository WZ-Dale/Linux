/*=============================================================== 
 *   描    述：基于封装的TcpSocket类完成tcp服务端程序 
 *       1. 创建套接字
 *       2. 绑定地址信息
 *       3. 开始监听
 *       4. 获取已经连接成功的客户端socket
 *       5. 接收数据
 *       6. 发送数据
 *       7. 关闭套接字
 ================================================================*/

#include <iostream>
#include "tcpsocket.hpp"

int main(int argc, char *argv[])
{
  if (argc != 3) {
    printf("./tcp_srv ip  port\n");
    return -1;
  }
  std::string ip = argv[1];
  uint16_t port = atoi(argv[2]);

  TcpSocket sock;
  CHECK_RET(sock.Socket());
  CHECK_RET(sock.Bind(ip, port));
  CHECK_RET(sock.Listen());

  while(1) {
    TcpSocket clisock;
    struct sockaddr_in cliaddr;
    //accept是阻塞获取已经完成的连接
    if (sock.Accept(clisock, &cliaddr) == false) {
      continue;
    }
    printf("new connect client:%s:%d\n", 
        inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));

    int fd = clisock.GetSockFd();
    calculator_info info;

    recv(fd, &info, sizeof(calculator_info), 0);
    printf("num1:[%d] %c num2[%d] = [%d]\n", info.num1, info.op,
        info.num2, info.num1 + info.num2);
  }
  sock.Close();
  return 0;
}
