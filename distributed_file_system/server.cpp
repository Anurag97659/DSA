#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

struct FileMeta {
    bool locked;
};

unordered_map<string, FileMeta> metadata;
CRITICAL_SECTION meta_lock;

DWORD WINAPI handle_client(LPVOID lpParam) {
    SOCKET client_socket = (SOCKET)lpParam;
    char buffer[1024] = {0};

    recv(client_socket, buffer, sizeof(buffer), 0);
    string request(buffer);

    size_t pos = request.find(" ");
    if (pos == string::npos) {
        closesocket(client_socket);
        return 0;
    }

    string command = request.substr(0, pos);
    string filename = request.substr(pos + 1);

    if (command == "READ") {
        ifstream file(filename);
        if (!file) {
            string msg = "File not found";
            send(client_socket, msg.c_str(), msg.size(), 0);
        } else {
            string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
            send(client_socket, content.c_str(), content.size(), 0);
        }
    }
    else if (command == "WRITE") {
        EnterCriticalSection(&meta_lock);
        if (metadata[filename].locked) {
            LeaveCriticalSection(&meta_lock);
            string msg = "File is locked";
            send(client_socket, msg.c_str(), msg.size(), 0);
            closesocket(client_socket);
            return 0;
        }
        metadata[filename].locked = true;
        LeaveCriticalSection(&meta_lock);

        memset(buffer, 0, sizeof(buffer));
        recv(client_socket, buffer, sizeof(buffer), 0);

        ofstream file(filename);
        file << buffer;
        file.close();

        EnterCriticalSection(&meta_lock);
        metadata[filename].locked = false;
        LeaveCriticalSection(&meta_lock);

        string msg = "Write successful";
        send(client_socket, msg.c_str(), msg.size(), 0);
    }
    else {
        string msg = "Invalid command";
        send(client_socket, msg.c_str(), msg.size(), 0);
    }

    closesocket(client_socket);
    return 0;
}

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    InitializeCriticalSection(&meta_lock);

    SOCKET server_fd = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    bind(server_fd, (sockaddr*)&address, sizeof(address));
    listen(server_fd, 5);

    cout << "DFS Server running on port 8080 (Windows)" << endl;

    while (true) {
        SOCKET client_socket = accept(server_fd, NULL, NULL);
        CreateThread(NULL, 0, handle_client, (LPVOID)client_socket, 0, NULL);
    }

    DeleteCriticalSection(&meta_lock);
    closesocket(server_fd);
    WSACleanup();
    return 0;
}
