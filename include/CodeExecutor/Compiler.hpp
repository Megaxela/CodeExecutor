//
// Created by megaxela on 1/5/18.
//

#pragma once

#include <memory>
#include "Object.hpp"
#include "Source.hpp"
#include "BuildingContext.hpp"

namespace CodeExecutor
{
    class Compiler;

    using CompilerPtr = std::shared_ptr<Compiler>;

    /**
     * @brief Class, that describes
     * code compiler.
     */
    class Compiler
    {
    public:

        /**
         * @brief Destructor.
         */
        virtual ~Compiler() = default;

        /**
         * @brief Method, that used by builder
         * @param source
         * @param buildingContext
         * @return
         */
        virtual ObjectPtr compile(SourcePtr source,
                                  const std::filesystem::path& output,
                                  BuildingContextPtr buildingContext) = 0;
    };
}

