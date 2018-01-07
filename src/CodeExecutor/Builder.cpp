//
// Created by megaxela on 1/5/18.
//

#include <algorithm>
#include "CodeExecutor/Builder.hpp"

CodeExecutor::Builder::Builder() :
    m_compiler(nullptr),
    m_linker(nullptr),
    m_targets(),
    m_context()
{

}

void CodeExecutor::Builder::setCompiler(CodeExecutor::CompilerPtr compiler)
{
    m_compiler = std::move(compiler);
}

CodeExecutor::CompilerPtr CodeExecutor::Builder::compiler() const
{
    return m_compiler;
}

void CodeExecutor::Builder::setLinker(CodeExecutor::LinkerPtr linker)
{
    m_linker = std::move(linker);
}

CodeExecutor::LinkerPtr CodeExecutor::Builder::linker() const
{
    return m_linker;
}

void CodeExecutor::Builder::clearTargets()
{
    m_targets.clear();
}

void CodeExecutor::Builder::addTarget(CodeExecutor::SourcePtr source)
{
    m_targets.emplace_back(
        source,
       std::to_string(m_hash(source->content()))
    );
}

void CodeExecutor::Builder::addTarget(CodeExecutor::SourcePtr source, std::filesystem::path objectName)
{
    m_targets.emplace_back(source, objectName);
}

void CodeExecutor::Builder::removeTarget(CodeExecutor::SourcePtr source)
{
    auto result = std::find_if(
        m_targets.begin(),
        m_targets.end(),
        [source](const BuildTarget& code)
        {
            return code.first == source;
        }
    );

    if (result == m_targets.end())
    {
        return;
    }

    m_targets.erase(result);
}

void CodeExecutor::Builder::removeTarget(const std::filesystem::path&& objectName)
{
    auto result = std::find_if(
        m_targets.begin(),
        m_targets.end(),
        [objectName](const BuildTarget& code)
        {
            return code.second == objectName;
        }
    );

    if (result == m_targets.end())
    {
        return;
    }

    m_targets.erase(result);
}

unsigned long CodeExecutor::Builder::countTargets() const
{
    return m_targets.size();
}

CodeExecutor::SourcePtr CodeExecutor::Builder::getTargetSourceAt(const TargetsContainer::size_type&& i) const
{
    return m_targets.at(i).first;
}

std::filesystem::path CodeExecutor::Builder::getTargetObjectNameAt(const TargetsContainer::size_type&& i) const
{
    return m_targets.at(i).second;
}

void CodeExecutor::Builder::setBuildingContext(CodeExecutor::BuildingContextPtr context)
{
    m_context = std::move(context);
}

CodeExecutor::BuildingContextPtr CodeExecutor::Builder::buildingContext() const
{
    return m_context;
}

CodeExecutor::LibraryPtr CodeExecutor::Builder::build() const
{
    if (m_compiler == nullptr)
    {
        throw std::runtime_error("No compiler specified");
    }

    if (m_linker == nullptr)
    {
        throw std::runtime_error("No linker specified");
    }

    std::vector<ObjectPtr> objects;

    for (auto&& target : m_targets)
    {
        objects.push_back(m_compiler->compile(
            target.first,
            target.second,
            m_context
        ));
    }

    return m_linker->link(objects);
}
