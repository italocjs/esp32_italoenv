#pragma once
#warning "Entrypoint Native"
// #include <stdio.h>

// int abstracted_main()
// {
//     printf("Hello World from PlatformIO!\n");
// 	return 0;
// }

#include <iostream>
#include <string>
#include <chrono>
#include <ctime>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <sys/utsname.h>
#endif

std::string getOperatingSystem()
{
#ifdef _WIN32
    return "Windows";
#else
    struct utsname buffer;
    if (uname(&buffer) == 0)
    {
        return std::string(buffer.sysname) + " " + buffer.release;
    }
    return "Unknown";
#endif
}

std::string getCurrentTime()
{
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    return std::ctime(&now_time);
}

void print_device_information()
{
    std::cout << "Operating System: " << getOperatingSystem() << std::endl;
    std::cout << "Current Time: " << getCurrentTime();

#ifdef _WIN32
    SYSTEM_INFO siSysInfo;
    GetSystemInfo(&siSysInfo);
    std::cout << "Processor Count: " << siSysInfo.dwNumberOfProcessors << std::endl;
    std::cout << "Page Size: " << siSysInfo.dwPageSize << " Bytes" << std::endl;
#else
    long nprocs = sysconf(_SC_NPROCESSORS_ONLN);
    long pagesize = sysconf(_SC_PAGESIZE);
    std::cout << "Processor Count: " << nprocs << std::endl;
    std::cout << "Page Size: " << pagesize << " Bytes" << std::endl;
#endif
}

int abstracted_main()
{
    std::cout << "Hello from Desktop Application!" << std::endl;
    print_device_information();
    return 0;
}