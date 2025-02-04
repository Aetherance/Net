#include<iostream>
#include<arpa/inet.h>
#include<sys/un.h>
#include<string.h>
#include<unistd.h>
using namespace std;

int main() {

    int fd = socket(AF_UNIX,SOCK_STREAM,0);
    sockaddr_un sun;
    sun.sun_family = AF_UNIX;
    strcpy(sun.sun_path,"/tmp/sock");
    connect(fd,(sockaddr*)&sun,sizeof(sun));

    char buff[1024];

    read(fd,buff,1024);

    cout<<buff<<endl;

    return 0;
}