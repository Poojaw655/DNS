#include "DNSResolverFactory.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <hostname>" << std::endl;
        return 1;
    }

    std::string hostname = argv[1];
    bool verbose = (argc > 2 && std::string(argv[2]) == "--verbose");

    try {
        IDNSResolver* resolver = DNSResolverFactory::createResolver();

        std::cout << "IP Addresses for " << hostname << ":\n";
        for (const auto& ip : resolver->resolveHostname(hostname, verbose))
            std::cout << " - " << ip << "\n";

        std::cout << "Canonical Name: " << resolver->getCanonicalName(hostname) << "\n";
        delete resolver;
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return 2;
    }

    return 0;
}