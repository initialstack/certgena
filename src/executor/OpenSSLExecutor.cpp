#include "OpenSSLExecutor.hpp"

#include <iostream>
#include <cstdlib>

/**
 * Executes the given command string using the system shell.
 * 
 * @param cmd
 * @return true
 */
bool OpenSSLExecutor::execute(const std::string& cmd) {
    std::cout << "Executing: " << cmd << std::endl;
    int ret = std::system(cmd.c_str());
    
    return ret == 0;
}
