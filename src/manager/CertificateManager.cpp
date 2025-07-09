#include "CertificateManager.hpp"

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

/**
 * Constructs a CertificateManager with the given certificate generator and OpenSSL config path.
 * @param gen
 * @param opensslConfPat
 */
CertificateManager::CertificateManager(
    std::shared_ptr<ICertificateGenerator> gen,
    const std::string& opensslConfPath
) : generator_(std::move(gen)),
    configCreator_(opensslConfPath) {}

/**
 * Runs the certificate generation workflow.
 */
void CertificateManager::run() {
    // Generate CA key, certificate, and serial file
    generator_->generateCA("certs/ca.key", "certs/ca.crt", "certs/ca.srl");
    // Create OpenSSL configuration file
    configCreator_.create();

    // Ensure 'certs' directory exists
    fs::create_directories("certs");

    // Generate nginx key and certificate
    generator_->generateKey("certs/server.key");
    generator_->generateCert(
        "certs/server.key",
        "certs/server.crt",
        "nginx",
        "-extfile certs/openssl.cnf -extensions server_cert"
    );

    // Generate client key and certificate
    generator_->generateKey("certs/client.key");
    generator_->generateCert(
        "certs/client.key",
        "certs/client.crt",
        "client",
        "-extfile certs/openssl.cnf -extensions client_cert"
    );

    // Generate postgres key and certificate
    generator_->generateKey("certs/postgres.key");
    generator_->generateCert(
        "certs/postgres.key",
        "certs/postgres.crt",
        "postgres",
        "-extfile certs/openssl.cnf -extensions server_cert"
    );

    // Generate rabbitmq key and certificate with read permissions for all
    generator_->generateKey("certs/rabbitmq.key");
    fs::permissions(
        "certs/rabbitmq.key",
        fs::perms::owner_read | fs::perms::group_read | fs::perms::others_read
    );
    generator_->generateCert(
        "certs/rabbitmq.key",
        "certs/rabbitmq.crt",
        "rabbitmq",
        "-extfile certs/openssl.cnf -extensions server_cert"
    );
    fs::permissions(
        "certs/rabbitmq.crt",
        fs::perms::owner_read | fs::perms::group_read | fs::perms::others_read
    );

    // Generate redis key and certificate with read permissions for all
    generator_->generateKey("certs/redis.key");
    fs::permissions(
        "certs/redis.key",
        fs::perms::owner_read | fs::perms::group_read | fs::perms::others_read
    );
    generator_->generateCert(
        "certs/redis.key",
        "certs/redis.crt",
        "redis",
        "-extfile certs/openssl.cnf -extensions server_cert"
    );
    fs::permissions(
        "certs/redis.crt",
        fs::perms::owner_read | fs::perms::group_read | fs::perms::others_read
    );

    // Generate Diffie-Hellman parameters for redis
    generator_->generateDHParams("certs/redis.dh");

    std::cout << "Certificate generation completed.\n";
}
