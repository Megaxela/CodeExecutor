#include <zconf.h>
#include <fcntl.h>
#include <wait.h>
#include "CodeExecutor/Process.hpp"

template<typename Stream>
void readFd(int fd, Stream& ss)
{
    char buffer[1024];

    while (true)
    {
        auto result = read(fd, buffer, 1024);

        if (result < 0)
        {
            if (errno == EAGAIN)
            {
                continue;
            }
            else
            {
                return;
            }
        }
        else if (result == 0)
        {
            return;
        }

        buffer[result] = '\0';

        ss << buffer;
    }
}

CodeExecutor::Process::Process() :
    m_workingDirectory(std::filesystem::current_path()),
    m_program(),
    m_arguments(),
    m_inputData(),
    m_stdoutFile(),
    m_stderrFile(),
    m_stderrStream(),
    m_stdoutStream(),
    m_exitCode(0)
{

}

CodeExecutor::Process::Process(std::string command,
                               ArgumentsContainer arguments) :
    m_workingDirectory(std::filesystem::current_path()),
    m_program(std::move(command)),
    m_arguments(std::move(arguments)),
    m_inputData(),
    m_stdoutFile(),
    m_stderrFile(),
    m_stderrStream(),
    m_stdoutStream(),
    m_exitCode(0)
{

}

CodeExecutor::Process::~Process()
{

}

int CodeExecutor::Process::exitCode() const
{
    return m_exitCode;
}

std::string CodeExecutor::Process::readStandardError() const
{
    return m_stderrStream.str();
}

std::string CodeExecutor::Process::readStandardOutput() const
{
    return m_stdoutStream.str();
}

std::filesystem::path CodeExecutor::Process::standardErrorFile() const
{
    return m_stderrFile;
}

std::filesystem::path CodeExecutor::Process::standardOutputFile() const
{
    return m_stdoutFile;
}

void CodeExecutor::Process::setStandardErrorFile(std::filesystem::path path)
{
    m_stderrFile = std::move(path);
}

void CodeExecutor::Process::setStandardOutputFile(std::filesystem::path path)
{
    m_stdoutFile = std::move(path);
}

CodeExecutor::Process::ArgumentsContainer CodeExecutor::Process::arguments() const
{
    return m_arguments;
}

void CodeExecutor::Process::setArguments(CodeExecutor::Process::ArgumentsContainer arguments)
{
    m_arguments = std::move(arguments);
}

std::filesystem::path CodeExecutor::Process::program() const
{
    return m_program;
}

void CodeExecutor::Process::setProgram(std::filesystem::path path)
{
    m_program = std::move(path);
}

std::filesystem::path CodeExecutor::Process::workingDirectory() const
{
    return m_workingDirectory;
}

void CodeExecutor::Process::setWorkingDirectory(std::filesystem::path path)
{
    m_workingDirectory = std::move(path);
}

void CodeExecutor::Process::setInputData(std::string data)
{
    m_inputData = std::move(data);
}

std::string CodeExecutor::Process::inputData() const
{
    return m_inputData;
}

int CodeExecutor::Process::start()
{
    // Preparing replacing stdout, stdin, stderr
    int stdoutfd[2];
    int stdinfd[2];
    int stderrfd[2];

    int oldstdin;
    int oldstdout;
    int oldstderr;

    pipe(stdoutfd); // Where the parent is going to write to
    pipe(stdinfd);  // From where parent is going to read stdout
    pipe(stderrfd); // From where parent is going to read stderr

    oldstdin  = dup(0); // Saving current stdin
    oldstdout = dup(1); // Saving current stdout
    oldstderr = dup(2); // Saving current stderr

    close(0); // Closing current stdin
    close(1); // Closing current stdout
    close(2); // Closing current stderr

    dup2(stdoutfd[0], 0); // Make the read end of stdoutfd pipe as stdin
    dup2(stdinfd[1],  1); // Make the write end of stdinfd as stdout
    dup2(stderrfd[1], 2); // Make the write end of stderrfd as stderr

    auto pid = fork();

    // If it's child process
    if (!pid)
    {
        // Path to program, arguments and nullptr
        char* argv[m_arguments.size() + 2];

        // Maybe copy needed
        auto programString = m_program.string();

        // Path to program
        argv[0] = new char[programString.size() + 1];
        argv[0][programString.size()] = '\0';
        std::copy(programString.begin(), programString.end(), argv[0]);

        int i = 0;
        // Copying arguments
        for (auto&& arg : m_arguments)
        {
            argv[++i] = new char[arg.size() + 1];
            argv[i][arg.size()] = '\0';
            std::copy(arg.begin(), arg.end(), argv[i]);
        }

        // Setting null
        argv[m_arguments.size() + 1] = nullptr;

        // Closing useless fd
        close(stdoutfd[0]);
        close(stdoutfd[1]);

        close(stdinfd[0]);
        close(stdinfd[1]);

        close(stderrfd[0]);
        close(stderrfd[1]);

        execv(argv[0], argv);
    }
    else
    {
        // Restoring the original std fds of parent
        close(0);
        close(1);
        close(2);

        dup2(oldstdin,  0);
        dup2(oldstdout, 1);
        dup2(oldstderr, 2);

        close(stdoutfd[0]);
        close(stdinfd [1]);
        close(stderrfd[1]);

        // Writing to child's stdin
        write(
            stdoutfd[1],
            m_inputData.c_str(),
            m_inputData.size()
        );

        // Closing stdin, to force EOF
        close(stdoutfd[1]);

        // Making stdout and stderr nonblocking
        makeNonBlocking(stdinfd[0]);
        makeNonBlocking(stderrfd[0]);

        // Waiting child to end
        int status;
        waitpid(pid, &status, 0);
        m_exitCode = WEXITSTATUS(status);

        // Reading stdout
        readFd(stdinfd[0], m_stdoutStream);
        readFd(stderrfd[0], m_stderrStream);
    }

    return m_exitCode;
}

bool CodeExecutor::Process::makeNonBlocking(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);

    if (flags == -1)
    {
        return false;
    }

    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1)
    {
        return false;
    }

    flags = fcntl(fd, F_GETFL, 0);
    return (flags & O_NONBLOCK) == O_NONBLOCK;
}
