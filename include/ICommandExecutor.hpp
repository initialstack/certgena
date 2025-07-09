#pragma once

#include <string>

class ICommandExecutor {
public:
    virtual ~ICommandExecutor() = default;
    
    /**
     * Executes the given command string.
     * 
     * @param cmd
     * @return true
     */
    virtual bool execute(const std::string& cmd) = 0;
};
