#pragma once

#include "Compiler.hpp"
#include "Process.hpp"

namespace CodeExecutor
{
    /**
     * @brief Common compiler wrapper.
     */
    class CommonCompiler : public Compiler
    {
    public:

        /**
         * @brief Constructor.
         * @param pathToCompiler Path to `gcc` or `clang`.
         */
        explicit CommonCompiler(std::filesystem::path pathToCompiler);

        /**
         * @copydoc Compiler::compile
         */
        CodeExecutor::ObjectPtr compile(CodeExecutor::SourcePtr source,
                                        const std::filesystem::path& output,
                                        CodeExecutor::BuildingContextPtr buildingContext) override;

    private:
        std::filesystem::path m_path;
    };
}
