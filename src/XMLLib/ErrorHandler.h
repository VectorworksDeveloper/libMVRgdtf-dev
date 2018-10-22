#pragma once


#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H


namespace XML
{

	XERCES_CPP_NAMESPACE_USE

	class XMLErrorHandler : public DOMErrorHandler
	{
	public:

		XMLErrorHandler() {};
		~XMLErrorHandler() {};

		/** @name The error handler interface */
		bool handleError(const DOMError& domError);
		void resetErrors() {};

	private :
		/* Unimplemented constructors and operators */
		XMLErrorHandler(const DOMErrorHandler&);
		void operator=(const DOMErrorHandler&);

		char	errorString[256];
	};
}

#endif
