# CodeExecutor
It's C++17 interface library for executing C++ code inside application.

## Build
It's CMake based project, it can be used as
subproject (`add_subdirectory`) in your CMake project.

But also you can build it and use in any build system.

Steps to build it:
1. Clone repo: `git clone https://github.com/Megaxela/CodeExecutor`
1. Go into cloned repo: `cd CodeExecutor`
1. Create build folder `mkdir build`
1. Go into build folder `cd build`
1. Setup project: `cmake ..`
1. Build library: `cmake --build` or `make`

## Usage example
```cpp
#include <iostream>
#include <CodeExecutor/Builder.hpp>
#include <CodeExecutor/Process.hpp>
#include <CodeExecutor/CommonCompiler.hpp>
#include <CodeExecutor/CommonLinker.hpp>

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

    // Setting compiler instance
    builder.setCompiler(
        std::make_shared<CodeExecutor::CommonCompiler>(
            "/usr/bin/gcc"
        )
    );

    // Setting linker instance
    builder.setLinker(
         std::make_shared<CodeExecutor::CommonLinker>(
             "/usr/bin/gcc"
         )
    );

    // Adding build target
    builder.addTarget(

        // Creating source object from actual source
        CodeExecutor::Source::createFromSource(source1Example)
    );

    // Building library
    CodeExecutor::LibraryPtr result;

    try
    {
        result = builder.build();
    }
    catch (std::runtime_error &e)
    {
        // Catching compilation or linkage errors
        std::cerr << "Can't build sources. Error: " << e.what() << std::endl;
        return -1;
    }

    // Resolving function from built library
    auto func = result->resolveFunction<int(int, int)>("func");

    // Checking resolving result
    if (func == nullptr)
    {
        std::cerr << "Can't resolve function: " << result->errorString() << std::endl;
        return 1;
    }

    // Clearing targets
    builder.clearTargets();

    // Adding new target
    builder.addTarget(

        // Catching compilation or linkage errors
        CodeExecutor::Source::createFromSource(source2Example)
    );

    // Building second library
    CodeExecutor::LibraryPtr result2;

    try
    {
        result2 = builder.build();
    }
    catch (std::runtime_error &e)
    {
        // Catching compilation or linkage errors
        std::cerr << "Can't build sources. Error: " << e.what() << std::endl;
        return -1;
    }

    // Resolving second function
    auto func2 = result2->resolveFunction<int(int, int, int)>("func2");

    // Checking resolve result
    if (func2 == nullptr)
    {
        std::cerr << result2->errorString() << std::endl;
        return 1;
    }

    // Running resolved functions
    std::cout << "Executing func(12, 13): ";
    func(12, 13);

    std::cout << "Executing func2(1, 2, 3): " << func2(1, 2, 3) << std::endl;

    return 0;
}
```

## LICENSE

<img align="right" src="http://opensource.org/trademarks/opensource/OSI-Approved-License-100x137.png">

Library is licensed under the [MIT License](https://opensource.org/licenses/MIT)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.