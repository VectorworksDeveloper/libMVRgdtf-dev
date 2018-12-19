//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"
#include "GdtfError.h"

namespace VectorworksMVR
{	
	//----------------------------------------------------------------------------------------
	class CGdtfXmlParsingErrorImpl : public VCOMImpl<IGdtfXmlParsingError>
	{
	public:
		CGdtfXmlParsingErrorImpl();
		virtual ~CGdtfXmlParsingErrorImpl();
		
	public:
		virtual VCOMError VCOM_CALLTYPE     GetErrorType(GdtfDefines::EGdtfParsingError& error);
		
		
		// Implementation
	public:
		void SetPointer(GdtfParsingError* error);
		void GetPointer(GdtfParsingError*& pointer);
		
	private:
		GdtfParsingError*	fPtr;

	};
	
	const VWIID IID_IParsingError = { 0x4bd03cf8, 0xa421, 0x4673, {0x84, 0x88, 0x5e, 0xfa, 0xe1, 0x0c, 0x68, 0x56}};

}
