#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <iostream>
#include <string>

#pragma comment(lib, "ws2_32.lib")
using namespace std;

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (sockaddr*)&server, sizeof(server));

    int choice;
    cout << "1. WRITE file\n2. READ file\nEnter choice: ";
    cin >> choice;
    cin.ignore(); // clear newline

    if (choice == 1) {
        string filename, data;
        cout << "Enter filename: ";
        getline(cin, filename);

        cout << "Enter text to write: ";
        getline(cin, data);

        string cmd = "WRITE " + filename;
        send(sock, cmd.c_str(), cmd.size(), 0);

        send(sock, data.c_str(), data.size(), 0);

        char buffer[1024] = {0};
        recv(sock, buffer, sizeof(buffer), 0);
        cout << "Server: " << buffer << endl;
    }
    else if (choice == 2) {
        string filename;
        cout << "Enter filename: ";
        getline(cin, filename);

        string cmd = "READ " + filename;
        send(sock, cmd.c_str(), cmd.size(), 0);

        char buffer[4096] = {0};
        recv(sock, buffer, sizeof(buffer), 0);

        cout << "\n--- File Content ---\n";
        cout << buffer << endl;
        cout << "--------------------\n";
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}
