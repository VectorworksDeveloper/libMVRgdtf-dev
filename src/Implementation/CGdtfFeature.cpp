//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "VectorworksMVR.h"
#include "CGdtfFeature.h"
#include "CGdtfAttribute.h"


using namespace VectorWorks::Filing;

VectorworksMVR::CGdtfFeatureImpl::CGdtfFeatureImpl()
{
	fFeature = nullptr;
};

VectorworksMVR::CGdtfFeatureImpl::~CGdtfFeatureImpl()
{
    
};

MvrString VectorworksMVR::CGdtfFeatureImpl::GetName()
{
	if( ! fFeature) return "";	
		
    return fFeature->GetName();
}

void VectorworksMVR::CGdtfFeatureImpl::SetPointer(SceneData::GdtfFeature *feature)
{
    fFeature = feature;
}

SceneData::GdtfFeature* VectorworksMVR::CGdtfFeatureImpl::GetPointer()
{
	return fFeature;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFeatureImpl::SetName(MvrString name)
{
  	// Check if valid
	if(!fFeature) return kVCOMError_NotInitialized;

    fFeature->SetName(name);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFeatureImpl::BindToObject(void* objAddr)
{
	// Check if valid
	if(!fFeature) return kVCOMError_NotInitialized;
	
	fFeature->SetBind(objAddr);
	
	return kVCOMError_NoError;
}

void* VectorworksMVR::CGdtfFeatureImpl::GetBoundObject()
{
	// Check if valid
	if(!fFeature) return nullptr;
	
	return fFeature->GetBind();
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFeatureImpl::GetAttributeCount(size_t &count)
{
	if(!fFeature) {return kVCOMError_NotInitialized;}
	
	count = fFeature->GetLinkedAttributes().size();
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFeatureImpl::GetAttributeAt(size_t at, VectorworksMVR::IGdtfAttribute **attribute)
{
	// Check if Set
	if(!fFeature) {return kVCOMError_NotInitialized;}
	
	// Check if no Overflow
	if (at >=  fFeature->GetLinkedAttributes().size()) { return kVCOMError_OutOfBounds;  }
	
	
	SceneData::GdtfAttribute* gdtfAttribute = fFeature->GetLinkedAttributes()[at];
	
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfAttributeImpl* pAttributeObj = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfAttribute, (IVWUnknown**) & pAttributeObj)))
	{
		// Check Casting
		CGdtfAttributeImpl* pResultInterface = dynamic_cast<CGdtfAttributeImpl* >(pAttributeObj);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(gdtfAttribute);
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	
	//---------------------------------------------------------------------------
	// Check Incomming Object
	if (*attribute)
	{
		(*attribute)->Release();
		*attribute		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*attribute	= pAttributeObj;
	
	return kVCOMError_NoError;
}
