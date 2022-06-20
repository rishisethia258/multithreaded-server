#include <bits/stdc++.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <limits.h>
using namespace std;

#define SERVERPORT 8989
#define BUFSIZE 4096
#define SOCKETERROR (-1)
#define SERVER_BACKLOG 1

typedef struct sockaddr_in SA_IN;
typedef struct sockaddr SA; 

void handle_connection(int client_socket);

int check(int exp, const char *msg)
{
    if (exp == SOCKETERROR)
    {
        perror(msg);
        exit(1);
    }
    return exp;
}

int main(int argc, char **argv)
{
    int server_socket, client_socket, addr_size;
    SA_IN server_addr, client_addr;

    check((server_socket = socket(AF_INET, SOCK_STREAM, 0)), "Failed to create the socket");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVERPORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    check((bind(server_socket, (SA *)&server_addr, sizeof(server_addr))), "Bind failed!");

    check(listen(server_socket, SERVER_BACKLOG), "Listen Failed");

    while (true)
    {
        cout << "Waiting for connections...\n";
        addr_size = sizeof(SA_IN);

        check(client_socket = accept(server_socket, (SA*)&server_addr, (socklen_t *)&addr_size), "ACCEPT FAILED");
        cout<<"Connected!\n";

        handle_connection(client_socket);
    }
    return 0;
}

void handle_connection(int client_socket)
{
    char buffer[BUFSIZE];
    size_t bytes_read;
    int msgsize = 0;               
    char actualpath[PATH_MAX + 1]; 

    while ((bytes_read = read(client_socket, buffer + msgsize, sizeof(buffer) - msgsize - 1)) > 0)
    {
        msgsize += bytes_read;
        if (msgsize > BUFSIZE - 1 || buffer[msgsize - 1] == '\n')
            break;
    }

    check(bytes_read, "recv error");
    buffer[msgsize - 1] = 0;

    cout << "REQUEST: " << buffer << endl;
    fflush(stdout);

    if (realpath(buffer, actualpath) == NULL)
    {
        cout << "ERROR(bad path " << buffer << "\n";
        close(client_socket);
        return;
    }

    FILE *fp = fopen(actualpath, "r");
    if (fp == NULL)
    {
        cout << "ERROR(open): " << buffer << endl;
        close(client_socket);
        return;
    }

    while ((bytes_read = fread(buffer, 1, BUFSIZE, fp)) > 0)
    {
        cout << "sending " << bytes_read << " bytes\n";
        write(client_socket, buffer, bytes_read);
    }
    close(client_socket);
    fclose(fp);
    cout << "Closing connection\n";
}
