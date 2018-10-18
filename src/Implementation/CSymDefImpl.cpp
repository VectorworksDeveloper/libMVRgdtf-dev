//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "VectorworksMVR.h"
#include "CMediaRessourceVectorImpl.h"
#include "Utility.h"

using namespace VectorWorks::Filing;


VectorworksMVR::CSymDefImpl::CSymDefImpl()
{
	fPtr		= nullptr;
	fContext	= nullptr;
}

VectorworksMVR::CSymDefImpl::~CSymDefImpl()
{
	fPtr		= nullptr;
	fContext	= nullptr;

	for(auto it : farrGeometryWrappers)
		delete it;
	farrGeometryWrappers.clear();
}

MvrString VectorworksMVR::CSymDefImpl::GetName()
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return "";
	
	// Otherise return data
	return fPtr->getName().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CSymDefImpl::GetGeometryCount(size_t& outCount)
{
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	// Otherise return data
	outCount = fPtr->getGeometryArray().size();
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CSymDefImpl::GetGeometryAt(size_t at, IGeometryReference** outGeometryRef)
{
	//------------------------------------------------------------------------------------------
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	ASSERTN(kEveryone,fContext);
	if( ! fContext) return kVCOMError_NotInitialized;
	
	
	//------------------------------------------------------------------------------------------
	// Check the position in the array
	size_t count = fPtr->getGeometryArray().size();
	
	
	ASSERTN(kEveryone, at < count);
	if (count <= at) { return kVCOMError_InvalidArg; }
	
	SceneData::SceneDataGeoInstanceObjPtr pScGeoObjInst = fPtr->getGeometryArray().at(at);
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGeometryReferenceImpl* pGeometryRef = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GeometryReference, (IVWUnknown**) & pGeometryRef)))
	{
		// Check Casting
		CGeometryReferenceImpl* pResultInterface = dynamic_cast<CGeometryReferenceImpl* >(pGeometryRef);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(pScGeoObjInst, pScGeoObjInst->IsSymDef(), fContext);
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
	if (*outGeometryRef)
	{
		(*outGeometryRef)->Release();
		*outGeometryRef		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*outGeometryRef		= pGeometryRef;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CSymDefImpl::AddGeometry(const STransformMatrix& scMatrix, IGeometryProvider* provider)
{
	ASSERTN(kEveryone, provider);
	if( ! provider ) return kVCOMError_InvalidArg;

	CGeometryProviderWrapper* providerWrapper = new CGeometryProviderWrapper( provider );

	//---------------------------------------------------------------------------
	// Create the new object, and set the file name
	SceneData::SceneDataGeometryObjPtr geometryObject = new SceneData::SceneDataGeometryObj();
	geometryObject->SetGeometryProvider( providerWrapper );
	
	farrGeometryWrappers.push_back( providerWrapper );
	
	//---------------------------------------------------------------------------
	// Set Transfrom Matrix
	VWTransformMatrix ma;
	Utility::ConvertMatrix(scMatrix, ma);
	geometryObject->SetTransformMatrix(ma);
		
		
	//---------------------------------------------------------------------------
	// Simply add it to the the array, deletion will be handeld by the container
	fPtr->Add(geometryObject);

	// If export fails, just return false
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CSymDefImpl::AddSymbol(const STransformMatrix& geometry, ISymDef* symDef)
{
	//------------------------------------------------------------------------------------------
	// Check if this is initialized
	ASSERTN(kEveryone,fPtr);
	if( ! fPtr) return kVCOMError_NotInitialized;
	
	//------------------------------------------------------------------------------------------
	// Cast incomming symDef
	CSymDefImpl* pSymDef = dynamic_cast<CSymDefImpl*>(symDef);
	
	// Check Casting
	ASSERTN(kEveryone, pSymDef != nullptr);
	if ( ! pSymDef) { return kVCOMError_InvalidArg; }
	
	//------------------------------------------------------------------------------------------
	// Get linked Symdef
	SceneData::SceneDataSymDefObjPtr pScSymDef = nullptr;
	pSymDef->GetPointer(pScSymDef);
	
	ASSERTN(kEveryone, pScSymDef != nullptr);
	if ( ! pScSymDef) { return kVCOMError_NotInitialized; }
	
	
	//------------------------------------------------------------------------------------------
	// Create new geometry obj
	SceneData::SceneDataSymbolObjPtr newSymbolObj = new SceneData::SceneDataSymbolObj(SceneData::SceneDataGUID(VWFC::UUID()));
	
	// Set Transfrom Matrix
	VWTransformMatrix ma;
	Utility::ConvertMatrix(geometry,  ma);
	newSymbolObj->SetTransformMatrix(ma);
	
	// Set SymbolDef
	newSymbolObj->SetSymDef(pScSymDef);
	
	//-------------------------------------------------------------------------------------------
	// Add Object
	fPtr->Add(newSymbolObj);
	
	return kVCOMError_NoError;
}

void VectorworksMVR::CSymDefImpl::SetPointer(SceneData::SceneDataSymDefObjPtr pointer, SceneData::SceneDataExchange* context)
{
	fPtr		= pointer;
	fContext	= context;
}

void VectorworksMVR::CSymDefImpl::GetPointer(SceneData::SceneDataSymDefObjPtr& pointer)
{
	pointer = fPtr;
}
