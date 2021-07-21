#include "logger.h"

#include <typeinfo>
#include <fstream>

using namespace NSDebug;

DebugInfo::DebugInfo(std::string const& file, int line, std::string const& explanation)
    : file_place{file}
    , line_place{line}
    , explain{explanation} {}

void DebugInfo::print(std::ostream& os) const {
    os << "\tFILE:: " << file_place << "\n\tLINE:: " << line_place;
}

void Warning::Dump(std::ostream& os) const {
    if (typeid(os) == typeid(std::cout))
        os << warnFormat << "WARN:: " << NSFormat::SingleCode{ NSFormat::NSTextFMT::StyleCode::BOLD_OFF } << explain << NSFormat::SingleCode{} << "\n";
    else
        os << "WARN:: " << explain << "\n";
    print(os);
    os << std::endl;
}

Warning::Warning(std::string const& file, int line, std::string const& explanation)
    : DebugInfo{file, line, explanation} {
    warnFormat.setCode(NSFormat::NSTextFMT::ColorCode::YELLOW).setCode(NSFormat::NSTextFMT::StyleCode::BOLD);
}

Message::Message(std::string const& file, int line, std::string const& explanation)
    : DebugInfo{file, line, explanation} {
    warnFormat.setCode(NSFormat::NSTextFMT::ColorCode::CYAN).setCode(NSFormat::NSTextFMT::StyleCode::BOLD);
}

void Message::Dump(std::ostream& os) const {
    if (typeid(os) == typeid(std::cout))
        os << warnFormat << "DMSG:: " << NSFormat::SingleCode{ NSFormat::NSTextFMT::StyleCode::BOLD_OFF } << explain << NSFormat::SingleCode{} << "\n";
    else
        os << "DMSG:: " << explain << "\n";
    print(os);
    os << std::endl;
}

void Error::Dump(std::ostream& os) const {
    if (typeid(os) == typeid(std::cerr))
        os << errFormat << "ERR::  " << NSFormat::SingleCode{ NSFormat::NSTextFMT::StyleCode::BOLD_OFF } << explain << NSFormat::SingleCode{} << "\n";
    else
        os << "ERR::  " << explain << "\n";
    print(os);
    os << std::endl;
}

Error::Error(std::string const& file, int line, std::string const& explanation)
    : DebugInfo{file, line, explanation} {
    errFormat.setCode(NSFormat::NSTextFMT::ColorCode::RED).setCode(NSFormat::NSTextFMT::StyleCode::BOLD);
}

Logger const& Logger::DumpWarnings(std::ostream& os) const {
    for (auto&& log : logs)
        if (typeid(*log) == typeid(Warning))
            log->Dump(os);
    return *this;
}

Logger const& Logger::DumpErrors(std::ostream& os) const {
    for (auto&& log : logs)
        if (typeid(*log) == typeid(Error))
            log->Dump(os);
    return *this;
}

Logger const& Logger::Dump(std::ostream& os) const {
    for (auto&& log : logs)
        log->Dump(os);
    return *this;
}

Logger const& Logger::Dump() const {
    for (auto&& log : logs)
        log->Dump();
    return *this;
}

Logger& Logger::AddLog(DebugInfo const* log) {
    logs.push_back(log);
    #ifdef gDEBUG
        log->Dump();
    #endif //gDEBUG
    return *this;
}

Logger const& Logger::DumpToFile() const {
    std::ofstream outfile{ "dump.log" };
    if (outfile.is_open())
        Dump(outfile);
    return *this;
}

Logger::~Logger() {
    try {
#ifdef gDEBUG
        DumpToFile();
#endif //gDEBUG
    }
    catch (...) {
        // silence death
    }
    for (auto&& x : logs)
        delete x;
}
