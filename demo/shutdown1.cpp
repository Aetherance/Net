#include<iostream>
#include<arpa/inet.h>
#include<memory.h>

using namespace std;

int main() {
    int lfd = socket(AF_INET,SOCK_STREAM,0);
    sockaddr_in sin;
    int sin_size = sizeof(sockaddr_in);
    memset(&sin,0,sin_size);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(1111);
    sin.sin_addr.s_addr = INADDR_ANY;
    if(bind(lfd,(sockaddr*)&sin,sizeof(sockaddr))!=0) {
        perror("bind");
    }
    listen(lfd,SOMAXCONN);
    cout<<"waiting"<<endl;
    int sock = accept(lfd,(sockaddr*)&sin,(socklen_t*)&sin_size);
    cout<<"connected"<<endl;

    send(sock,"hello",5,0);

    return 0;
}