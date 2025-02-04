#include<iostream>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

using namespace std;

int main() {
    sockaddr_in sin;
    // memset(&sin,0,sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(1234);
    inet_pton(AF_INET,"0.0.0.0",&sin.sin_addr);

    int lfd = socket(AF_INET,SOCK_DGRAM,0);

    bind(lfd,(sockaddr*)&sin,sizeof(sockaddr_in));

    // sleep(10);

    char buff[1024];

    int size = sizeof(sockaddr_in);

    recvfrom(lfd,buff,1024,0,(sockaddr*)&sin,(socklen_t*)&size);

    cout<<buff;

    return 0;
}