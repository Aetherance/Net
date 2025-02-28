#include<iostream>
#include<arpa/inet.h>
#include<memory.h>
#include<unistd.h>
#include<fstream>
#include<fcntl.h>
using namespace std;

void response(int);
void receive(int);

int main() {
    int lfd = socket(AF_INET,SOCK_STREAM,0);
    sockaddr_in sin;
    memset(&sin,0,sizeof(sockaddr_in));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(8080);
    sin.sin_addr.s_addr = INADDR_ANY;
    if(bind(lfd,(sockaddr*)&sin,sizeof(sockaddr_in)) == -1) {
        perror("bind");
        exit(-1);
    };
    listen(lfd,1);
    sockaddr_in client_sin;
    socklen_t len = sizeof(sockaddr_in);
    int sock = accept(lfd,(sockaddr*)&client_sin,&len);
    receive(sock);
    response(sock);

    return 0;
}

void response(int sock) {
    char buff[10240] = {};
    string index(buff);
    int fd = open("/home/user/CODE/Net/http/index.html",O_RDONLY);
    int n = read(fd,buff,10240);
    buff[n] = '\0';
    string response = 
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html\r\n"
    "Content-Length: 50\r\n"
    "Connection: keep-alive\r\n"
    "\r\n"+
    index;

    send(sock,response.data(),response.size(),0);
}

void receive(int sock) {
    char buff[1024];
    read(sock,buff,1024);
    cout<<buff<<endl;
}