#pragma once

#include "ICommandExecutor.hpp"

class OpenSSLExecutor : public ICommandExecutor {
public:
    /**
     * Executes the given command string using the system shell.
     * 
     * @param cmd
     * @return true
     */
    bool execute(const std::string& cmd) override;
};
