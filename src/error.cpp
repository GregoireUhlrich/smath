#include "error.h"

void callError(smError::Error error, const std::string& caller) {
    callError(error, caller, 0);
}

void callWarning(smError::Warning warning, const std::string& caller) {
    callWarning(warning, caller, 0);
}
