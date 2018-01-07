//
// Created by megaxela on 1/5/18.
//

#pragma once

#include "Compiler.hpp"
#include "Linker.hpp"
#include "Library.hpp"

namespace CodeExecutor
{
    /**
     * @brief Class, that describes object
     * that serves full process of building,
     * linkage and loading.
     */
    class Builder
    {
        // Source and it's object filename
        using BuildTarget = std::pair<SourcePtr, std::filesystem::path>;

        // Build targets
        using TargetsContainer = std::vector<BuildTarget>;

    public:
        /**
         * @brief Constructor.
         */
        Builder();

        /**
         * @brief Method for setting compiler.
         * @param compiler Compiler.
         */
        void setCompiler(CompilerPtr compiler);

        /**
         * @brief Method for getting smart ptr
         * to defined compiler.
         * @return Smart ptr to Compiler object.
         */
        CompilerPtr compiler() const;

        /**
         * @brief Method for setting linker.
         * @param linker Linker.
         */
        void setLinker(LinkerPtr linker);

        /**
         * @brief Method for getting smart ptr
         * to defined linker.
         * @return Smart ptr to Linker object.
         */
        LinkerPtr linker() const;

        /**
         * @brief Method for clearing all
         * build targets.
         */
        void clearTargets();

        /**
         * @brief Method for adding source file
         * for building. Object name will be
         * generated automatically from source data.
         * @param source Pointer to source object.
         */
        void addTarget(SourcePtr source);

        /**
         * @brief Method for adding source file
         * for building.
         * @param source Source object.
         * @param objectName Object file name. It must be
         * unique for every source. If this object name
         * already exists, std::invalid_argument execption
         * will be thrown.
         */
        void addTarget(SourcePtr source, std::filesystem::path objectName);

        /**
         * @brief Method for removing target source.
         * @param source Source object.
         */
        void removeTarget(SourcePtr source);

        /**
         * @brief Method for removing target by object name.
         * @param target Object name.
         */
        void removeTarget(const std::filesystem::path&& objectName);

        /**
         * @brief Method for getting current count of
         * available targets.
         * @return Number of targets.
         */
        TargetsContainer::size_type countTargets() const;

        /**
         * @brief Method for getting target source by index.
         * If index is out of range, std::out_of_range exception
         * will be thrown.
         * @param i Index.
         * @return Smart ptr to source object.
         */
        SourcePtr getTargetSourceAt(const TargetsContainer::size_type&& i) const;

        /**
         * @brief Method for getting target object name by index.
         * If index is our of range, std::out_of_range exception
         * will be thrown.
         * @param i Index.
         * @return Target object name.
         */
        std::filesystem::path getTargetObjectNameAt(const TargetsContainer::size_type&& i) const;

        /**
         * @brief Method for building targeted sources.
         * If building was not successful. std::runtime_error
         * will be thrown.
         * @todo Make custom exception type with fail stage
         * @return Built library.
         */
        LibraryPtr build() const;

        /**
         * @brief Method for setting building context.
         * @param context Smart pointer to building context.
         */
        void setBuildingContext(BuildingContextPtr context);

        /**
         * @brief Method for getting current building
         * context.
         * @return Building context.
         */
        BuildingContextPtr buildingContext() const;

    private:
        std::hash<std::string> m_hash;

        CompilerPtr m_compiler;
        LinkerPtr m_linker;

        TargetsContainer m_targets;
        BuildingContextPtr m_context;
    };
}
