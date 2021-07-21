#include "formater_WIN.h"

#include <iostream>
#include <bitset>

short def = 0;
using namespace NSFormat;

std::ostream& operator<<(std::ostream& os, SingleCode const& code) {
    // gat console handler, get current style, set new one.

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    if (!GetConsoleScreenBufferInfo(hConsole, &info)) {
        std::cerr << "Can not get Console info!";
        return os;
    }
    short toSet = info.wAttributes;
    switch (code.code_) {
    case NSTextFMT::StyleCode::BOLD_OFF:
        toSet |= FOREGROUND_INTENSITY;
        break;
    case NSTextFMT::StyleCode::DEF:
        toSet = def;
        break;
    default:
        std::cerr << "Unexpected code!\n";
        return os;
    }

    SetConsoleTextAttribute(hConsole, toSet);
    return os;
}

std::ostream& operator<<(std::ostream& os, Formater const& format) {
    // get console handler, set params
    SetConsoleTextAttribute(format.hConsole, format.code_);
    return os;
}

Formater::Formater() {
    default_console_params = 0;
    CONSOLE_SCREEN_BUFFER_INFO info;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!GetConsoleScreenBufferInfo(hConsole, &info)) {
        std::cerr << "Can not get Console info!";
        return;
    }
    default_console_params = info.wAttributes;
    def = info.wAttributes;
    default_console_background = background_mask &  default_console_params;
    code_ |= default_console_background;
}

Formater::Formater(Formater const& formater) noexcept {
    code_ = formater.code_;
}

Formater& Formater::operator=(Formater const& formater) noexcept {
    code_ = formater.code_;
    return *this;
}

Formater& Formater::clear() noexcept {
    code_ = default_console_params;
    return *this;
}

Formater& Formater::setCode(int code) noexcept {
    code_ |= code;
    return *this;
}

Formater& Formater::setCode(NSTextFMT::StyleCode code) noexcept {
    switch (code) {
    case NSTextFMT::StyleCode::BOLD:
        code_ &= ~FOREGROUND_INTENSITY;
        return *this;
    case NSTextFMT::StyleCode::BOLD_OFF:
        code_ |= FOREGROUND_INTENSITY;
        return *this;
    }
    return *this;
}

Formater& Formater::removeCode(int code) noexcept {
    code_ &= ~code;
    return *this;
}
