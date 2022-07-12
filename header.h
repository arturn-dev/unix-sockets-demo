#include <iostream>
#include <iomanip>
#include <chrono>

const char SOCKET_PATH[] = "/tmp/demo.sock";

auto timestamp()
{
    return std::chrono::high_resolution_clock::now().time_since_epoch().count();
}