#include<iostream>
#include<arpa/inet.h>
#include<string.h>

using namespace std;

int main() {
    sockaddr_in sin;
    memset(&sin,0,sizeof(sockaddr_in));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(1234);
    inet_pton(AF_INET,"0.0.0.0",&sin.sin_addr);
    int fd = socket(AF_INET,SOCK_DGRAM,0);
    bind(fd,(sockaddr*)&sin,sizeof(sockaddr));

    char buff[1024];

    int size = sizeof(sin);

    recvfrom(fd,buff,1024,0,(sockaddr*)&sin,(socklen_t*)&size);

    sockaddr_in temp = sin;

    cout<<buff;

    recvfrom(fd,buff,1024,0,(sockaddr*)&sin,(socklen_t*)&size);
    sendto(fd,"world",6,0,(sockaddr*)&sin,sizeof(sin));

    cout<<buff;

    getchar();
    sendto(fd,"2被3代替了",64,0,(sockaddr*)&temp,sizeof(temp));

    return 0;
}