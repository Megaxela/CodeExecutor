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
         * @param source Smart pointer to source object.
         * @param buildingContext Building context.
         * @return Smart pointer to object
         */
        virtual ObjectPtr compile(SourcePtr source,
                                  const std::filesystem::path& output,
                                  BuildingContextPtr buildingContext) = 0;

        /**
         * @brief Method for getting standard output
         * string.
         * @return Standard output.
         */
        const std::string& standardOutput() const;

        /**
         * @brief Method for getting standard error
         * string.
         * @return Standard error.
         */
        const std::string& standardError() const;

    protected:

        void setOutput(std::string output);

        void setError(std::string error);

    private:

        std::string m_stdout;
        std::string m_stderr;

    };
}

