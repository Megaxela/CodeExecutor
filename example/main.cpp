
#include <CodeExecutor/Builder.hpp>
#include <iostream>
#include <zconf.h>
#include <fstream>
#include <fcntl.h>
#include <cstring>
#include <wait.h>
#include <CodeExecutor/Process.hpp>

class SampleCompiler : public CodeExecutor::Compiler
{
public:
    CodeExecutor::ObjectPtr compile(CodeExecutor::SourcePtr source, const std::filesystem::path& output,
                                    CodeExecutor::BuildingContextPtr buildingContext) override
    {
        CodeExecutor::Process process("/usr/bin/g++");

        CodeExecutor::Process::ArgumentsContainer arguments;

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
            throw std::runtime_error("Can't compile source.");
        }

        return std::make_shared<CodeExecutor::Object>(output);
    }
};

class SampleLinker : public CodeExecutor::Linker
{
public:
    CodeExecutor::LibraryPtr link(const std::vector<CodeExecutor::ObjectPtr>& objects) override
    {
        std::stringstream library_name;
        library_name << "exec_" << ++m_counter << ".so";

        CodeExecutor::Process process("/usr/bin/gcc");

        CodeExecutor::Process::ArgumentsContainer arguments = {
                "-shared",
                "-fPIC",
                "-lc",
                "-o",
                library_name.str()
        };

        for (auto&& obj : objects)
        {
            arguments.emplace_back(obj->path());
        }

        process.setArguments(std::move(arguments));

        auto result = process.start();

        if (result != 0)
        {
            throw std::runtime_error("Can't perform linkage.");
        }

        auto currentPath = std::filesystem::current_path() / library_name.str();

        return std::make_shared<CodeExecutor::Library>(currentPath);
    }

private:
    int m_counter = 0;
};

static const char* source1Example =
    "#include <iostream>\n"
    "extern \"C\" int func(int a, int b)"
    "{"
    "   std::cout << a + b << std::endl;"
    "}";

static const char* source2Example =
    "extern \"C\" int func2(int a, int b, int c)"
    "{"
    "    return a + b + c;"
    "}";


int main(int argc, char** argv)
{
    CodeExecutor::Builder builder;

    builder.setCompiler(std::make_shared<SampleCompiler>());
    builder.setLinker(std::make_shared<SampleLinker>());

    builder.addTarget(
        CodeExecutor::Source::createFromSource(source1Example)
    );

    auto result = builder.build();

    auto func = result->resolveFunction<int(int, int)>("func");

    if (func == nullptr)
    {
        std::cerr << result->errorString() << std::endl;
        return 1;
    }

    builder.clearTargets();
    builder.addTarget(
        CodeExecutor::Source::createFromSource(source2Example)
    );

    auto result2 = builder.build();

    auto func2 = result2->resolveFunction<int(int, int, int)>("func2");

    if (func2 == nullptr)
    {
        std::cerr << result2->errorString() << std::endl;
        return 1;
    }

    std::cout << "Executing func(12, 13): ";
    func(12, 13);
    std::cout << "Executing func2(1, 2, 3): " << func2(1, 2, 3) << std::endl;

    return 0;
}