#ifdef _WIN32

#include "WinDNSResolver.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdexcept>

#pragma comment(lib, "ws2_32.lib")

WinDNSResolver::WinDNSResolver() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        throw std::runtime_error("WSAStartup failed");
}

WinDNSResolver::~WinDNSResolver() {
    WSACleanup();
}

std::vector<std::string> WinDNSResolver::resolveHostname(const std::string& hostname, bool verbose) {
    std::vector<std::string> results;
    struct addrinfo hints = {}, *res;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    int status = getaddrinfo(hostname.c_str(), nullptr, &hints, &res);
    if (status != 0)
        throw std::runtime_error("getaddrinfo failed");

    for (auto p = res; p != nullptr; p = p->ai_next) {
        char ipstr[INET6_ADDRSTRLEN];
        void* addr = (p->ai_family == AF_INET)
            ? (void*)&((struct sockaddr_in*)p->ai_addr)->sin_addr
            : (void*)&((struct sockaddr_in6*)p->ai_addr)->sin6_addr;

        inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
        results.emplace_back(ipstr);
    }

    freeaddrinfo(res);
    return results;
}

std::string WinDNSResolver::getCanonicalName(const std::string& hostname) {
    struct addrinfo hints = {}, *res;
    hints.ai_family = AF_UNSPEC;
    hints.ai_flags = AI_CANONNAME;

    int status = getaddrinfo(hostname.c_str(), nullptr, &hints, &res);
    if (status != 0)
        throw std::runtime_error("getaddrinfo failed");

    std::string cname = res->ai_canonname ? res->ai_canonname : "N/A";
    freeaddrinfo(res);
    return cname;
}

#endif
