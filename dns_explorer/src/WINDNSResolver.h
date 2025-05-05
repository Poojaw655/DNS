#ifndef WINDNSRESOLVER_H
#define WINDNSRESOLVER_H

#ifdef _WIN32

#include "IDNSResolver.h"

class WinDNSResolver : public IDNSResolver {
public:
    WinDNSResolver();
    ~WinDNSResolver();
    std::vector<std::string> resolveHostname(const std::string& hostname, bool verbose) override;
    std::string getCanonicalName(const std::string& hostname) override;
};

#endif
#endif
