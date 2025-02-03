#include<iostream>
#include<arpa/inet.h>
using namespace std;

int main() {
    struct in_addr ip_addr;
    inet_pton(AF_INET,"192.168.0.1",&ip_addr);
    unsigned long ip = ip_addr.s_addr;

    cout<<ip<<endl;

    cout<<htonl(ip)<<endl;

    cout<<ntohl(htonl(ip))<<endl;

    return 0;   
}