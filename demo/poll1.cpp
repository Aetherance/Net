#include<iostream>
#include<arpa/inet.h>
#include<memory.h>
#include<poll.h>

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
    sockaddr csin;
    int size_csin = sizeof(csin);
    int sock = accept(lfd,(sockaddr*)&csin,(socklen_t*)&csin);
    
    if(sock == -1){
        perror("accept");
    }
    cout<<"connected"<<endl;

    pollfd fds[10];
    fds[0].fd = sock;
    fds[0].events = POLLIN;
    
    poll(fds,1,-1);

    cout<<"poll over"<<endl;


    return 0;
}