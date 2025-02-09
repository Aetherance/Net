#include<iostream>
#include<arpa/inet.h>
#include<memory.h>
#include<sys/epoll.h>
using namespace std;

sockaddr_in addInit(unsigned int port) {
    sockaddr_in sin;
    memset(&sin,0,sizeof(sockaddr));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = INADDR_ANY;
    return sin;
}

int Listen(const sockaddr_in &sin,int back) {
    int lfd = socket(AF_INET,SOCK_STREAM,0);
    int bind_ret = bind(lfd,(sockaddr*)&sin,sizeof(sockaddr));
    if(bind_ret == -1) {
        perror("bind");
        return -1;
    }
    listen(lfd,back);
    return lfd;
}

int main() {
    sockaddr_in sin = addInit(1234);
    int lfd = Listen(sin,10);
    int epfd = epoll_create(10);
    epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = lfd;
    epoll_ctl(epfd,EPOLLIN,lfd,&ev);

    while (true) {
        epoll_event rev[10];
        int num_fds = epoll_wait(epfd,rev,10,-1);
        for(auto e : rev) {
            if(e.data.fd != lfd) {
                cout<<"deal with other tasks"<<endl;
            }
            else 
            {
                sockaddr_in csin;
                int size;
                int sock = accept(lfd,(sockaddr*)&csin,(socklen_t*)&size);
                char ip[16];
                inet_ntop(AF_INET,&csin.sin_addr,ip,sizeof(sin));
                cout<<"Client "<<ip<<":"<<ntohs(csin.sin_port)<<" connected!"<<endl;
            }
        }
     }
    

    return 0;
}