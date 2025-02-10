#include<iostream>
#include<arpa/inet.h>
#include<memory.h>
#include<unistd.h>
using namespace std;

int main() {
    sockaddr_in sin;
    memset(&sin,0,sizeof(sockaddr_in));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(1234);
    sin.sin_addr.s_addr = INADDR_ANY;

    int lfd = socket(AF_INET,SOCK_STREAM,0);

    if(bind(lfd,(sockaddr*)&sin,sizeof(sockaddr))) {
        perror("bind");
    }

    listen(lfd,10);

    while (true) {
        char ip[16];
        sockaddr_in csin;
        int csin_size;
        int new_sock = accept(lfd,(sockaddr*)&csin,(socklen_t*)&csin_size);
        inet_ntop(AF_INET,&csin.sin_addr,ip,csin_size);
        cout<<"Client on "<<ip<<":"<<ntohs(csin.sin_port)<< " connected!"<<endl;
    }

    return 0;
}