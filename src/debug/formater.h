#pragma once

#include <ostream>
namespace Format
{
    namespace TextFMT
    {
        enum ColorCode
        {
            BLACK   = 30,
            RED     = 31,
            GREEN   = 32,
            YELLOW  = 33,
            BLUE    = 34,
            MAGENTA = 35,
            CYAN    = 36,
            WHYTE   = 37,
            DEFAULT = 39,
        };
        enum StyleCode
        {
            BOLD        = 1,
            FAINT       = 2,
            ITALIC      = 3,
            UNDERLINE   = 4,

            BOLD_OFF   = 22,
            ITALIC_OFF  = 23,
            UNDERLINE_OFF = 24,
        };
    }

    // empty class responsible for reset format
    class SingleCode final
    {
        unsigned char code_ = 0;

    public:
        SingleCode(int code) : code_{(unsigned char)code} {}
        SingleCode() = default;
        // Rest of constructors and operators are default
        friend std::ostream& operator<<(std::ostream& os, SingleCode const& code);
    };
    class Formater final
    {
        unsigned char set_codes[108] = {};

    public:
        Formater() = default;
        Formater(Formater const& formater) noexcept;
        Formater& operator=(Formater const& formater) noexcept;
        Formater(Formater && formater) = delete;
        Formater & operator=(Formater && formater) = delete;

        Formater& clear() noexcept;
        Formater& setCode(int code) noexcept;
        Formater& removeCode(int code) noexcept;

        friend std::ostream& operator<<(std::ostream& os, Formater const& fromat);
    };
}
