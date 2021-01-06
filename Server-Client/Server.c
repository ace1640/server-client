#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

#pragma comment(lib, "Ws2_32.lib")

int to_dec(char *str)
{
    int dec = 0;
    char buffer[100] = {0};

    while (*str && *str >= '0' && *str <= '9')
    {
        dec *= 10;
        dec += *(str)++ & 0xF;
    }

    return (dec);
}

int main(int argc, char **argv)
{

    char buffer[100] = {0};
    WSADATA wsa;
    SOCKET fd, client_fd;
    struct sockaddr_in socks = {0}, client = {0};
    size_t client_size = sizeof(client);

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        fprintf(stderr, "[-] Error startup winsock !\n");

    printf("[+] WSASTartup started successfully\n");

    if ((fd = WSASocketA(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, NULL, 0)) < 0)
        fprintf(stderr, "[-] Error to assign socket !\n");

    printf("[+] socket created !\n");

    socks.sin_addr.s_addr = INADDR_ANY;
    socks.sin_port = htons(to_dec(argv[1]));
    socks.sin_family = AF_INET;

    if (bind(fd, (struct sockaddr *)&socks, sizeof(socks)) < 0)
        fprintf(stderr, "[-] Error bind socket !\n");

    if (listen(fd, SOMAXCONN) < 0)
        fprintf(stderr, "[-] Error listen socket !\n");

    printf("[+] Listening on %s", argv[1]);

    for (;;)
    {
        client_fd = accept(fd, (struct sockaddr *)&client, &client_size);
        printf("[+] New client connected %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
        printf("[+] send hello to %s\n", inet_ntoa(client.sin_addr));

        send(client_fd, "hello", 5, 0);

        int bytes_recv = recv(client_fd, buffer, 99, 0);
        printf("%s\n", buffer);
        closesocket(client_fd);
        printf("[-] client disconnected %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
    }

    printf("[+] server closed !\n");
    closesocket(fd);

    return (EXIT_SUCCESS);
}