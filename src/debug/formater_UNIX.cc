#include "formater_UNIX.h"

std::ostream& Format::operator<<(std::ostream& os, SingleCode const& code)
{
    return os << "\033[" << (int)code.code_ << "m";
}

std::ostream& Format::operator<<(std::ostream& os, Formater const& fromat)
{
    os << "\033[";
    bool hasToPutSemicolon = false;
    for (int i = 0; i != 108; ++i)
    {
        if (fromat.set_codes[i])
        {
            if (hasToPutSemicolon)
                os << ';';
            os << i;
            hasToPutSemicolon = true;
        }
    }
    return os << "m";
}

Format::Formater::Formater(Formater const& formater) noexcept
{
    for (int i = 0; i != 108; ++i)
        set_codes[i] = formater.set_codes[i];
}

Format::Formater& Format::Formater::operator=(Formater const& formater) noexcept
{
    for (int i = 0; i != 108; ++i)
        set_codes[i] = formater.set_codes[i];
    return *this;
}

Format::Formater& Format::Formater::clear() noexcept
{
    for (int i = 0; i != 108; ++i)
        set_codes[i] = 0;
    return *this;
}

Format::Formater& Format::Formater::setCode(int code) noexcept
{
    if (code >= sizeof(set_codes) || code < 0)
        return *this;
    set_codes[code] = 1;
    return *this;
}

Format::Formater& Format::Formater::removeCode(int code) noexcept
{
    if (code >= sizeof(set_codes) || code < 0)
        return *this;
    set_codes[code] = 0;
    return *this;
}
