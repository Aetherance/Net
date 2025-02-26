#include<iostream>
#include<arpa/inet.h>
#include<memory.h>
#include<sys/epoll.h>
#include<fcntl.h>
#include<unistd.h>
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

void setNOBLOCK(int fd) {
    int FLAG = fcntl(fd,F_GETFL);
    fcntl(fd,F_SETFL,FLAG|O_NONBLOCK);
}

int main() {
    sockaddr_in sin = addInit(1234);
    int lfd = Listen(sin,10);
    int epfd = epoll_create(10);
    epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = lfd;
    epoll_ctl(epfd,EPOLL_CTL_ADD,lfd,&ev);
    setNOBLOCK(lfd);
    while (true) {
        epoll_event rev[10];
        int num_fds = epoll_wait(epfd,rev,10,-1);
        for(int i = 0;i<num_fds;i++) {
            if(rev[i].data.fd != lfd) {
                cout<<"doing"<<endl;
                usleep(100000);
                char buff[1024];
                int r_ret;
                if((r_ret = read(rev[i].data.fd,buff,1024)) == 0) {
                    sockaddr_in csin;
                    int size;
                    getpeername(rev[i].data.fd,(sockaddr*)&csin,(socklen_t*)&size);
                    char ip[16];
                    inet_ntop(AF_INET,&csin.sin_addr,ip,sizeof(csin));
                    cout<<"Client "<<ip<<":"<<ntohs(csin.sin_port)<<" exited!"<<endl;
                    close(rev[i].data.fd);
                    epoll_ctl(epfd, EPOLL_CTL_DEL, rev[i].data.fd, NULL);
                }
                else if(r_ret > 0){
                    cout<<buff;
                }
            }
            else 
            {
                sockaddr_in csin;
                int size;
                int sock = accept(lfd,(sockaddr*)&csin,(socklen_t*)&size);
                if(sock == -1) {
                    continue;
                }
                char ip[16];
                inet_ntop(AF_INET,&csin.sin_addr,ip,sizeof(csin));
                cout<<"Client "<<ip<<":"<<ntohs(csin.sin_port)<<" connected!"<<endl;
                epoll_event ev;
                ev.data.fd = sock;
                ev.events = EPOLLIN;
                setNOBLOCK(sock);
                epoll_ctl(epfd,EPOLL_CTL_ADD,sock,&ev);
            }
        }
     }
    

    return 0;
}