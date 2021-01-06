
#include <stdio.h>
#include <winsock2.h>

int main(int argc, char **argv)
{
    char buffer[100] = {0};
    SOCKET fd;
    struct sockaddr_in sock = {0}, server = {0};
    WSADATA wsa;
    size_t server_size = sizeof(server);

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        fprintf(stderr, "[-] Error to initialize Winsock2\n");

    if ((fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        fprintf(stderr, "[-] Error to initialize the socket !\n");

    sock.sin_addr.s_addr = inet_addr(argv[1]);
    sock.sin_port = htons(5555);
    sock.sin_family = AF_INET;

    if (WSAConnect(fd, (struct sockaddr *)&sock, sizeof(sock), NULL, NULL, NULL, NULL) < 0)
        fprintf(stderr, "[-] Error to connect to remote host\n");

    int i = recv(fd, buffer, sizeof(buffer) - 1, 0);

    printf("%s", buffer);

    int dd = send(fd, "world", 6, 0);
}