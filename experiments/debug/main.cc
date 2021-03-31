#include "../../src/debug/debug.h"

#include "global.h"

#include <string>
#include <iostream>


int main()
{
    gWARNING("Smth bad happened");
    gMESSAGE("AAAAAAAAAAA");
    gWARNING("ASD");

    gERROR("AGGD");
    return 0;
}