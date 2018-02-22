#include <gtest/gtest.h>
#include <CodeExecutor/Source.hpp>
#include <CodeExecutor/Builder.hpp>
#include <CodeExecutor/CommonCompiler.hpp>
#include <CodeExecutor/CommonLinker.hpp>

static CodeExecutor::BuilderPtr makeBuilder(
    std::string compiler,
    std::string linker
)
{
    auto builder = std::make_shared<CodeExecutor::Builder>();

    builder->setCompiler(
        std::make_shared<CodeExecutor::CommonCompiler>(
            std::move(compiler)
        )
    );

    builder->setLinker(
        std::make_shared<CodeExecutor::CommonLinker>(
            std::move(linker)
        )
    );

    return builder;
}

static CodeExecutor::BuilderPtr makeBuilder()
{
    return makeBuilder("/usr/bin/gcc", "/usr/bin/gcc");
}

TEST(Building, SingleFunction)
{
    const char* source =
        "extern \"C\" int function(int number)"
        "{ return number; }";

    // Creating builder
    auto builder = makeBuilder();

    // Creating source
    auto src = CodeExecutor::Source::createFromSource(source);

    ASSERT_NE(src, nullptr);

    // Adding target to be built
    builder->addTarget(src);

    CodeExecutor::LibraryPtr library;

    // Building library
    ASSERT_NO_THROW(
        library = builder->build()
    );

    ASSERT_NE(library, nullptr);

    // Resolving function
    auto function = library->resolveFunction<int(int)>("function");

    ASSERT_NE(function, nullptr);

    // Checking execution result
    ASSERT_EQ(function(12), 12);
}

TEST(Building, MultipleFunctionsSequence)
{
    const char* source =
        "extern \"C\" int function1(int number)"
        "{ return number; }\n"
        "extern \"C\" int function2(int number)"
        "{ return number * number; }";

    // Creating builder
    auto builder = makeBuilder();

    // Creating source
    auto src = CodeExecutor::Source::createFromSource(source);

    ASSERT_NE(src, nullptr);

    // Adding target to be built
    builder->addTarget(src);

    CodeExecutor::LibraryPtr library;

    // Building library
    ASSERT_NO_THROW(
        library = builder->build()
    );

    ASSERT_NE(library, nullptr);

    // Resolving function1(12) == 12
    auto function1 = library->resolveFunction<int(int)>("function1");

    ASSERT_NE(function1, nullptr);

    // Checking execution result
    ASSERT_EQ(function1(12), 12);

    // Resolving function2(12) == 144
    auto function2 = library->resolveFunction<int(int)>("function2");

    ASSERT_NE(function2, nullptr);

    // Checking execution result
    ASSERT_EQ(function2(12), 144);
}

TEST(Building, MultipleFunctionOneTime)
{
    const char* source =
        "extern \"C\" int function1(int number)"
        "{ return number; }\n"
        "extern \"C\" int function2(int number)"
        "{ return number * number; }";

    // Creating builder
    auto builder = makeBuilder();

    // Creating source
    auto src = CodeExecutor::Source::createFromSource(source);

    ASSERT_NE(src, nullptr);

    // Adding target to be built
    builder->addTarget(src);

    CodeExecutor::LibraryPtr library;

    // Building library
    ASSERT_NO_THROW(
        library = builder->build()
    );

    ASSERT_NE(library, nullptr);

    // Resolving function1(12) == 12
    auto function1 = library->resolveFunction<int(int)>("function1");

    // Resolving function2(12) == 144
    auto function2 = library->resolveFunction<int(int)>("function2");

    ASSERT_NE(function1, nullptr);

    ASSERT_NE(function2, nullptr);

    // Checking execution result
    ASSERT_EQ(function1(12), 12);

    // Checking execution result
    ASSERT_EQ(function2(12), 144);
}

class ClassMockup
{
public:
    virtual int someFunction(int) = 0;
};

TEST(Building, Class)
{
    const char* source =
        "class ClassMockup"
        "{"
        "public:"
            "virtual int someFunction(int val)"
            "{"
            "    return val + 2 * val;"
            "}"
        "};"
        ""
        "extern \"C\" ClassMockup* creator()"
        "{ return new ClassMockup; }";

    // Creating builder
    auto builder = makeBuilder();

    // Creating source
    auto src = CodeExecutor::Source::createFromSource(source);

    ASSERT_NE(src, nullptr);

    // Adding target to be built
    builder->addTarget(src);

    CodeExecutor::LibraryPtr library;

    // Building library
    ASSERT_NO_THROW(
        library = builder->build();
    );

    ASSERT_NE(library, nullptr);

    // Resolving function
    auto function = library->resolveFunction<ClassMockup*()>("creator");

    ASSERT_NE(function, nullptr);

    // Checking execution result
    ClassMockup* target = function();

    ASSERT_EQ(target->someFunction(12), 12 * 3);
}

