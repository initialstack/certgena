#include "OpenSSLExecutor.hpp"
#include "CertificateGenerator.hpp"
#include "CertificateManager.hpp"

#include <iostream>
#include <memory>
#include <cstdlib>

/**
 * Entry point of the certificate generation program.
 *
 * Usage:
 *   program_name [options]
 *
 * Options:
 *   -h, --help    Show this help message and exit.
 *
 * @param argc
 * @param argv
 * 
 * @return int
 */
int main(int argc, char* argv[]) {
    // Handle help option
    if (argc > 1) {
        std::string arg = argv[1];

        if (arg == "-h" || arg == "--help") {
            std::cout << "Usage: " << argv[0] << " [options]\n"
                      << "Options:\n"
                      << "  -h, --help      Show this help message and exit\n"
                      << "This program generates CA, keys, certificates, and DH params for nginx, redis, rabbitmq, and postgres.\n";

            return 0;
        }
    }

    // Check if OpenSSL is installed
    if (std::system("which openssl > /dev/null 2>&1") != 0) {
        std::cerr << "Error: openssl is not installed.\n";
        return 1;
    }

    // Create OpenSSL command executor
    auto executor = std::make_shared<OpenSSLExecutor>();

    // Create certificate generator with CA details and OpenSSL config path
    auto certGen = std::make_shared<CertificateGenerator>(
        executor,
        "certs/ca.key",
        "certs/ca.crt",
        "certs/ca.srl",
        "certs/openssl.cnf"
    );

    // Create certificate manager
    CertificateManager manager(certGen, "certs/openssl.cnf");

    // Run the certificate generation workflow with exception handling
    try {
        manager.run();
    }

    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
