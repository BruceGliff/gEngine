#include "../../src/debug/debug.h"

#include "global.h"

int main()
{
    gWARNING("Smth bad happened");
    gERROR("AAAAAAAAAAA");
    gWARNING("ASD");
    gERROR("AGGD");
    return 0;
}