#include<iostream>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include"threadpool"

using namespace std;

void talk(int new_sock) {
    while(true) {
        char buff[102400];
        cin>>buff;
        if(strcmp(buff,"cls") == 0) {
            system("clear");
        }
        send(new_sock,buff,1024,0);
    }
}

void receive(int new_sock) {
    while (true) {
        char buff[1024000];
        if(read(new_sock,buff,102400))
            cout<<"远方的朋友:  "<<buff<<endl;
        if(strcmp(buff,"cls") == 0) {
            system("clear");
        }
    }
}

int main() {
    threadpool pool(2);
    
    int sock = socket(AF_INET,SOCK_STREAM,0);

    sockaddr_in add;
    add.sin_family = AF_INET;
    add.sin_port = htons(59281);

    inet_pton(AF_INET,"103.8.71.176",&add.sin_addr);

    cout<<"等待连接..."<<endl;
    
    while(connect(sock,(sockaddr*)&add,sizeof(add)) == -1){
        cout<<"waiting"<<endl;
    };

    pool.submit([sock](){
        receive(sock);
    });

    pool.submit([sock](){
        talk(sock);
    });
    
    pool.stop();

    return 0;
}