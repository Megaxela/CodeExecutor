#include "CodeExecutor/CommonCompiler.hpp"

CodeExecutor::CommonCompiler::CommonCompiler(std::filesystem::path pathToCompiler) :
    m_path(std::move(pathToCompiler))
{

}

CodeExecutor::ObjectPtr
CodeExecutor::CommonCompiler::compile(CodeExecutor::SourcePtr source,
                                      const std::filesystem::path& output,
                                      CodeExecutor::BuildingContextPtr buildingContext)
{
    Process process(m_path);

    Process::ArgumentsContainer arguments;

    if (buildingContext)
    {
        for (auto iterator = buildingContext->includeDirectoriesBegin(),
                  end = buildingContext->includeDirectoriesEnd();
             iterator != end;
             ++iterator)
        {
            arguments.push_back(" -I" + iterator->string());
        }

        for (auto iterator = buildingContext->libraryDirectoriesBegin(),
                  end = buildingContext->libraryDirectoriesEnd();
             iterator != end;
             ++iterator)
        {
            arguments.push_back(" -L" + iterator->string());
        }

        for (auto iterator = buildingContext->librariesBegin(),
                  end = buildingContext->librariesEnd();
             iterator != end;
             ++iterator)
        {
            arguments.push_back(" -l" + *iterator);
        }

        for (auto iterator = buildingContext->definesBegin(),
                  end = buildingContext->definesEnd();
             iterator != end;
             ++iterator)
        {
            arguments.push_back(" -D" + *iterator);
        }

        for (auto iterator = buildingContext->compileFlagsBegin(),
                  end = buildingContext->compileFlagsEnd();
             iterator != end;
             ++iterator)
        {
            arguments.push_back(*iterator);
        }
    }

    std::string tail[] = {
        "-fPIC",
        "-o",
        output,
        "-c",
        "-xc++",
        "-"
    };

    arguments.insert(arguments.end(), tail, tail + 6);

    process.setArguments(std::move(arguments));

    process.setInputData(
        source->content()
    );

    auto result = process.start();

    if (result != 0)
    {
        throw std::runtime_error("Can't compile source. Error: " + process.readStandardError());
    }

    setError(std::move(process.readStandardError()));
    setOutput(std::move(process.readStandardOutput()));

    return std::make_shared<Object>(output);
}
