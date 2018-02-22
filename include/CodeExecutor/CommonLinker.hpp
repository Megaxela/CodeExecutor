#pragma once

#include "Linker.hpp"
#include "Process.hpp"

namespace CodeExecutor
{
    /**
     * @brief Class, that describes common
     * linker for `gcc` or `clang`.
     */
    class CommonLinker : public Linker
    {
    public:

        /**
         * @brief Linker constructor.
         * @param path Path to linker (`gcc` or `clang`)
         */
        explicit CommonLinker(std::filesystem::path path);

        /**
         * @copydoc Linker::link
         */
        LibraryPtr link(const std::vector<ObjectPtr>& objects) override;

    private:
        std::filesystem::path m_path;
        int m_counter = 0;
    };
}

