#include<iostream>
#include<arpa/inet.h>
#include<sys/epoll.h>
#include<memory.h>
using namespace std;

int main() {
    int lfd = socket(AF_INET,SOCK_STREAM,0);
    sockaddr_in sin;
    int sin_size = sizeof(sockaddr_in);
    memset(&sin,0,sin_size);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(4567);
    sin.sin_addr.s_addr = INADDR_ANY;
    if(bind(lfd,(sockaddr*)&sin,sizeof(sockaddr))!=0) {
        perror("bind");
    }
    listen(lfd,SOMAXCONN);
    cout<<"waiting"<<endl;
    int sock = accept(lfd,(sockaddr*)&sin,(socklen_t*)&sin_size);
    cout<<"connected"<<endl;

    int epfd = epoll_create(5);
    epoll_event ev;
    ev.events = EPOLLOUT;
    ev.data.fd = sock;

    epoll_ctl(epfd,EPOLL_CTL_ADD,sock,&ev);

    epoll_event rev[10];

    epoll_wait(epfd,rev,10,-1);


    return 0;
}