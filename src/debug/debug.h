#pragma once
#include "logger.h"
#include "process/global.h"
#include <exception>
extern int _J84659365ifInDebugMode;
// add warning log to further dump
#define gWARNING(x)                                                             \
    {                                                                           \
        GLOBAL::GetLogger().AddLog(new Debug::Warning{__FILE__, __LINE__, x});  \
    }

// add error log, dump everything to file, throw std::runtime_error
#define gERROR(x)                                                               \
    {                                                                           \
        GLOBAL::GetLogger().AddLog(new Debug::Error{__FILE__, __LINE__, x});    \
        GLOBAL::GetLogger().DumpToFile();                                       \
        throw std::runtime_error(x);                                            \
    }

// add debug log only in debug mode
#define gMESSAGE(x)                                                             \
    if (_J84659365ifInDebugMode)                                                \
    {                                                                           \
        GLOBAL::GetLogger().AddLog(new Debug::Message{__FILE__, __LINE__, x});  \
    }
    

