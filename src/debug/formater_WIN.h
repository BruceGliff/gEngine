#pragma once
#include <windows.h>   // WinApi header. Has to be included only in windows case!

#include <ostream>
namespace Format
{
    namespace TextFMT
    {
        enum ColorCode
        {
            BLACK             = 0,
            DARKBLUE          = FOREGROUND_BLUE,
            DARKGREEN         = FOREGROUND_GREEN,
            DARKCYAN          = FOREGROUND_GREEN | FOREGROUND_BLUE,
            DARKRED           = FOREGROUND_RED,
            DARKMAGENTA       = FOREGROUND_RED | FOREGROUND_BLUE,
            DARKYELLOW        = FOREGROUND_RED | FOREGROUND_GREEN,
            DARKGRAY          = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
            GRAY              = FOREGROUND_INTENSITY,
            BLUE              = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
            GREEN             = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
            CYAN              = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
            RED               = FOREGROUND_INTENSITY | FOREGROUND_RED,
            MAGENTA           = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
            YELLOW            = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
            WHITE             = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
        };
        enum class StyleCode
        {
            BOLD        = 1,
            FAINT       = 2,
            ITALIC      = 3,
            UNDERLINE   = 4,

            BOLD_OFF   = 22,
            ITALIC_OFF  = 23,
            UNDERLINE_OFF = 24,

            DEF
        };
    }

    // empty class responsible for reset format
    class SingleCode final
    {
    public:
        TextFMT::StyleCode code_ = TextFMT::StyleCode::DEF;
        short prev = 0;

        SingleCode(TextFMT::StyleCode code) : code_{code}  {}
        SingleCode() = default;
        // Rest of constructors and operators are default
        //friend std::ostream& operator<<(std::ostream& os, SingleCode const& code);
    };
    // Contains all flags which apply on out stream
    class Formater final
    {
    public:
        // flags of which code is applied
        short code_ = 0;
        HANDLE  hConsole;
        static const short background_mask = 0b1110000; // responsible for background
        short default_console_params;
        short default_console_background;

        Formater();
        Formater(Formater const& formater) noexcept;
        Formater& operator=(Formater const& formater) noexcept;
        Formater(Formater && formater) = delete;
        Formater & operator=(Formater && formater) = delete;

        // set all flags to 0
        Formater& clear() noexcept;
        // set flag with code to 1
        Formater& setCode(int code) noexcept;
        Formater& setCode(TextFMT::StyleCode code) noexcept;
        // set flag with code to 1 
        Formater& removeCode(int code) noexcept;
    };
}
std::ostream& operator<<(std::ostream& os, Format::Formater const& fromat);
std::ostream& operator<<(std::ostream& os, Format::SingleCode const& code);
