#include <unistd.h>

#include <sys/socket.h>
#include <sys/un.h>

#include "header.h"

int main()
{
    auto connectionSocket = socket(AF_UNIX, SOCK_STREAM, 0);

    sockaddr_un sockAddr;
    sockAddr.sun_family = AF_UNIX;
    strncpy(sockAddr.sun_path, SOCKET_PATH, sizeof(sockAddr.sun_path) - 1);

    bind(connectionSocket, (sockaddr*)&sockAddr, sizeof(sockAddr));

    listen(connectionSocket, 1); // listen to incoming connections

    std::cout << timestamp() << " Calling accept()\n";
    auto dataSocket = accept(connectionSocket, NULL, NULL); // accept incoming connection (block execution until connect() is invoked on the other side)
    std::cout << timestamp() << " accept() returned\n";

    char buf[100] = {0};
    do
    {
        std::cout << timestamp() << " Calling read()\n";
        auto noOfBytesRead = read(dataSocket, buf, sizeof(buf) - 1); // read incoming data from data socket
        std::cout << timestamp() << " read() returned\n";
        std::cout << timestamp() << " Data received: " << buf << std::endl;
    } while(strcmp(buf, "STOP") != 0);
    
    std::cout << timestamp() << " Closing connection\n";

    close(dataSocket);
    close(connectionSocket);
    unlink(SOCKET_PATH);

    return 0;
}