#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include"threadpool"

using namespace std;

void talk(int new_sock) {
    while(true) {
        char buff[102400];
        cin>>buff;
        if(strcmp(buff,"cls") == 0) {
            system("clear");
        }
        send(new_sock,buff,1024,0);
    }
}

void receive(int new_sock) {
    while (true) {
        char buff[1024000];
        if(read(new_sock,buff,102400))
            cout<<"远方的朋友:  "<<buff<<endl;
        if(strcmp(buff,"cls") == 0) {
            system("clear");
        }
    }
}

int main() {
    threadpool pool(2);
    sockaddr_in add;
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    add.sin_family = AF_INET;
    add.sin_addr.s_addr = INADDR_ANY;
    add.sin_port = (htons(25565));
    
    bind(sockfd,(sockaddr*)&add,sizeof(add));

    listen(sockfd,3);

    int addlen = sizeof(add);

    cout<<"server waiting"<<endl;
   
    int new_sock = accept(sockfd,(sockaddr*)&add,(socklen_t*)&addlen);
    cout<<"send message to client:";
    if(new_sock == -1) {
        perror("accept error\n");
        return -1;
    }
    

    pool.submit([new_sock](){
        talk(new_sock);
    });

    pool.submit([new_sock](){
        receive(new_sock);
    });

    pool.stop();

    return 0;
}