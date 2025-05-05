#include "DNSResolverFactory.h"

#ifdef _WIN32
#include "WinDNSResolver.h"
#else
#include "POSIXDNSResolver.h"
#endif

IDNSResolver* DNSResolverFactory::createResolver() {
#ifdef _WIN32
    return new WinDNSResolver();
#else
    return new POSIXDNSResolver();
#endif
}
