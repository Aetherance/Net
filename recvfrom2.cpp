#include<iostream>
#include<arpa/inet.h>
#include<string.h>

using namespace std;

int main() {
    sockaddr_in sin;
    memset(&sin,0,sizeof(sockaddr_in));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(1234);
    inet_pton(AF_INET,"127.0.0.1",&sin.sin_addr);


    int fd = socket(AF_INET,SOCK_DGRAM,0);
    sendto(fd,"connect",10,0,(sockaddr*)&sin,sizeof(sockaddr_in));

    sendto(fd,"Hi",5,0,(sockaddr*)&sin,sizeof(sockaddr_in));

    return 0;
}