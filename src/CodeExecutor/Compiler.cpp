#include "CodeExecutor/Compiler.hpp"

const std::string& CodeExecutor::Compiler::standardOutput() const
{
    return m_stdout;
}

const std::string& CodeExecutor::Compiler::standardError() const
{
    return m_stderr;
}

void CodeExecutor::Compiler::setOutput(std::string output)
{
    m_stdout = std::move(output);
}

void CodeExecutor::Compiler::setError(std::string error)
{
    m_stderr = std::move(error);
}
