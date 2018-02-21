#pragma once

#include <memory>
#include "filesystem.hpp"
#include <functional>
#include <dlfcn.h>

namespace CodeExecutor
{
    class Library;

    using LibraryPtr = std::shared_ptr<Library>;

    /**
     * @brief Class, that describes
     * library.
     */
    class Library
    {
    public:
        /**
         * @brief Default constructor.
         */
        Library();

        /**
         * @brief Constructor.
         */
        explicit Library(const std::filesystem::path& path);

        /**
         * @brief Destructor.
         */
        ~Library();

        /**
         * @brief Method for getting library path.
         * @return
         */
        std::filesystem::path path() const;

        /**
         * @brief Method for getting loading
         * error string.
         * @return Error string.
         */
        std::string errorString() const;

        /**
         * @brief Method for checking is library
         * loaded and ready to use.
         */
        bool isLoaded() const;

        /**
         * @brief Method for loading library.
         * @return Loading success.
         */
        bool load();

        /**
         * @brief Method for unloading library.
         * @return Unloading success.
         */
        bool unload();

        /**
         * @brief Method for resolving symbols.
         * @param name Symbol name.
         * @return
         */
        void* resolve(const char* name);

        /**
         * @brief Method for resolving symbols.
         * @tparam M Function type.
         * @param name
         * @return
         */
        template<class M>
        std::function<M> resolveFunction(const char* name)
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

            return std::function<M>((M*) result);
        };

    private:

        // Linux specific
        void* m_library;

        std::filesystem::path m_path;
        std::string m_errorString;
    };
}

