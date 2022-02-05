#include "formater_UNIX.h"

using namespace NSFormat;

/*
std::ostream& operator<<(std::ostream& os, SingleCode const& code) {
    return os << "\033[" << (int)code.code_ << "m";
}

std::ostream& operator<<(std::ostream& os, Formater const& fromat) {
    os << "\033[";
    bool hasToPutSemicolon = false;
    for (int i = 0; i != 108; ++i)
        if (fromat.set_codes[i]) {
            if (hasToPutSemicolon)
                os << ';';
            os << i;
            hasToPutSemicolon = true;
        }
    return os << "m";
}
*/

Formater::Formater(Formater const& formater) noexcept {
    for (int i = 0; i != 108; ++i)
        set_codes[i] = formater.set_codes[i];
}

Formater& Formater::operator=(Formater const& formater) noexcept {
    for (int i = 0; i != 108; ++i)
        set_codes[i] = formater.set_codes[i];
    return *this;
}

Formater& Formater::clear() noexcept {
    for (int i = 0; i != 108; ++i)
        set_codes[i] = 0;
    return *this;
}

Formater& Formater::setCode(int code) noexcept {
    if (code >= sizeof(set_codes) || code < 0)
        return *this;
    set_codes[code] = 1;
    return *this;
}

Formater& Formater::removeCode(int code) noexcept {
    if (code >= sizeof(set_codes) || code < 0)
        return *this;
    set_codes[code] = 0;
    return *this;
}
