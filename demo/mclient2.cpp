#include<iostream>
#include<arpa/inet.h>
#include<memory.h>
using namespace std;


int main() {
    sockaddr_in sin;
    memset(&sin,0,sizeof(sockaddr));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(1234);
    inet_pton(AF_INET,"localhost",&sin.sin_addr);

    int fd = socket(AF_INET,SOCK_STREAM,0);

    connect(fd,(sockaddr*)&sin,sizeof(sockaddr));

    while (true)
    {
        getchar();
        send(fd,"hello",6,0);
    }
    

    return 0;
}
