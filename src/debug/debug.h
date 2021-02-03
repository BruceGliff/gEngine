#pragma once
#include "../../src/debug/logger.h"
#include <exception>

#define gWARNING(x)                                                             \
    {                                                                           \
        GLOBAL::GetLogger().AddLog(new Debug::Warning{__FILE__, __LINE__, x});  \
    }

#define gERROR(x)                                                               \
    {                                                                           \
        GLOBAL::GetLogger().AddLog(new Debug::Error{__FILE__, __LINE__, x});    \
        GLOBAL::GetLogger().DumpToFile();                                       \
        throw std::runtime_error(x);                                            \
    }
