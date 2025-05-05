#ifndef POSIXDNSRESOLVER_H
#define POSIXDNSRESOLVER_H

#ifndef _WIN32

#include "IDNSResolver.h"

class POSIXDNSResolver : public IDNSResolver {
public:
    std::vector<std::string> resolveHostname(const std::string& hostname, bool verbose) override;
    std::string getCanonicalName(const std::string& hostname) override;
};

#endif
#endif
