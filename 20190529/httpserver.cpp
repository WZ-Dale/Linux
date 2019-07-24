/*=============================================================== 
*   描    述：使用封装的tcpsocket完成实现一个最简单的http服务器 
*       返回一个简单页面:
*       <html><body><h1>Hello World</h1></body></html>
*       http是传输层协议，在传输层使用tcp协议实现；默认端口80
*       tcp服务器的基础上进行http协议数据的解析
*       http是一个短连接，在http1.1中实现了长连接
*       http数据的解析过程：
*           1. 获取http头部（首行+头部）
*               首行中包含url可以直到客户端请求什么资源，GET请求还可以获取到提交的数据
*               首行中包含的协议版本：拿到版本就可以针对不同版本的特性进行处理
*           2. 解析头部
*               可以获取到正文有多长，正文是什么类型的数据
*           3. 获取正文进行处理（通常将正文交给子进程处理）
*       问题：如何获取头部--如何保证获取一个完整的头部
*       MSG_PEEK
================================================================*/
#include <iostream>
#include <sstream>
#include "tcpsocket.hpp"

int main(int argc, char *argv[])
{
    if (argc != 3) {
        std::cout<< "./httpserver ip port\n";
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
        if (sock.Accept(clisock) == false) {
            continue;
        }
        std::string buf;
        clisock.Recv(buf);
        std::cout << "req:["<< buf <<"]\n";

        std::string body;
        body = "<html><body><h1>Hello World</h1></body></html>";
        std::stringstream ss;
        ss << "HTTP/1.1 502 Bad GateWay\r\n";
        ss << "Content-Length: " << body.size() <<"\r\n";
        ss << "Content-Type: text/html\r\n";
        ss << "Location: http://www.baidu.com\r\n";
        ss << "\r\n";
        std::string header = ss.str();

        clisock.Send(header);
        clisock.Send(body);
        clisock.Close();
    }
    sock.Close();
    return 0;
}

