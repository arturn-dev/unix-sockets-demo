#include <unistd.h>

#include <sys/socket.h>
#include <sys/un.h>

#include "header.h"

int main()
{
    auto dataSocket = socket(AF_UNIX, SOCK_STREAM, 0);

    sockaddr_un sockAddr;
    sockAddr.sun_family = AF_UNIX;
    strncpy(sockAddr.sun_path, SOCKET_PATH, sizeof(sockAddr.sun_path) - 1);

    std::cout << timestamp() << " Calling connect()\n";
    connect(dataSocket, (sockaddr*)&sockAddr, sizeof(sockAddr));

    char buf[100] = {0};
    while(strcmp(buf, "STOP") != 0)
    {
        std::cin.getline(buf, sizeof(buf) - 1);
        std::cout << timestamp() << " Writing buffer\n";
        write(dataSocket, buf, sizeof(buf));
    }

    std::cout << timestamp() << " Closing data socket\n";

    close(dataSocket);

    return 0;
}