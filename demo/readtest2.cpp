#include<iostream>
#include<arpa/inet.h>
#include<memory.h>
#include<unistd.h>
using namespace std;

int main() {
    int lfd = socket(AF_INET,SOCK_STREAM,0);
    sockaddr_in sin;
    int sin_size = sizeof(sockaddr_in);
    memset(&sin,0,sin_size);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(4567);
    sin.sin_addr.s_addr = INADDR_ANY;
    connect(lfd,(sockaddr*)&sin,sizeof(sin));

    sleep(100);

    return 0;
}