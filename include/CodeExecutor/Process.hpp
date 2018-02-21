#pragma once

#include <string>
#include <vector>
#include "filesystem.hpp"

namespace CodeExecutor
{
    /**
     * @brief Class, that describes
     * runnable process.
     */
    class Process
    {
    public:
        using ArgumentsContainer = std::vector<std::string>;

        /**
         * @brief Default constructor.
         */
        Process();

        /**
         * @brief Constructor from command.
         * @param command Command.
         */
        explicit Process(std::string command, ArgumentsContainer arguments = ArgumentsContainer());

        /**
         * @brief Destructor.
         */
        ~Process();

        /**
         * @brief Method for getting process
         * result exit code.
         * @return Exit code.
         */
        int exitCode() const;

        /**
         * @brief Get stderr content.
         * @return Error output.
         */
        std::string readStandardError() const;

        /**
         * @brief Get stdout content.
         * @return Out content.
         */
        std::string readStardardOutput() const;

        /**
         * @brief Method for getting path to
         * standard error file.
         * @return Path to file with stderr.
         */
        std::filesystem::path standardErrorFile() const;

        /**
         * @brief Method for getting path to
         * standard output file.
         * @return Path to file with stdout.
         */
        std::filesystem::path standardOutputFile() const;

        /**
         * @brief Method for setting standard error
         * file.
         * @param path Path to file.
         */
        void setStandardErrorFile(std::filesystem::path path);

        /**
         * @brief Method for setting standard output
         * file.
         * @param path Path to file.
         */
        void setStandardOutputFile(std::filesystem::path path);

        /**
         * @brief Method for getting program arguments.
         * @return Container with arguments.
         */
        ArgumentsContainer arguments() const;

        /**
         * @brief Method for setting program arguments.
         * @param arguments Program arguments.
         */
        void setArguments(ArgumentsContainer arguments);

        /**
         * @brief Method for getting program path.
         * @return Path to program.
         */
        std::filesystem::path program() const;

        /**
         * @brief Method for setting program path.
         * @param path Path to program.
         */
        void setProgram(std::filesystem::path path);

        /**
         * @brief Method for getting working directory.
         * @return Path to working directory.
         */
        std::filesystem::path workingDirectory() const;

        /**
         * @brief Method for setting working directory.
         * @param path Path to working directory.
         */
        void setWorkingDirectory(std::filesystem::path path);

        /**
         * @brief Method for setting data redirected
         * to program stdin.
         * @param data Data.
         */
        void setInputData(std::string data);

        /**
         * @brief Method for getting data, that will
         * be redirected to program's stdin.
         * @return Data.
         */
        std::string inputData() const;

        /**
         * @brief Method for starting process.
         * @return Execution result.
         */
        int start();

    private:

        bool makeNonBlocking(int fd);

        std::filesystem::path m_workingDirectory;
        std::filesystem::path m_program;
        ArgumentsContainer m_arguments;

        std::string m_inputData;

        std::filesystem::path m_stdoutFile;
        std::filesystem::path m_stderrFile;

        std::stringstream m_stderrStream;
        std::stringstream m_stdoutStream;

        int m_exitCode;
    };
}

