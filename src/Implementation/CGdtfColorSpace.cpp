#include "CGdtfColorSpace.h"
//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------

using namespace VectorworksMVR;

VectorworksMVR::CGdtfColorSpaceImpl::CGdtfColorSpaceImpl()
{
    fColorSpace = nullptr;
}

VectorworksMVR::CGdtfColorSpaceImpl::~CGdtfColorSpaceImpl()
{GdtfConv
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfColorSpaceImpl::GetColorSpace(EGdtfColorSpace outVal)
{
	//Check Pointer
	if( ! fColorSpace)		return kVCOMError_NotInitialized;    

    outVal = fColorSpace->GetColorSpace();

	return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfColorSpaceImpl::GetRed(CieColor& outVal)
{
	//Check Pointer
	if( ! fColorSpace)		return kVCOMError_NotInitialized;    

    outVal = fColorSpace->GetRed();

	return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfColorSpaceImpl::GetGreen(CieColor& outVal)
{
	//Check Pointer
	if( ! fColorSpace)		return kVCOMError_NotInitialized;    

    outVal = fColorSpace->GetGreen();

    return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfColorSpaceImpl::GetBlue(CieColor& outVal)
{
	//Check Pointer
	if( ! fColorSpace)		return kVCOMError_NotInitialized;    

    outVal = fColorSpace->GetBlue();

    return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfColorSpaceImpl::SetColorSpace(EGdtfColorSpace val)
{
	//Check Pointer
	if( ! fColorSpace)		return kVCOMError_NotInitialized;    
	
    return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfColorSpaceImpl::SetRed(C
    ieColor val)
{
	//Check Pointer
	if( ! fColorSpace)		return kVCOMError_NotInitialized;    

    fColorSpace->SetRed(val);

	return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfColorSpaceImpl::SetGreen(CieColor& val)
{
	//Check Pointer
	if( ! fColorSpace)		return kVCOMError_NotInitialized;    

    fColorSpace->SetGreen(val);

	return kVCOMError_NoError;
}

VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfColorSpaceImpl::SetBlue(CieColor& val)
{
	//Check Pointer
	if( ! fColorSpace)		return kVCOMError_NotInitialized;    

    fColorSpace->SetBlue(val);

	return kVCOMError_NoError;
}


VCOMError VCOM_CALLTYPE VectorworksMVR::CGdtfColorSpaceImpl::BindToObject(void * objAddr)
{
    // Check if valid
    if (!fColorSpace) return kVCOMError_NotInitialized;

    fColorSpace->SetBind(objAddr);

    return kVCOMError_NoError;
}

void *VCOM_CALLTYPE VectorworksMVR::CGdtfColorSpaceImpl::GetBoundObject()
{
    // Check if valid
    if (!fColorSpace) return nullptr;

    return fColorSpace->GetBind();
}

void VectorworksMVR::CGdtfColorSpaceImpl::SetPointer(SceneData::GdtfColorSpace * ColorSpace)
{
    fColorSpace = ColorSpace;
}

SceneData::GdtfColorSpace * VectorworksMVR::CGdtfColorSpaceImpl::GetPointer()
{
    return fColorSpace;
}
