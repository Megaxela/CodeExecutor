//
// Created by megaxela on 1/5/18.
//

#include "CodeExecutor/BuildingContext.hpp"

CodeExecutor::BuildingContext::BuildingContext() :
    m_includeDirectories(),
    m_libraryDirectories(),
    m_libraries(),
    m_compileFlags(),
    m_defines()
{

}

CodeExecutor::BuildingContext::IncludeDirectoriesContainer::iterator
CodeExecutor::BuildingContext::includeDirectoriesBegin()
{
    return m_includeDirectories.begin();
}

CodeExecutor::BuildingContext::IncludeDirectoriesContainer::iterator
CodeExecutor::BuildingContext::includeDirectoriesEnd()
{
    return m_includeDirectories.end();
}

CodeExecutor::BuildingContext::IncludeDirectoriesContainer::const_iterator
CodeExecutor::BuildingContext::includeDirectoriesBegin() const
{
    return m_includeDirectories.begin();
}

CodeExecutor::BuildingContext::IncludeDirectoriesContainer::const_iterator
CodeExecutor::BuildingContext::includeDirectoriesEnd() const
{
    return m_includeDirectories.end();
}

void CodeExecutor::BuildingContext::addIncludeDirectory(CodeExecutor::BuildingContext::IncludeDirectoriesContainer::value_type path)
{
    m_includeDirectories.push_back(path);
}

CodeExecutor::BuildingContext::IncludeDirectoriesContainer::size_type
CodeExecutor::BuildingContext::countIncludeDirectories() const
{
    return m_includeDirectories.size();
}

CodeExecutor::BuildingContext::IncludeDirectoriesContainer::value_type
CodeExecutor::BuildingContext::includeDirectoryAt(const CodeExecutor::BuildingContext::IncludeDirectoriesContainer::size_type&& index) const
{
    return m_includeDirectories.at(index);
}


CodeExecutor::BuildingContext::LibraryDirectoriesContainer::iterator
CodeExecutor::BuildingContext::libraryDirectoriesBegin()
{
    return m_libraryDirectories.begin();
}

CodeExecutor::BuildingContext::LibraryDirectoriesContainer::iterator
CodeExecutor::BuildingContext::libraryDirectoriesEnd()
{
    return m_libraryDirectories.end();
}

CodeExecutor::BuildingContext::LibraryDirectoriesContainer::const_iterator
CodeExecutor::BuildingContext::libraryDirectoriesBegin() const
{
    return m_libraryDirectories.begin();
}

CodeExecutor::BuildingContext::LibraryDirectoriesContainer::const_iterator
CodeExecutor::BuildingContext::libraryDirectoriesEnd() const
{
    return m_libraryDirectories.end();
}

void CodeExecutor::BuildingContext::addLibraryDirectory(CodeExecutor::BuildingContext::LibraryDirectoriesContainer::value_type path)
{
    m_libraryDirectories.push_back(path);
}

CodeExecutor::BuildingContext::LibraryDirectoriesContainer::size_type
CodeExecutor::BuildingContext::countLibraryDirectories() const
{
    return m_libraryDirectories.size();
}

CodeExecutor::BuildingContext::LibraryDirectoriesContainer::value_type
CodeExecutor::BuildingContext::libraryDirectoryAt(const CodeExecutor::BuildingContext::IncludeDirectoriesContainer::size_type&& index) const
{
    return m_libraryDirectories.at(index);
}


CodeExecutor::BuildingContext::LibrariesContainer::iterator
CodeExecutor::BuildingContext::librariesBegin()
{
    return m_libraries.begin();
}

CodeExecutor::BuildingContext::LibrariesContainer::iterator
CodeExecutor::BuildingContext::librariesEnd()
{
    return m_libraries.end();
}

CodeExecutor::BuildingContext::LibrariesContainer::const_iterator
CodeExecutor::BuildingContext::librariesBegin() const
{
    return m_libraries.begin();
}

CodeExecutor::BuildingContext::LibrariesContainer::const_iterator
CodeExecutor::BuildingContext::librariesEnd() const
{
    return m_libraries.end();
}

void CodeExecutor::BuildingContext::addLibrary(CodeExecutor::BuildingContext::LibrariesContainer::value_type path)
{
    m_libraries.push_back(path);
}

CodeExecutor::BuildingContext::LibrariesContainer::size_type
CodeExecutor::BuildingContext::countLibraries() const
{
    return m_libraries.size();
}

CodeExecutor::BuildingContext::LibrariesContainer::value_type
CodeExecutor::BuildingContext::libraryAt(const CodeExecutor::BuildingContext::LibrariesContainer::size_type&& index) const
{
    return m_libraries.at(index);
}


CodeExecutor::BuildingContext::CompileFlagsContainer::iterator
CodeExecutor::BuildingContext::compileFlagsBegin()
{
    return m_compileFlags.begin();
}

CodeExecutor::BuildingContext::CompileFlagsContainer::iterator
CodeExecutor::BuildingContext::compileFlagsEnd()
{
    return m_compileFlags.end();
}

CodeExecutor::BuildingContext::CompileFlagsContainer::const_iterator
CodeExecutor::BuildingContext::compileFlagsBegin() const
{
    return m_compileFlags.begin();
}

CodeExecutor::BuildingContext::CompileFlagsContainer::const_iterator
CodeExecutor::BuildingContext::compileFlagsEnd() const
{
    return m_compileFlags.end();
}

void CodeExecutor::BuildingContext::addCompileFlag(CodeExecutor::BuildingContext::CompileFlagsContainer::value_type path)
{
    m_compileFlags.push_back(path);
}

CodeExecutor::BuildingContext::CompileFlagsContainer::size_type
CodeExecutor::BuildingContext::countCompileFlags() const
{
    return m_compileFlags.size();
}

CodeExecutor::BuildingContext::CompileFlagsContainer::value_type
CodeExecutor::BuildingContext::compileFlagAt(const CodeExecutor::BuildingContext::CompileFlagsContainer::size_type&& index) const
{
    return m_compileFlags.at(index);
}


CodeExecutor::BuildingContext::DefinesContainer::iterator
CodeExecutor::BuildingContext::definesBegin()
{
    return m_defines.begin();
}

CodeExecutor::BuildingContext::DefinesContainer::iterator
CodeExecutor::BuildingContext::definesEnd()
{
    return m_defines.end();
}

CodeExecutor::BuildingContext::DefinesContainer::const_iterator
CodeExecutor::BuildingContext::definesBegin() const
{
    return m_defines.begin();
}

CodeExecutor::BuildingContext::DefinesContainer::const_iterator
CodeExecutor::BuildingContext::definesEnd() const
{
    return m_defines.end();
}

void CodeExecutor::BuildingContext::addDefine(CodeExecutor::BuildingContext::DefinesContainer::value_type path)
{
    m_defines.push_back(path);
}

CodeExecutor::BuildingContext::DefinesContainer::size_type
CodeExecutor::BuildingContext::countDefines() const
{
    return m_defines.size();
}

CodeExecutor::BuildingContext::DefinesContainer::value_type
CodeExecutor::BuildingContext::defineAt(const CodeExecutor::BuildingContext::DefinesContainer::size_type&& index) const
{
    return m_defines.at(index);
}
