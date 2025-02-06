#include<iostream>
#include<arpa/inet.h>
#include<unistd.h>

using namespace std;

int main() {
    int lfd = socket(AF_INET6,SOCK_STREAM,0);

    sockaddr_in6 sin6;
    sin6.sin6_family = AF_INET6;
    sin6.sin6_port = htons(6666);
    sin6.sin6_flowinfo = 0;
    sin6.sin6_scope_id = 0;
    inet_pton(AF_INET6,"::",&sin6.sin6_addr);

    bind(lfd,(sockaddr*)&sin6,sizeof(sin6));

    listen(lfd,3);

    int size = sizeof(sin6);

    int new_fd = accept(lfd,(sockaddr*)&sin6,(socklen_t*)&size);

    send(new_fd,"Hello world!",1024,0);
    send(new_fd,"This is a test",1024,0);
    send(new_fd,"This is a longggggggggggggggggggggggg test",1024,0);
    

    return 0;
}