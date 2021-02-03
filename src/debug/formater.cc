#include "formater.h"

std::ostream& Format::operator<<(std::ostream& os, SingleCode const& code)
{
    return os << "\033[" << (int)code.code_ << "m";
}
