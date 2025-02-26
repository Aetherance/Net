#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>

void handle_request(int client_socket) {
    char buffer[1024] = {0};
    read(client_socket, buffer, 1024);

    std::string response;
    if (std::string(buffer).find("GET /") != std::string::npos) {
        // 完全转义的HTML字符串
        // std::string html = 
        //     "<!DOCTYPE html>\n"
        //     "<html>\n"
        //     "<head>\n"
        //     "    <title>Button Demo</title>\n"
        //     "</head>\n"
        //     "<body>\n"
        //     "    <button onclick=\"sendRequest()\">Click Me</button>\n"
        //     "    <script>\n"
        //     "        function sendRequest() {\n"
        //     "            fetch('/message', { method: 'POST' })\n"
        //     "                .then(response => response.text())\n"
        //     "                .then(text => alert('Response: ' + text))\n"
        //     "                .catch(error => console.error('Error:', error));\n"
        //     "        }\n"
        //     "    </script>\n"
        //     "</body>\n"
        //     "</html>";
        std::string html = 
    "<!DOCTYPE html>\n"
    "<html>\n"
    "<head>\n"
    "    <title>Button Demo</title>\n"
    "    <style>\n"
    "        body { \n"
    "            font-family: Arial, sans-serif;\n"
    "            display: flex;\n"
    "            flex-direction: column;\n"
    "            align-items: center;\n"
    "            padding: 20px;\n"
    "        }\n"
    "        button {\n"
    "            padding: 12px 24px;\n"
    "            font-size: 16px;\n"
    "            background: #007bff;\n"
    "            color: white;\n"
    "            border: none;\n"
    "            border-radius: 4px;\n"
    "            cursor: pointer;\n"
    "            margin: 20px;\n"
    "        }\n"
    "        #result {\n"
    "            margin-top: 20px;\n"
    "            padding: 15px;\n"
    "            border: 1px solid #ddd;\n"
    "            border-radius: 4px;\n"
    "            min-width: 200px;\n"
    "            text-align: center;\n"
    "            background: #f8f9fa;\n"
    "            transition: opacity 0.3s;\n"
    "        }\n"
    "        .success {\n"
    "            color: #155724;\n"
    "            background-color: #d4edda;\n"
    "            border-color: #c3e6cb;\n"
    "        }\n"
    "        .error {\n"
    "            color: #721c24;\n"
    "            background-color: #f8d7da;\n"
    "            border-color: #f5c6cb;\n"
    "        }\n"
    "    </style>\n"
    "</head>\n"
    "<body>\n"
    "    <button onclick=\"sendRequest()\">Get Message</button>\n"
    "    <div id=\"result\"></div>\n"
    "    <script>\n"
    "        function sendRequest() {\n"
    "            const resultDiv = document.getElementById('result');\n"
    "            resultDiv.style.opacity = '1';\n"
    "            \n"
    "            fetch('/message', { method: 'POST' })\n"
    "                .then(response => {\n"
    "                    if (!response.ok) throw new Error('Network error');\n"
    "                    return response.text();\n"
    "                })\n"
    "                .then(text => {\n"
    "                    resultDiv.className = 'success';\n"
    "                    resultDiv.innerHTML = `\n"
    "                        <div>Server Response:</div>\n"
    "                        <div style='margin-top:8px;font-weight:bold;'>${text}</div>\n"
    "                    `;\n"
    "                    setTimeout(() => {\n"
    "                        resultDiv.style.opacity = '0';\n"
    "                    }, 2000);\n"
    "                })\n"
    "                .catch(error => {\n"
    "                    resultDiv.className = 'error';\n"
    "                    resultDiv.textContent = 'Error: ' + error.message;\n"
    "                });\n"
    "        }\n"
    "    </script>\n"
    "</body>\n"
    "</html>";

        response = 
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: " + std::to_string(html.size()) + "\r\n\r\n" + html;
    }
    else if (std::string(buffer).find("POST /message") != std::string::npos) {
        response = 
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n"
            "Content-Length: 11\r\n\r\n"
            "Hello World";
    }
    else {
        response = 
            "HTTP/1.1 404 Not Found\r\n"
            "Content-Length: 0\r\n\r\n";
    }

    send(client_socket, response.c_str(), response.size(), 0);
    close(client_socket);
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    bind(server_fd, (sockaddr*)&address, sizeof(address));
    listen(server_fd, 5);

    std::cout << "Server running on http://localhost:8080" << std::endl;

    while (true) {
        int client_socket = accept(server_fd, nullptr, nullptr);
        std::thread(handle_request, client_socket).detach();
    }

    close(server_fd);
    return 0;
}