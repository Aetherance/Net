#include<iostream>
#include<arpa/inet.h>
#include<sys/un.h>
#include<string.h>
#include<unistd.h>
using namespace std;

int main() {
    sockaddr_un sun;
    memset(&sun,0,sizeof(sockaddr_un));
    sun.sun_family = AF_UNIX;
    strcpy(sun.sun_path,"/tmp/sock");

    int sockfd = socket(AF_UNIX,SOCK_STREAM,0);

    bind(sockfd,(sockaddr*)&sun,sizeof(sun));

    listen(sockfd,3);

    int len = sizeof(sun);

    int new_fd = accept(sockfd,(sockaddr*)&sun,(socklen_t*)&len);

    string buff;

    getline(cin,buff);

    send(new_fd,buff.data(),1024,0);

    unlink("/tmp/sock");

    return 0;
}