#pragma once

#include <string>

class ICertificateGenerator {
public:
    virtual ~ICertificateGenerator() = default;

    /**
     * Generates a private key and saves it to the specified path.
     * 
     * @param path
     * @param bits
     */
    virtual void generateKey(const std::string& path, int bits = 2048) = 0;

    /**
     * Generates a certificate signed by a CA using the specified private key.
     * @param keyPath
     * @param certPath
     * @param cn
     * @param extOpts
     */
    virtual void generateCert(
        const std::string& keyPath, const std::string& certPath,
        const std::string& cn, const std::string& extOpts = "") = 0;

    /**
     * Generates Diffie-Hellman parameters and saves them to the specified path.
     * 
     * @param path
     * @param bits
     */
    virtual void generateDHParams(const std::string& path, int bits = 2048) = 0;

    /**
     * Generates a Certificate Authority (CA) key, certificate, and serial file.
     * 
     * @param keyPath
     * @param certPath
     * @param serialPath
     */
    virtual void generateCA(
        const std::string& keyPath, const std::string& certPath,
        const std::string& serialPath) = 0;
};