#pragma once

#include <memory>
#include "filesystem.hpp"

namespace CodeExecutor
{
    class Object;

    using ObjectPtr = std::shared_ptr<Object>;

    /**
     * @brief Class, that describes object file.
     */
    class Object
    {
    public:
        /**
         * @brief Constructor.
         * @param file Path to object file.
         */
        explicit Object(const std::filesystem::path& file);

        /**
         * @brief Method for getting path to the
         * object file.
         * @return Path to object file.
         */
        std::filesystem::path path() const;

    private:

        std::filesystem::path m_path;

    };
}

