#include "Include.h"


SOCKET Connection;
std::string name;

void ShowMenu()
{
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
    std::cout << "@@@@@@@@@@       @@   @@     @@@@@     @@@      @@@     @@@@@    @@    @     @@@@     @@@@@    @@@@@       @@@@@@@@@@@@@" << std::endl;
    std::cout << "@@@@@@@@@@      @  @ @  @    @        @   @    @   @    @        @ @   @    @    @    @        @    @      @@@@@@@@@@@@@" << std::endl;
    std::cout << "@@@@@@@@@@      @   @   @    @        @        @        @        @  @  @    @         @        @    @      @@@@@@@@@@@@@" << std::endl;
    std::cout << "@@@@@@@@@@      @       @    @@@@@     @@       @@      @@@@@    @  @  @    @         @@@@@    @@@@@       @@@@@@@@@@@@@" << std::endl;
    std::cout << "@@@@@@@@@@      @       @    @           @        @     @        @  @  @    @  @@@    @        @ @         @@@@@@@@@@@@@" << std::endl;
    std::cout << "@@@@@@@@@@      @       @    @        @   @    @   @    @        @   @ @    @    @    @        @  @@       @@@@@@@@@@@@@" << std::endl;
    std::cout << "@@@@@@@@@@      @       @    @@@@@     @@@      @@@     @@@@@    @    @@     @@@@     @@@@@    @    @      @@@@@@@@@@@@@" << std::endl;
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
    std::cout << "@@@@@@@                     @@@@@@@@@@@@@@@@@@@                    @@@@@@@@@@@@@@@@@@@@@                       @@@@@@@@@" << std::endl;
    std::cout << "@@@@@@@  Created by: Artem  @@@@@@@@@@@@@@@@@@@  Press N to start  @@@@@@@@@@@@@@@@@@@@@  Press I to see info  @@@@@@@@" << std::endl;
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
    
}


void ClientHandler()
{
    char msg[256];
    while (true) {
        int bytesReceived = recv(Connection, msg, sizeof(msg), NULL);
        if (bytesReceived <= 0) {
            continue;
        }
        msg[bytesReceived] = '\0';

        // Перевірка, чи повідомлення не є власним
        std::string receivedMsg(msg);
        if (receivedMsg.find(name + ":") != 0) { 
            std::cout << receivedMsg << std::endl;
        }
    }
} 


int main() 
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
 
    ShowMenu();

    while (true) {
        char choice = _getch();
        if (choice == 'N' || choice == 'n' || choice == 'Т' || choice == 'т') {
            break;
        }
        else if (choice == 'I' || choice == 'i' || choice == 'Ш' || choice == 'ш') {
            std::cout << "HALLO NIGGA" << std::endl;
        }
    }

    WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if (WSAStartup(DLLVersion, &wsaData) != 0) {
        std::cout << "Error" << std::endl;
        exit(1);
    }

    SOCKADDR_IN addr;
    int sizeofaddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1111);
    addr.sin_family = AF_INET;

    Connection = socket(AF_INET, SOCK_STREAM, NULL);
    if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
        std::cout << "Error: failed to connect to server.\n";
        return 1;
    }
    std::cout << " " << std::endl;
    std::cout << "                                                      Connected!\n                                                      ";
    std::cout << " " << std::endl;
    std::cout << " " << std::endl;

    std::cout << "Введіть ваше Ім'я: ";
    std::getline(std::cin, name);

    CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, NULL, NULL, NULL);
    
      
    char msg1[256];
    while (true) {
        std::cin.getline(msg1, sizeof(msg1));
        std::string fullMsg = name + ": " + msg1;
        std::cout << fullMsg << std::endl;
        send(Connection, fullMsg.c_str(), fullMsg.size() + 1, NULL);
        Sleep(10);
    }
    

    /*         //test new
    char msg1[256];
    while (true) {
        std::cout << "Введіть ваше повідомлення: ";
        std::cin.getline(msg1, sizeof(msg1));

        std::string fullMsg = name + ": " + msg1;
        send(Connection, fullMsg.c_str(), fullMsg.size() + 1, NULL);
        Sleep(10);

        // Очищення рядка після вводу (робить консоль чистішою)
        std::cout << "\r\033[K";
    }
    */
    

    return 0;
}
