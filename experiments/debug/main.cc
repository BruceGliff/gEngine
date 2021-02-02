#include "../../src/debug/debug.h"
#include "../../src/debug/logger.h"

Debug::Logger LOG{};
namespace GLOBAL
{
    Debug::Logger & GetLogger()
    {
        return LOG;
    }
}

int main()
{


    return 0;
}