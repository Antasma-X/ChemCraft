#ifndef ERROR_H
#define ERROR_H

#include "StdLibDependencies.h"
#include "GUIDependencies.h"

#include "config.h"


/* 
Whenever an error occurs throughout the code, the error is pushed to the errorStrings stack
This function creates a popup in the bottom left corner of the screen that gives the error message
This can be closed be clicking OK  

The most recent error is prioritized
prganize includestime too
*/
class Error{
    std::stack<std::string> errorStrings;

    public:
        void Push(std::string errorString);
        void ErrorPopUp();
};

extern Error* error;
#endif