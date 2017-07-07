# tcp_ip协议栈（网络进程间通信）
循序渐进学习TCP网络编程<br>
## 准备<br>
[套接字及套接字接口函数](https://github.com/liuchenjane/tcp_ip/blob/master/%E5%A5%97%E6%8E%A5%E5%AD%97.md)<br>

## 1. 基本的TCP/IP服务器端和客户端<br>
<br>
服务器端一直监听本地的6666号端口，如果收到连接请求，将接收请求并接收客户端发来的消息；<br>
客户端与服务器建立连接并发送一条消息。<br>
<br>

[TCP server实现](https://github.com/liuchenjane/tcp_ip/blob/master/tcp_ip/server.cpp) <br>
[TCP client实现](https://github.com/liuchenjane/tcp_ip/blob/master/tcp_ip/client.cpp) <br>

## 2. TCP协议选项带有超时设置的TCP/IP <br>
SO_SNDTIMEO, SO_RCVTIMEO 会分别设置socket的发送和接收超时时间<br>

[client中通过setsocketopt设置TCP选项](https://github.com/liuchenjane/tcp_ip/blob/master/tcp_ip6.2/client.cpp)<br>
[server实现](https://github.com/liuchenjane/tcp_ip/blob/master/tcp_ip6.2/server.cpp)<br>

