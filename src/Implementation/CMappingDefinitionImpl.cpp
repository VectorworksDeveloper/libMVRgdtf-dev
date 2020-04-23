//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CMediaRessourceVectorImpl.h"


using namespace VectorworksMVR::Filing;


VectorworksMVR::CMappingDefinitionImpl::CMappingDefinitionImpl()
{
	fPtr = nullptr;
}

VectorworksMVR::CMappingDefinitionImpl::~CMappingDefinitionImpl()
{
	fPtr = nullptr;
}

MvrString VectorworksMVR::CMappingDefinitionImpl::GetName()
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return "";
	
	return fPtr->getName().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CMappingDefinitionImpl::GetGuid(MvrUUID& outGuid)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherise return data
	fPtr->getGuid().GetUuidObj().GetUUID(outGuid.a, outGuid.b, outGuid.c, outGuid.d);

	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CMappingDefinitionImpl::GetSizeX(Uint32& sizeX)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherwise return data
	sizeX = fPtr->GetSizeX();

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CMappingDefinitionImpl::GetSizeY(Uint32& sizeY)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherwise return data
	sizeY = fPtr->GetSizeY();

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CMappingDefinitionImpl::GetSource(ISource** outSource)
{
	//------------------------------------------------------------------------------------------
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	SceneData::SceneDataSourceObjPtr source = fPtr->GetSource();
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CSourceImpl* pSource = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_SourceObj, (IVWUnknown**) &pSource)))
	{
		// Check Casting
		CSourceImpl* pResultInterface = dynamic_cast<CSourceImpl*>(pSource);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(source);
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	else
	{
		return kVCOMError_Failed;
	}
	
	//---------------------------------------------------------------------------
	// Check Incoming Object
	if (*outSource)
	{
		(*outSource)->Release();
		*outSource		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*outSource = pSource;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CMappingDefinitionImpl::GetScaleHandling(EScaleHandlingType& scaleHandling)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherwise return data
	scaleHandling = fPtr->GetScaleHandling();

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CMappingDefinitionImpl::SetSizeX(Uint32 sizeX)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherwise return data
	fPtr->SetSizeX(sizeX);

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CMappingDefinitionImpl::SetSizeY(Uint32 sizeY)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherwise return data
	fPtr->SetSizeY(sizeY);

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CMappingDefinitionImpl::SetSource(ISource* source)
{	
	// ------------------------------------------------------------------------------------------
	// Check the incoming object
	if (!source) { return kVCOMError_InvalidArg; }
	
	// ------------------------------------------------------------------------------------------
	// Cast to object
	CSourceImpl* pSource = dynamic_cast<CSourceImpl* >(source);
	
	ASSERTN(kEveryone, pSource != nullptr);
	if ( ! pSource) { return kVCOMError_Failed;	}
	
	//
	SceneData::SceneDataSourceObjPtr scSource = nullptr;
	pSource->GetPointer(scSource);
	
	ASSERTN(kEveryone, scSource != nullptr);
	if ( ! scSource) { return kVCOMError_InvalidArg; }
	
	fPtr->SetSource(scSource);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CMappingDefinitionImpl::SetScaleHandling(EScaleHandlingType scaleHandling)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherwise return data
	fPtr->SetScaleHandling(scaleHandling);

	return kVCOMError_NoError;
}


void VectorworksMVR::CMappingDefinitionImpl::SetPointer(SceneData::SceneDataMappingDefinitionObjPtr pointer)
{
	fPtr = pointer;
}

void VectorworksMVR::CMappingDefinitionImpl::GetPointer(SceneData::SceneDataMappingDefinitionObjPtr& pointer)
{
	pointer = fPtr;
}
