#include<iostream>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

using namespace std;

int main() {
    int fd = socket(AF_INET6,SOCK_STREAM,0);

    sockaddr_in6 sin6;
    memset(&sin6,0,sizeof(sockaddr_in6));
    sin6.sin6_family = AF_INET6;
    sin6.sin6_port = htons(6666);
    inet_pton(AF_INET6,"::1",&sin6.sin6_addr);

    connect(fd,(sockaddr*)&sin6,sizeof(sin6));

    char buff[1024];
    read(fd,buff,1024);
    cout<<buff<<endl;

    read(fd,buff,1024);
    cout<<buff<<endl;
    
    read(fd,buff,1024);
    cout<<buff<<endl;

    return 0;
}