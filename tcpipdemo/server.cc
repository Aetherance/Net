#include<iostream>
#include<memory.h>
#include<arpa/inet.h>

int main() {
    int lfd = socket(AF_INET,SOCK_STREAM,0);
    sockaddr_in sin;
    memset(&sin,0,sizeof(sockaddr_in));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(1234);
    sin.sin_addr.s_addr = INADDR_ANY;
    
    if(bind(lfd,(sockaddr*)&sin,sizeof(sockaddr_in)) == -1) {
        perror("bind");
    }

    listen(lfd,3);

    sockaddr_in client_sin;
    socklen_t client_sin_len = sizeof(sockaddr_in);
    int sock = accept(lfd,(sockaddr*)&client_sin,&client_sin_len);

    send(sock,"Hello World!",13,0);

    return 0;
}