#include "global.h"
#include "../../src/debug/logger.h"

Debug::Logger LOG{};

Debug::Logger & GLOBAL::GetLogger()
{
    return LOG;
}
