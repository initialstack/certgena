#pragma once

#include "ICertificateGenerator.hpp"
#include "OpenSSLConfigCreator.hpp"

#include <memory>
#include <string>

class CertificateManager {
    std::shared_ptr<ICertificateGenerator> generator_; ///< Certificate generator instance
    OpenSSLConfigCreator configCreator_;               ///< Helper to create OpenSSL configuration files

public:
    /**
     * Constructs a CertificateManager with a certificate generator and OpenSSL config path.
     * 
     * @param gen
     * @param opensslConfPath
     */
    explicit CertificateManager(
        std::shared_ptr<ICertificateGenerator> gen,
        const std::string& opensslConfPath
    );

    /**
     * Executes the certificate management workflow.
     */
    void run();
};
