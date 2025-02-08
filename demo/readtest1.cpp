#include<iostream>
#include<arpa/inet.h>
#include<memory.h>
#include<unistd.h>
#include<fcntl.h>
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

    int flags = fcntl(sock, F_GETFL, 0);    // 获取当前套接字标志
    fcntl(sock, F_SETFL, flags | O_NONBLOCK);  // 设置套接字为非阻塞模式

    while (true) {
        char buff[1024];
        if(read(sock,buff,1024) == 0)return -1;
        cout<<"read!"<<endl;
    }

    return 0;
}

// read()的确是阻塞的