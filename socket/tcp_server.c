#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>


#define PORT 6688
#define BACKLOG 1024
main() {

    //第一步： 创建socket,获得文件描述符
    //int socket(int domain, int type, int protocol);
    int mySocket = socket(AF_INET, SOCK_STREAM, 0);
    printf("mySocket: %d \n", mySocket);

    //第二步： 把IP和port绑定到刚创建的mySocket
    //int bind(int sockfd, const struct sockaddr *addr,socklen_t addrlen);
    struct sockaddr_in stSocketAddr = {0};
    stSocketAddr.sin_family = AF_INET;
    stSocketAddr.sin_port = htons(PORT); //网络用的是大端模式，x86系统用的是小端模式，需要进行大小端转换，所以要用htons()
    stSocketAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    int bid = bind(mySocket, (void *)&stSocketAddr, sizeof(stSocketAddr)); // (void *)的含义？ ==> 无类型指针，可以指向任何类型
    printf("bind_id: %d \n", bid);

    //第三步： 监听mySocket 连接建立的过程，也就是常说的三次握手
    //int listen(int sockfd, int backlog); backlog该如何设置？
    int lid = listen(mySocket, BACKLOG);
    printf("listen_id: %d \n", bid);

    //第四步： 获取内核已建立连接（完成3次握手）的请求
    // int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
    struct sockaddr_in stSocketAddrRemote = {0};
    int stSocketAddrRemoteLen = 0;
    while(1==1){
        //监听的socket和真正用来传递数据的socket, 是不一样的。一个是上面创建的mySocket, 一个是下面的aid
        int aid = accept(mySocket, (void *)&stSocketAddrRemote, &stSocketAddrRemoteLen);
        //inet_ntoa 如何将数字转换为IP?
        printf("accept_id: %d, remote_ip %s, remote_port %d, sockLen %d \n", aid, inet_ntoa(stSocketAddrRemote.sin_addr), ntohs(stSocketAddrRemote.sin_port), stSocketAddrRemoteLen);
    }
    


}