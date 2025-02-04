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

    char buff[1024];

    int size = sizeof(sin);

    sendto(fd,"This is 3",64,0,(sockaddr*)&sin,sizeof(sin));
    recvfrom(fd,buff,1024,0,(sockaddr*)&sin,(socklen_t*)&size);

    cout<<buff;

    return 0;
}