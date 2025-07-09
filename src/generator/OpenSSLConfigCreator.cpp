#include "OpenSSLConfigCreator.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

OpenSSLConfigCreator::OpenSSLConfigCreator(std::string path) : path_(std::move(path)) {}

/**
 * Creates the OpenSSL configuration file at the specified path.
 */
void OpenSSLConfigCreator::create() {
    // Ensure the directory for the config file exists
    fs::create_directories(fs::path(path_).parent_path());

    // Open the config file for writing
    std::ofstream conf(path_);
    if (!conf) {
        std::cerr << "Failed to create OpenSSL configuration file at " << path_ << "\n";
        return;
    }

    // Write OpenSSL configuration content
    conf <<
        "[ server_cert ]\n"
        "basicConstraints = CA:FALSE\n"
        "keyUsage = digitalSignature, keyEncipherment\n"
        "extendedKeyUsage = serverAuth\n"
        "subjectAltName = @alt_names\n\n"
        "[ client_cert ]\n"
        "basicConstraints = CA:FALSE\n"
        "keyUsage = digitalSignature, keyEncipherment\n"
        "extendedKeyUsage = clientAuth\n"
        "subjectAltName = @alt_names\n\n"
        "[ alt_names ]\n"
        "DNS.1 = localhost\n"
        "DNS.2 = nginx\n"
        "DNS.3 = redis\n"
        "DNS.4 = rabbitmq\n"
        "DNS.5 = postgres\n"
        "IP.1 = 127.0.0.1\n"
        "IP.2 = ::1\n";

    std::cout << "OpenSSL configuration created at " << path_ << "\n";
}
