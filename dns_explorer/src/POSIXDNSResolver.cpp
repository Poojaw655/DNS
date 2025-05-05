#ifndef _WIN32

#include "POSIXDNSResolver.h"
#include <netdb.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <cstring>

std::vector<std::string> POSIXDNSResolver::resolveHostname(const std::string& hostname, bool verbose) {
    std::vector<std::string> results;
    struct addrinfo hints = {}, *res;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    int status = getaddrinfo(hostname.c_str(), nullptr, &hints, &res);
    if (status != 0)
        throw std::runtime_error(gai_strerror(status));

    for (auto p = res; p != nullptr; p = p->ai_next) {
        char ipstr[INET6_ADDRSTRLEN];
        void* addr = nullptr;

        if (p->ai_family == AF_INET)
            addr = &((struct sockaddr_in*)p->ai_addr)->sin_addr;
        else
            addr = &((struct sockaddr_in6*)p->ai_addr)->sin6_addr;

        inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
        results.emplace_back(ipstr);
    }

    freeaddrinfo(res);
    return results;
}

std::string POSIXDNSResolver::getCanonicalName(const std::string& hostname) {
    struct addrinfo hints = {}, *res;
    hints.ai_family = AF_UNSPEC;
    hints.ai_flags = AI_CANONNAME;

    int status = getaddrinfo(hostname.c_str(), nullptr, &hints, &res);
    if (status != 0)
        throw std::runtime_error(gai_strerror(status));

    std::string cname = res->ai_canonname ? res->ai_canonname : "N/A";
    freeaddrinfo(res);
    return cname;
}

#endif
