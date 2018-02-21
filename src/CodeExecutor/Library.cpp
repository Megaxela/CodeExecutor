#include "CodeExecutor/Library.hpp"

CodeExecutor::Library::Library() :
    m_library(nullptr),
    m_path(),
    m_errorString()
{

}

CodeExecutor::Library::Library(const std::filesystem::path& path) :
    m_library(dlopen(path.string().c_str(), RTLD_LAZY)),
    m_path(path),
    m_errorString()
{
    auto errorString = dlerror();
    if (errorString)
    {
        m_errorString = errorString;
    }
}

CodeExecutor::Library::~Library()
{
    if (m_library)
    {
        dlclose(m_library);
    }
}

std::filesystem::path CodeExecutor::Library::path() const
{
    return m_path;
}

std::string CodeExecutor::Library::errorString() const
{
    return m_errorString;
}

bool CodeExecutor::Library::isLoaded() const
{
    return m_library != nullptr;
}

bool CodeExecutor::Library::load()
{
    return false;
}

bool CodeExecutor::Library::unload()
{
    return false;
}

void* CodeExecutor::Library::resolve(const char* name)
{
    if (m_library == nullptr)
    {
        return nullptr;
    }

    auto result = dlsym(m_library, name);
    auto errorString = dlerror();
    if (errorString)
    {
        m_errorString = errorString;
        return nullptr;
    }

    return result;
}
