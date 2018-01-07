//
// Created by megaxela on 1/5/18.
//

#include "CodeExecutor/Source.hpp"

CodeExecutor::SourcePtr CodeExecutor::Source::createFromSource(std::string content)
{
    auto source = std::make_shared<Source>(std::move(content), HideArg());

    return source;
}

std::string CodeExecutor::Source::content() const
{
    return m_content;
}

CodeExecutor::Source::Source(std::string content, HideArg) :
    m_content(std::move(content))
{

}
