#include<iostream>
#include<arpa/inet.h>
#include<memory.h>

int main() {
    sockaddr_in sin;
    memset(&sin,0,sizeof(sockaddr_in));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(1234);
    inet_pton(AF_INET,"localhost",&sin.sin_addr);

    int sock = socket(AF_INET,SOCK_STREAM,0);

    connect(sock,(sockaddr*)&sin,sizeof(sockaddr_in));

    char buff[13] = {};

    recv(sock,buff,13,0);
    std::cout<<buff;    

    return 0;
}