#pragma once

#include "ICertificateGenerator.hpp"
#include "ICommandExecutor.hpp"

#include <memory>
#include <string>

class CertificateGenerator : public ICertificateGenerator {
    std::shared_ptr<ICommandExecutor> executor_;
    const std::string caCert_;      ///< Path to the CA certificate file
    const std::string caKey_;       ///< Path to the CA private key file
    const std::string caSerial_;    ///< Path to the CA serial file
    const std::string opensslConf_; ///< Path to the OpenSSL configuration file

public:
    /**
     * Constructs a CertificateGenerator with the specified command executor and CA details.
     * 
     * @param executor
     * @param caKey
     * @param caCert
     * @param caSerial
     * @param opensslConf
     */
    CertificateGenerator(std::shared_ptr<ICommandExecutor> executor,
        const std::string& caKey,
        const std::string& caCert,
        const std::string& caSerial,
        const std::string& opensslConf);

    /**
     * Generates a private key and saves it to the specified path.
     * 
     * @param path
     * @param bits
     */
    void generateKey(const std::string& path, int bits = 2048) override;

    /**
     * Generates a certificate signed by the CA using the specified key.
     * 
     * @param keyPath
     * @param certPath
     * @param cn
     * @param extOpts
     */
    void generateCert(
        const std::string& keyPath, const std::string& certPath,
        const std::string& cn, const std::string& extOpts = "") override;

    /**
     * Generates Diffie-Hellman parameters and saves them to the specified path.
     * 
     * @param path
     * @param bits
     */
    void generateDHParams(const std::string& path, int bits = 2048) override;

    /**
     * Generates a Certificate Authority (CA) key, certificate, and serial file.
     * 
     * @param keyPath
     * @param certPath
     * @param serialPath
     */
    void generateCA(
        const std::string& keyPath, const std::string& certPath,
        const std::string& serialPath) override;
};
