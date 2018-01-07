//
// Created by megaxela on 1/5/18.
//

#include "CodeExecutor/Object.hpp"

CodeExecutor::Object::Object(const std::filesystem::path& file) :
    m_path(file)
{

}

std::filesystem::path CodeExecutor::Object::path() const
{
    return m_path;
}
