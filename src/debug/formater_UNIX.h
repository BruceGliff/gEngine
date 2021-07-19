#pragma once

#include <ostream>
namespace NSFormat {
    // Codes of text formating
    namespace NSTextFMT {
        enum ColorCode {
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
        enum StyleCode {
            BOLD        = 1,
            FAINT       = 2,
            ITALIC      = 3,
            UNDERLINE   = 4,

            BOLD_OFF   = 22,
            ITALIC_OFF  = 23,
            UNDERLINE_OFF = 24,
        };
    } // namespace NSTextFMT

    // empty class responsible for reset format
    class SingleCode final {
        unsigned char code_ = 0;
    public:
        SingleCode(int code) : code_{(unsigned char)code} {}
        SingleCode() = default;
        // Rest of constructors and operators are default
        friend std::ostream& operator<<(std::ostream& os, SingleCode const& code);
    };
    // Contains all flags which apply on out stream
    class Formater final {
        // flags of which code is applied
        unsigned char set_codes[108] = {};

    public:
        Formater() = default;
        Formater(Formater const& formater) noexcept;
        Formater& operator=(Formater const& formater) noexcept;
        Formater(Formater && formater) = delete;
        Formater & operator=(Formater && formater) = delete;

        // set all flags to 0
        Formater& clear() noexcept;
        // set flag with code to 1
        Formater& setCode(int code) noexcept;
        // set flag with code to 1 
        Formater& removeCode(int code) noexcept;

        friend std::ostream& operator<<(std::ostream& os, Formater const& fromat);
    };
} // namespace NSFormat
