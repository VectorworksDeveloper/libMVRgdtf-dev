// ErrorHandler.cpp
//
// Error handling code for the XML parser.
#include "StdAfx.h"

#include "ErrorHandler.h"

using namespace XML;

bool XMLErrorHandler::handleError(const DOMError &domError)
{
    // Display whatever error message passed from the serializer
    if (domError.getSeverity() == DOMError::DOM_SEVERITY_WARNING)
        ::strcpy(errorString, "\nWarning Message: ");

    else if (domError.getSeverity() == DOMError::DOM_SEVERITY_ERROR)
        ::strcpy(errorString, "\nError Message: ");

    else
        ::strcpy(errorString, "\nFatal Message: ");

    char *msg = XMLString::transcode(domError.getMessage());
    ::strcpy(errorString, msg);
    XMLString::release(&msg);

    // Instructs the serializer to continue serialization if possible.
    return true;
}
