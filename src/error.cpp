#include "error.h"

void callError(Error error, const std::string& caller)
{
    callError(error, caller, 0);
}

void callWarning(Warning warning, const std::string& caller)
{
    callWarning(warning, caller, 0);
}
