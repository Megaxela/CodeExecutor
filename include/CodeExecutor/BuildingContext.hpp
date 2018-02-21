#pragma once

#include <memory>
#include <vector>
#include "filesystem.hpp"

namespace CodeExecutor
{
    class BuildingContext;

    using BuildingContextPtr = std::shared_ptr<BuildingContext>;

    /**
     * @brief Class, that describes building
     * context. It contains:
     *
     * - Include directories.
     * - Library directories.
     * - Libraries to link
     * - Compiler flags
     * - Defines
     */
    class BuildingContext
    {
        using IncludeDirectoriesContainer = std::vector<std::filesystem::path>;
        using LibraryDirectoriesContainer = std::vector<std::filesystem::path>;
        using LibrariesContainer = std::vector<std::string>;
        using CompileFlagsContainer = std::vector<std::string>;
        using DefinesContainer = std::vector<std::string>;

    public:

        /**
         * @brief Constructor.
         */
        BuildingContext();

        /**
         * @brief Virtual destructor.
         */
        virtual ~BuildingContext() = default;

        /**
         * @brief Method for getting include directories
         * non const begin iterator.
         * @return Include directories non const iterator.
         */
        IncludeDirectoriesContainer::iterator includeDirectoriesBegin();

        /**
         * @brief Method for getting include directories
         * non const end iterator.
         * @return Include directories non const iterator.
         */
        IncludeDirectoriesContainer::iterator includeDirectoriesEnd();

        /**
         * @brief Method for getting include directories
         * const begin iterator.
         * @return Include directories const iterator.
         */
        IncludeDirectoriesContainer::const_iterator includeDirectoriesBegin() const;

        /**
         * @brief Method for getting include directories
         * const end iterator.
         * @return Include directories const iterator.
         */
        IncludeDirectoriesContainer::const_iterator includeDirectoriesEnd() const;

        /**
         * @brief Method for adding include directory.
         * @param path Path to directory.
         */
        void addIncludeDirectory(IncludeDirectoriesContainer::value_type path);

        /**
         * @brief Method for getting count of include directories.
         * @return Count of include directories.
         */
        IncludeDirectoriesContainer::size_type countIncludeDirectories() const;

        /**
         * @brief Method for getting include directory by index.
         * If index is out of range, std::out_of_range exception will
         * be thrown.
         * @param index Index.
         * @return Include directory.
         */
        IncludeDirectoriesContainer::value_type includeDirectoryAt(const IncludeDirectoriesContainer::size_type&& index) const;

        /**
         * @brief Method for getting library directories
         * non const begin iterator.
         * @return Library directories non const iterator.
         */
        LibraryDirectoriesContainer::iterator libraryDirectoriesBegin();

        /**
         * @brief Method for getting library directories
         * non const end iterator.
         * @return Library directories non const iterator.
         */
        LibraryDirectoriesContainer::iterator libraryDirectoriesEnd();

        /**
         * @brief Method for getting library directories
         * const begin iterator.
         * @return Library directories const iterator.
         */
        LibraryDirectoriesContainer::const_iterator libraryDirectoriesBegin() const;

        /**
         * @brief Method for getting library directories
         * const end iterator.
         * @return Library directories const iterator.
         */
        LibraryDirectoriesContainer::const_iterator libraryDirectoriesEnd() const;

        /**
         * @brief Method for adding library directory.
         * @param path Path to directory.
         */
        void addLibraryDirectory(LibraryDirectoriesContainer::value_type path);

        /**
         * @brief Method for getting count of library directories.
         * @return Count of library directories.
         */
        LibraryDirectoriesContainer::size_type countLibraryDirectories() const;

        /**
         * @brief Method for getting library directory by index.
         * If index is out of range, std::out_of_range exception will
         * be thrown.
         * @param index Index.
         * @return Include directory.
         */
        LibraryDirectoriesContainer::value_type libraryDirectoryAt(const LibraryDirectoriesContainer::size_type&& index) const;

        /**
         * @brief Method for getting link libraries
         * non const begin iterator.
         * @return Libraries non const iterator.
         */
        LibrariesContainer::iterator librariesBegin();

        /**
         * @brief Method for getting link libraries
         * non const end iterator.
         * @return Libraries non const iterator.
         */
        LibrariesContainer::iterator librariesEnd();

        /**
         * @brief Method for getting link libraries
         * const begin iterator.
         * @return Library directories const iterator.
         */
        LibrariesContainer::const_iterator librariesBegin() const;

        /**
         * @brief Method for getting link libraries
         * const end iterator.
         * @return Library directories const iterator.
         */
        LibrariesContainer::const_iterator librariesEnd() const;

        /**
         * @brief Method for adding link library.
         * @param library Library.
         */
        void addLibrary(LibrariesContainer::value_type library);

        /**
         * @brief Method for getting count of link libraries.
         * @return Count of link libraries.
         */
        LibrariesContainer::size_type countLibraries() const;

        /**
         * @brief Method for getting link library by index.
         * If index is out of range, std::out_of_range exception will
         * be thrown.
         * @param index Index.
         * @return Include directory.
         */
        LibrariesContainer::value_type libraryAt(const LibrariesContainer::size_type&& index) const;

        /**
         * @brief Method for getting compile flags
         * non const begin iterator.
         * @return Compile flags non const iterator.
         */
        CompileFlagsContainer::iterator compileFlagsBegin();

        /**
         * @brief Method for getting compile flags
         * non const end iterator.
         * @return Compile flags non const iterator.
         */
        CompileFlagsContainer::iterator compileFlagsEnd();

        /**
         * @brief Method for getting compile flags
         * const begin iterator.
         * @return Compile flags const iterator.
         */
        CompileFlagsContainer::const_iterator compileFlagsBegin() const;

        /**
         * @brief Method for getting compile flags
         * const end iterator.
         * @return Compile flags const iterator.
         */
        CompileFlagsContainer::const_iterator compileFlagsEnd() const;

        /**
         * @brief Method for adding compile flag.
         * @param flag Flag.
         */
        void addCompileFlag(CompileFlagsContainer::value_type flag);

        /**
         * @brief Method for getting count of compile flags.
         * @return Count of compile flags.
         */
        CompileFlagsContainer::size_type countCompileFlags() const;

        /**
         * @brief Method for getting compile flag by index.
         * If index is out of range, std::out_of_range exception will
         * be thrown.
         * @param index Index.
         * @return Include directory.
         */
        CompileFlagsContainer::value_type compileFlagAt(const CompileFlagsContainer::size_type&& index) const;

        /**
         * @brief Method for getting defines
         * non const begin iterator.
         * @return Defines non const iterator.
         */
        DefinesContainer::iterator definesBegin();

        /**
         * @brief Method for getting defines
         * non const end iterator.
         * @return Defines non const iterator.
         */
        DefinesContainer::iterator definesEnd();

        /**
         * @brief Method for getting defines
         * const begin iterator.
         * @return Defines const iterator.
         */
        DefinesContainer::const_iterator definesBegin() const;

        /**
         * @brief Method for getting defines
         * const end iterator.
         * @return Defines const iterator.
         */
        DefinesContainer::const_iterator definesEnd() const;

        /**
         * @brief Method for adding define.
         * @param define Define.
         */
        void addDefine(DefinesContainer::value_type define);

        /**
         * @brief Method for getting count of defines.
         * @return Count of defines.
         */
        DefinesContainer::size_type countDefines() const;

        /**
         * @brief Method for getting define by index.
         * If index is out of range, std::out_of_range exception will
         * be thrown.
         * @param index Index.
         * @return Define.
         */
        DefinesContainer::value_type defineAt(const DefinesContainer::size_type&& index) const;

    private:

        IncludeDirectoriesContainer m_includeDirectories{};
        LibraryDirectoriesContainer m_libraryDirectories{};
        LibrariesContainer m_libraries{};
        CompileFlagsContainer m_compileFlags{};
        DefinesContainer m_defines{};

    };
}

