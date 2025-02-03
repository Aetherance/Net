搞清楚网络!!!

# 大小端序转换函数

定义在<arpa/inet.h>中的四个函数 

`uint16_t htons(uint16_t host_uint16_t);`

将16位无符号短整数从主机字节序转换为网络字节序。(通常转换端口号)

`uint32_t htonl(uint32_t host_uint32_t);`

将32位无符号长整数从主机字节序转换位网络字节序。(通常转换IP地址)

`uint16_t ntohs(uint16_t net_uint16_t);` 和 `uint32_t ntohl(uint32_t net_uint32_t);` 