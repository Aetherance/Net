#include<iostream>
#include<arpa/inet.h>
#include<memory.h>
#include<fcntl.h>
#include<unistd.h>
using namespace std;

int main() {
    int fd = socket(AF_INET,SOCK_STREAM,0);
    sockaddr_in sin;
    int sin_size = sizeof(sockaddr_in);
    memset(&sin,0,sin_size);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(4567);
    inet_pton(AF_INET,"localhost",&sin.sin_addr);

    connect(fd,(sockaddr*)&sin,sin_size);
    int new_file = open("../sendfile_result",O_WRONLY|O_CREAT|O_TRUNC,0644);
    
    char buff[1024];
    memset(buff,0,sizeof(buff));
    int recv_size = 0;

    while ((recv_size = recv(fd,buff,sizeof(buff),0)) > 0) {
        write(new_file,buff,recv_size);
    }
    
    close(new_file);
    close(fd);

    return 0;
}