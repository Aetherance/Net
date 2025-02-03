#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>

using namespace std;

int main() {
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

    char buff[1024];
    cin>>buff;

    send(new_sock,buff,1024,0);

    char test[1024] = "会不会覆盖？";

    send(new_sock,test,1024,0);

    return 0;
}