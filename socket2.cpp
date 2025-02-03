#include<iostream>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>

using namespace std;

int main() {
    int sock = socket(AF_INET,SOCK_STREAM,0);

    sockaddr_in add;
    add.sin_family = AF_INET;
    add.sin_port = htons(59281);

    inet_pton(AF_INET,"103.8.71.176",&add.sin_addr);

    if(connect(sock,(sockaddr*)&add,sizeof(add)) == -1){
        perror("没连上\n");
        return -1;
    };

    char buff[1024];

    read(sock,buff,1024);

    cout<<buff<<endl;

    read(sock,buff,1024);

    cout<<buff<<endl;

    cout<<"Yes"<<endl;

    return 0;
}