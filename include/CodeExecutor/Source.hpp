#pragma once

#include <memory>

namespace CodeExecutor
{
    class Source;

    using SourcePtr = std::shared_ptr<Source>;

    /**
     * @brief Class, that describes
     * source file content.
     */
    class Source
    {
        struct HideArg{};
    public:

        /**
         * @brief Hidden constructor.
         * @param content Content.
         */
        explicit Source(std::string content, HideArg);

        Source(const Source&) = delete;
        Source& operator=(const Source&) = delete;

        /**
         * @brief Virtual constructor.
         * @param content String with source code
         * content.
         * @return Source object pointer.
         */
        static SourcePtr createFromSource(std::string content);

//        static SourcePtr createFromFile

        /**
         * @brief Method for getting source content.
         * @return String with source content.
         */
        std::string content() const;

    private:

        std::string m_content;
    };
}

