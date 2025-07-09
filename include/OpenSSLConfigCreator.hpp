#pragma once

#include <string>

class OpenSSLConfigCreator {
    const std::string path_; ///< Path to the OpenSSL config file
public:
    /**
     * Constructs an OpenSSLConfigCreator with the target configuration file path.
     * 
     * @param path
     */
    explicit OpenSSLConfigCreator(std::string path);

    /**
     * Creates the OpenSSL configuration file at the specified path.
     */
    void create();
};
