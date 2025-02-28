#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string>
#include <sstream>
#include <vector>
#include <bitset>

// 完整的SHA-1实现
std::string sha1(const std::string& input) {
    uint32_t h0 = 0x67452301;
    uint32_t h1 = 0xEFCDAB89;
    uint32_t h2 = 0x98BADCFE;
    uint32_t h3 = 0x10325476;
    uint32_t h4 = 0xC3D2E1F0;

    // 消息填充
    uint64_t ml = input.size() * 8;
    std::string data = input;
    data += (char)0x80;
    while ((data.size() * 8) % 512 != 448) data += (char)0x00;
    for (int i = 7; i >= 0; --i) data += (char)((ml >> (i * 8)) & 0xFF);

    // 处理分块
    for (size_t i = 0; i < data.size(); i += 64) {
        uint32_t w[80]{0};
        for (int t = 0; t < 16; ++t) {
            w[t] = (data[i + t*4] << 24) | (data[i + t*4 +1] << 16) 
                 | (data[i + t*4 +2] << 8) | data[i + t*4 +3];
        }
        for (int t = 16; t < 80; ++t) {
            w[t] = (w[t-3] ^ w[t-8] ^ w[t-14] ^ w[t-16]);
            w[t] = (w[t] << 1) | (w[t] >> 31);
        }

        uint32_t a = h0, b = h1, c = h2, d = h3, e = h4;

        for (int t = 0; t < 80; ++t) {
            uint32_t f, k;
            if (t < 20) {
                f = (b & c) | ((~b) & d);
                k = 0x5A827999;
            } else if (t < 40) {
                f = b ^ c ^ d;
                k = 0x6ED9EBA1;
            } else if (t < 60) {
                f = (b & c) | (b & d) | (c & d);
                k = 0x8F1BBCDC;
            } else {
                f = b ^ c ^ d;
                k = 0xCA62C1D6;
            }

            uint32_t temp = ((a << 5) | (a >> 27)) + f + e + k + w[t];
            e = d;
            d = c;
            c = (b << 30) | (b >> 2);
            b = a;
            a = temp;
        }

        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
    }

    // 组合结果
    std::string hash;
    for (auto h : {h0, h1, h2, h3, h4}) {
        for (int i = 24; i >= 0; i -= 8) {
            hash += (char)((h >> i) & 0xFF);
        }
    }
    return hash;
}

// Base64编码实现
std::string base64_encode(const std::string& in) {
    const std::string base64_chars = 
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";
    
    std::string out;
    int val = 0, valb = -6;
    
    for (unsigned char c : in) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            out.push_back(base64_chars[(val>>valb)&0x3F]);
            valb -= 6;
        }
    }
    
    if (valb > -6)
        out.push_back(base64_chars[((val<<8)>>(valb+8))&0x3F]);
    
    while (out.size()%4)
        out.push_back('=');
    
    return out;
}

// WebSocket握手响应生成
std::string create_handshake_response(const std::string& client_key) {
    const std::string magic = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
    std::string combined = client_key + magic;
    std::string hash = sha1(combined);
    return base64_encode(hash);
}

// 构建WebSocket数据帧
std::string create_websocket_frame(const std::string& message) {
    std::string frame;
    
    // FIN + Text frame
    frame.push_back(0x81);
    
    // 处理长度
    if (message.size() <= 125) {
        frame.push_back(message.size());
    } else if (message.size() <= 65535) {
        frame.push_back(126);
        frame.push_back((message.size() >> 8) & 0xFF);
        frame.push_back(message.size() & 0xFF);
    }
    
    frame += message;
    return frame;
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in address;
    const int PORT = 8080;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 5);

    std::cout << "WebSocket server running on port " << PORT << std::endl;

    while (true) {
        sockaddr_in client_addr;
        socklen_t addr_len = sizeof(client_addr);
        int client_socket = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);

        char buffer[1024] = {0};
        read(client_socket, buffer, 1024);

        std::string request(buffer);
        size_t key_start = request.find("Sec-WebSocket-Key: ") + 19;
        size_t key_end = request.find("\r\n", key_start);
        std::string client_key = request.substr(key_start, key_end - key_start);

        std::string accept_key = create_handshake_response(client_key);
        
        std::string response = 
            "HTTP/1.1 101 Switching Protocols\r\n"
            "Upgrade: websocket\r\n"
            "Connection: Upgrade\r\n"
            "Sec-WebSocket-Accept: " + accept_key + "\r\n\r\n";

        send(client_socket, response.c_str(), response.size(), 0);

        // 发送测试消息
        std::string message = "Hello World";
        std::string frame = create_websocket_frame(message);
        send(client_socket, frame.c_str(), frame.size(), 0);

        close(client_socket);
    }

    close(server_fd);
    return 0;
}