#include "CertificateGenerator.hpp"
#include <filesystem>
#include <iostream>
#include <stdexcept>

namespace fs = std::filesystem;

/**
 * Constructs a CertificateGenerator with the specified command executor and CA details.
 * 
 * @param executor
 * @param caKey
 * @param caCert
 * @param caSerial
 * @param opensslConf
 */
CertificateGenerator::CertificateGenerator(
    std::shared_ptr<ICommandExecutor> executor,
    const std::string& caKey,
    const std::string& caCert,
    const std::string& caSerial,
    const std::string& opensslConf
) : executor_(executor),
    caCert_(caCert),
    caKey_(caKey),
    caSerial_(caSerial),
    opensslConf_(opensslConf)
{}

/**
 * Generates an RSA private key and saves it to the specified path.
 * 
 * @param path
 * @param bits
 */
void CertificateGenerator::generateKey(const std::string& path, int bits) {
    if (fs::is_directory(path)) {
        std::cout << "Warning: " << path << " is a directory, removing it.\n";
        fs::remove_all(path);
    }

    std::cout << "Generating RSA key: " << path << " (" << bits << " bits)...\n";

    std::string cmd = "openssl genpkey -algorithm RSA -out " + path + " -pkeyopt rsa_keygen_bits:" + std::to_string(bits);

    if (!executor_->execute(cmd)) {
        throw std::runtime_error("Failed to generate key: " + path);
    }

    fs::permissions(path, fs::perms::owner_read | fs::perms::owner_write);
}

/**
 * Generates an X.509 certificate signed by the CA using the specified private key.
 * 
 * @param keyPath
 * @param certPath
 * @param cn
 * @param extOpts
 */
void CertificateGenerator::generateCert(
    const std::string& keyPath,
    const std::string& certPath,
    const std::string& cn,
    const std::string& extOpts
) {
    std::cout << "Generating certificate: " << certPath << " with CN=" << cn << "...\n";
    std::string subj = "/C=RU/ST=Moscow/L=Moscow/O=Vladislav/OU=InitialStack/CN=" + cn + "/emailAddress=test@mail.ru";
    std::string cmd = "openssl req -new -sha256 -key " + keyPath + " -subj \"" + subj + "\" | "
                      "openssl x509 -req -sha256 "
                      "-CA " + caCert_ + " "
                      "-CAkey " + caKey_ + " "
                      "-CAserial " + caSerial_ + " "
                      "-CAcreateserial "
                      "-days 365 "
                      + extOpts + " "
                      "-out " + certPath;

    if (!executor_->execute(cmd)) {
        throw std::runtime_error("Failed to generate certificate: " + certPath);
    }

    fs::permissions(certPath, fs::perms::owner_read | fs::perms::group_read | fs::perms::others_read);
}

/**
 * Generates Diffie-Hellman parameters and saves them to the specified path.
 * 
 * @param path
 * @param bits
 */
void CertificateGenerator::generateDHParams(const std::string& path, int bits) {
    std::cout << "Generating Diffie-Hellman parameters (this may take a while)...\n";

    std::string cmd = "openssl dhparam -out " + path + " " + std::to_string(bits);

    if (!executor_->execute(cmd)) {
        throw std::runtime_error("Failed to generate DH parameters: " + path);
    }

    fs::permissions(path, fs::perms::owner_read | fs::perms::group_read | fs::perms::others_read);
}

/**
 * Generates a root Certificate Authority (CA) key, certificate, and serial file.
 * 
 * @param keyPath
 * @param certPath
 * @param serialPath
 */
void CertificateGenerator::generateCA(
    const std::string& keyPath,
    const std::string& certPath,
    const std::string& /*serialPath*/
) {
    fs::create_directories(fs::path(keyPath).parent_path());

    if (!fs::exists(keyPath)) {
        std::cout << "Generating root CA private key...\n";

        std::string cmd = "openssl genpkey -algorithm RSA -out " + keyPath + " -pkeyopt rsa_keygen_bits:4096";

        if (!executor_->execute(cmd)) {
            throw std::runtime_error("Failed to generate CA key");
        }

        fs::permissions(keyPath, fs::perms::owner_read | fs::perms::owner_write);
    } else {
        std::cout << "Root CA private key already exists, skipping.\n";
    }

    if (!fs::exists(certPath)) {
        std::cout << "Generating root CA certificate...\n";
        std::string cmd = "openssl req -x509 -new -nodes -sha256 "
                          "-key " + keyPath + " "
                          "-days 3650 "
                          "-subj \"/C=RU/ST=Moscow/L=Moscow/O=Vladislav/OU=InitialStack/CN=localhost/emailAddress=test@mail.ru\" "
                          "-out " + certPath;

        if (!executor_->execute(cmd)) {
            throw std::runtime_error("Failed to generate CA certificate");
        }

        fs::permissions(certPath, fs::perms::owner_read | fs::perms::group_read | fs::perms::others_read);
    } else {
        std::cout << "Root CA certificate already exists, skipping.\n";
    }
}
