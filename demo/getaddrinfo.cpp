#include<iostream>
#include<arpa/inet.h>
#include<netdb.h>
#include<memory.h>
using namespace std;

int main() {
    addrinfo info,* res;
    memset(&info,0,sizeof(addrinfo));
    info.ai_family = AF_INET;
    info.ai_socktype = SOCK_STREAM;
    getaddrinfo("127.0.0.1","1234",&info,&res);


    return 0;
}