#ifndef IDNSRESOLVER_H
#define IDNSRESOLVER_H

#include <string>
#include <vector>

class IDNSResolver {
public:
    virtual ~IDNSResolver() = default;
    virtual std::vector<std::string> resolveHostname(const std::string& hostname, bool verbose) = 0;
    virtual std::string getCanonicalName(const std::string& hostname) = 0;
};

#endif
