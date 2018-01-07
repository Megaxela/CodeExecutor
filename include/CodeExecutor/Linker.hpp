//
// Created by megaxela on 1/5/18.
//

#pragma once

#include <memory>
#include "Library.hpp"
#include "Object.hpp"

namespace CodeExecutor
{
    class Linker;

    using LinkerPtr = std::shared_ptr<Linker>;

    /**
     * @brief Class, that describes linker.
     */
    class Linker
    {
    public:

        /**
         * @brief Virtual destructor.
         */
        virtual ~Linker() = default;

        virtual LibraryPtr link(const std::vector<ObjectPtr>& objects) = 0;
    };
}

