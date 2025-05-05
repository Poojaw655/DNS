#ifndef DNSRESOLVERFACTORY_H
#define DNSRESOLVERFACTORY_H

#include "IDNSResolver.h"

class DNSResolverFactory {
public:
    static IDNSResolver* createResolver();
};

#endif
