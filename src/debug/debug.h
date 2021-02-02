#pragma once

#define gWARNING(x)                                             \
    {                                                           \       
        GLOBAL::GetLogger().AddWarning(__FILE__, __LINE__, x);  \
    }