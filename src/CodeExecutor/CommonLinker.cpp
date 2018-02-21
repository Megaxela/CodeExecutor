#include "CodeExecutor/CommonLinker.hpp"

CodeExecutor::CommonLinker::CommonLinker(std::filesystem::path path) :
    m_path(std::move(path))
{

}

CodeExecutor::LibraryPtr CodeExecutor::CommonLinker::link(const std::vector<ObjectPtr>& objects)
{
    std::stringstream library_name;
    library_name << "exec_" << ++m_counter << ".so";

    Process process(m_path);

    Process::ArgumentsContainer arguments = {
        "-shared",
        "-fPIC",
        "-lc",
        "-o",
        library_name.str()
    };

    for (auto&& obj : objects)
    {
        arguments.emplace_back(obj->path());
    }

    process.setArguments(std::move(arguments));

    auto result = process.start();

    if (result != 0)
    {
        throw std::runtime_error("Can't perform linkage.");
    }

    auto currentPath = std::filesystem::current_path() / library_name.str();

    return std::make_shared<CodeExecutor::Library>(currentPath);
}
