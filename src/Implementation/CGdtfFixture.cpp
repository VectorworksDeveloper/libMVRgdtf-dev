//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfFixture.h"
#include "CGdtfWheel.h"
#include "CGdtfActivationGroup.h"
#include "CGdtfFeatureGroup.h"
#include "CGdtfAttribute.h"
#include "CGdtfModel.h"
#include "CGdtfGeometry.h"
#include "CGdtfDmxMode.h"
#include "CGdtfRevision.h"
#include "CGdtfUserPreset.h"
#include "CGdtfMacro.h"
#include "CGdtfPhysicalEmitter.h"
#include "CMediaRessourceVectorImpl.h"
#include "Utility.h"
#include "CGdtfDmxProfile.h"
#include "CGdtfCRIGroup.h"
#include "CGdtfFTRDM.h"
#include "CGdtfXmlParsingError.h"
#include "GdtfError.h"
#include "CGdtfFilter.h"
#include "CGdtfColorSpace.h"

using namespace VectorworksMVR::Filing;

VectorworksMVR::CGdtfFixtureImpl::CGdtfFixtureImpl()
{
    fFixtureObject = nullptr;
}

VectorworksMVR::CGdtfFixtureImpl::~CGdtfFixtureImpl()
{
    if (fFixtureObject) {delete fFixtureObject;}
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::ReadFromFile(MvrString fullPath)
{
	TXString strFullPath ( fullPath );
	
    // Create the file pointer on the full path
    IFileIdentifierPtr file (IID_FileIdentifier);
    file->Set(strFullPath);
	
    // Read From File
    return ReadFromFile(file, "" /*During GDTF reading, we read onyl one file*/);
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::OpenForWrite(MvrString fullPath, MvrString name, MvrString manufacturer, const MvrUUID& uuid)
{	
	TXString strFullPath ( fullPath );
	
	// Create the file pointer on the full path
	IFileIdentifierPtr file (IID_FileIdentifier);
	file->Set(strFullPath);
	
	bool fileExists = false;
	file->ExistsOnDisk(fileExists);
	if(fileExists) { file->DeleteOnDisk(); }
	
	// If there is an existing fixture loaded, delete the old one and start from scratch
	if (fFixtureObject) { delete fFixtureObject; }
	
	// Create the newFixture
	fFixtureObject = new SceneData::GdtfFixture();
	
	TXString	vwName			(name);
	TXString	vwManufacturer (manufacturer);
	VWFC::Tools::VWUUID vwUuid = VWFC::Tools::VWUUID(uuid.a, uuid.b, uuid.c, uuid.d);
	
	fFixtureObject->SetName(vwName);
	fFixtureObject->SetManufacturer(vwManufacturer);
	fFixtureObject->SetGuid(vwUuid);
	
	fZipFile = IZIPFilePtr(IID_ZIPFile);
	fZipFile->OpenNewWrite(file, false);
	
	
	// Read From File
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::AddFileToGdtfFile(MvrString fullPath, ERessourceType resType)
{
	if(!fFixtureObject) { return kVCOMError_Failed; }
	if(!fZipFile)		{ return kVCOMError_Failed; }
	TXString strFullPath ( fullPath );

	// Create the file pointer on the full path
	IFileIdentifierPtr file (IID_FileIdentifier);
	file->Set(strFullPath);
	
	bool fileExisis = false;
	file->ExistsOnDisk(fileExisis);
	
	// Check if the file exists
	if (!fileExisis) { return kVCOMError_Failed; }
	
	TXString fileName; file->GetFileName(fileName);
	
    // Append the SubFoldername for resources.
    fileName = SceneData::SceneDataZip::GetResourceSubFolder(resType) + fileName;

	fZipFile->AddFile(fileName, file);	
	
	// Read From File
	return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::Close()
{
	if(!fFixtureObject) { return kVCOMError_Failed; }
	if(!fZipFile)		{ return kVCOMError_Failed; }
		
	fFixtureObject->ExportToFile(fZipFile);
	
	fZipFile->Close();
	
	// Read From File
	return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::ReadFromFile(IFileIdentifierPtr file, TXString gdtfFileName)
{
	// Store Full Path
    file->GetFileFullPath(fFullPath);

	// Check there is already a object in here
	if (fFixtureObject) { delete fFixtureObject; }
	
	// Create the new Object
	fFixtureObject = new SceneData::GdtfFixture( file, gdtfFileName );
	
	// Check if this was good
	if (!fFixtureObject) { return kVCOMError_Failed; }
	
	// Check if you can read it
	if ( ! fFixtureObject->IsReaded()) { return kVCOMError_InvalidArg; }
	
	// If everything is OK
	return kVCOMError_NoError;
}

MvrString VectorworksMVR::CGdtfFixtureImpl::GetName()
{
    if(!fFixtureObject) {return "";}
	
    return fFixtureObject->GetName().GetCharPtr();
}

MvrString VectorworksMVR::CGdtfFixtureImpl::GetShortName()
{
    if(!fFixtureObject) {return "";}
	
    return fFixtureObject->GetShortName().GetCharPtr();
}

MvrString VectorworksMVR::CGdtfFixtureImpl::GetLongName()
{
    if(!fFixtureObject) {return "";}
	
    return fFixtureObject->GetLongName().GetCharPtr();
}

MvrString VectorworksMVR::CGdtfFixtureImpl::GetManufacturer()
{
    if(!fFixtureObject) {return "";}
	
    return fFixtureObject->GetManufacturer().GetCharPtr();
}

MvrString VectorworksMVR::CGdtfFixtureImpl::GetFixtureTypeDescription()
{
    if(!fFixtureObject) {return "";}
	
    return fFixtureObject->GetFixtureTypeDescription().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetFixtureGUID(VectorworksMVR::MvrUUID &uuid)
{
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
    
    fFixtureObject->GetGuid().GetUUID(uuid.a, uuid.b, uuid.c, uuid.d);
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetLinkedFixtureGUID(VectorworksMVR::MvrUUID &uuid)
{
	if(!fFixtureObject) {return kVCOMError_NotInitialized;}
	
	if(fFixtureObject->HasLinkedGuid() == false)
	{
		uuid.a = 0;
		uuid.b = 0;
		uuid.c = 0;
		uuid.d = 0;
        return kVCOMError_NotSet;
	}
	
	fFixtureObject->GetLinkedGuid().GetUUID(uuid.a, uuid.b, uuid.c, uuid.d);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::HasLinkedFixtureGUID(bool &uuid)
{
	if(!fFixtureObject) {return kVCOMError_NotInitialized;}
	
	uuid = fFixtureObject->HasLinkedGuid();
	
	return kVCOMError_NoError;
}

MvrString VectorworksMVR::CGdtfFixtureImpl::GetFixtureThumbnail()
{
    if(!fFixtureObject) {return "";}
	
    
    return fFixtureObject->GetThumbnailName().GetCharPtr();
}

MvrString VectorworksMVR::CGdtfFixtureImpl::GetFixtureThumbnail_PNG_FullPath()
{
	if(!fFixtureObject) {return "";}
	
	
	return fFixtureObject->GetPNGThumnailFullPath().GetCharPtr();
}

MvrString VCOM_CALLTYPE VectorworksMVR::CGdtfFixtureImpl::GetFixtureThumbnail_SVG_FullPath()
{
	if(!fFixtureObject) {return "";}
	
	
	return fFixtureObject->GetSVGThumnailFullPath().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::SetFixtureTypeDescription(MvrString descrip)
{
	if(!fFixtureObject) {return kVCOMError_NotInitialized;}
	
	TXString vwDescrp (descrip);
	fFixtureObject->SetFixtureTypeDescription(vwDescrp);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::SetShortName(MvrString shortName)
{
	if(!fFixtureObject) {return kVCOMError_NotInitialized;}
	
	TXString vwName (shortName);
	fFixtureObject->SetShortName(vwName);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::SetLongName(MvrString longname)
{
	if(!fFixtureObject) {return kVCOMError_NotInitialized;}
	
	TXString vwName (longname);
	fFixtureObject->SetLongName(vwName);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::SetFixtureThumbnail(MvrString thubnail)
{
	if(!fFixtureObject) {return kVCOMError_NotInitialized;}
	
	TXString vwThumb (thubnail);
	fFixtureObject->SetThumbnailName(vwThumb);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::SetLinkedFixtureGUID(const MvrUUID& uuid)
{
	if(!fFixtureObject) {return kVCOMError_NotInitialized;}
	
	VWFC::Tools::VWUUID vwUuid = VWFC::Tools::VWUUID(uuid.a, uuid.b, uuid.c, uuid.d);
	fFixtureObject->SetLinkedGuid(vwUuid);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetActivationGroupCount(size_t &count)
{
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
    
    count = fFixtureObject->GetActivationGroupArray().size();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetActivationGroupAt(size_t at, VectorworksMVR::IGdtfActivationGroup **activationGroup)
{
    // Check if Set
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
    
    // Check if no Overflow
    if (at >=  fFixtureObject->GetActivationGroupArray().size()) { return kVCOMError_OutOfBounds;  }
    
    
    SceneData::GdtfActivationGroup* gdtfActivationGroup = fFixtureObject->GetActivationGroupArray()[at];    
    
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfActivationGroupImpl* pActivationGroupObj = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfActivationGroup, (IVWUnknown**) & pActivationGroupObj)))
    {
        // Check Casting
        CGdtfActivationGroupImpl* pResultInterface = dynamic_cast<CGdtfActivationGroupImpl* >(pActivationGroupObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfActivationGroup);
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
    if (*activationGroup)
    {
        (*activationGroup)->Release();
        *activationGroup		= NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *activationGroup	= pActivationGroupObj;
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::CreateActivationGroup(MvrString name, IGdtfActivationGroup** activationGroup)
{
	// Check if Set
	if(!fFixtureObject) {return kVCOMError_NotInitialized;}
	
	TXString vwName(name);
	
	SceneData::GdtfActivationGroup* gdtfActivationGroup = fFixtureObject->AddActivationGroup(vwName);
	
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfActivationGroupImpl* pActivationGroupObj = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfActivationGroup, (IVWUnknown**) & pActivationGroupObj)))
	{
		// Check Casting
		CGdtfActivationGroupImpl* pResultInterface = dynamic_cast<CGdtfActivationGroupImpl* >(pActivationGroupObj);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(gdtfActivationGroup);
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
	if (*activationGroup)
	{
		(*activationGroup)->Release();
		*activationGroup		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*activationGroup	= pActivationGroupObj;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetFeatureGroupCount(size_t &count)
{
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
    
    count = fFixtureObject->GetFeatureGroupArray().size();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetFeatureGroupAt(size_t at, VectorworksMVR::IGdtfFeatureGroup **featureGroup)
{
    // Check if Set
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
    
    // Check if no Overflow
    if (at >=  fFixtureObject->GetFeatureGroupArray().size()) { return kVCOMError_OutOfBounds;  }
    
    
    SceneData::GdtfFeatureGroup* gdtfFeatureGroup = fFixtureObject->GetFeatureGroupArray()[at];
    
    
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfFeatureGroupImpl* pFeatureGroupObj = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfFeatureGroup, (IVWUnknown**) & pFeatureGroupObj)))
    {
        // Check Casting
        CGdtfFeatureGroupImpl* pResultInterface = dynamic_cast<CGdtfFeatureGroupImpl* >(pFeatureGroupObj);
        if (pResultInterface)
        {
            pResultInterface->setPointer(gdtfFeatureGroup);
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
    if (*featureGroup)
    {
        (*featureGroup)->Release();
        *featureGroup		= NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *featureGroup	= pFeatureGroupObj;
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::CreateFeatureGroup(MvrString name, MvrString prettyName, IGdtfFeatureGroup** featureGroup)
{
	// Check if Set
	if(!fFixtureObject) {return kVCOMError_NotInitialized;}
	
	TXString vwName		(name);
	TXString vwPretty	(prettyName);
	
	SceneData::GdtfFeatureGroup* gdtfFeatureGroup = fFixtureObject->AddFeatureGroup(vwName, vwPretty);
	
	
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfFeatureGroupImpl* pFeatureGroupObj = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfFeatureGroup, (IVWUnknown**) & pFeatureGroupObj)))
	{
		// Check Casting
		CGdtfFeatureGroupImpl* pResultInterface = dynamic_cast<CGdtfFeatureGroupImpl* >(pFeatureGroupObj);
		if (pResultInterface)
		{
			pResultInterface->setPointer(gdtfFeatureGroup);
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
	if (*featureGroup)
	{
		(*featureGroup)->Release();
		*featureGroup		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*featureGroup	= pFeatureGroupObj;
	
	return kVCOMError_NoError;
}
VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetAttributeCount(size_t &count)
{
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
    
    count = fFixtureObject->GetAttributeArray().size();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetAttributeAt(size_t at, VectorworksMVR::IGdtfAttribute **attribute)
{
    // Check if Set
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
    
    // Check if no Overflow
    if (at >=  fFixtureObject->GetAttributeArray().size()) { return kVCOMError_OutOfBounds;  }
    
    
    SceneData::GdtfAttribute* gdtfAttribute = fFixtureObject->GetAttributeArray()[at];
    
    
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

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::CreateAttribute(MvrString name, MvrString prettyName, IGdtfAttribute** attribute)
{
	// Check if Set
	if(!fFixtureObject) {return kVCOMError_NotInitialized;}
	
	TXString vwName		(name);
	TXString vwPretty	(prettyName);
	
	SceneData::GdtfAttribute* gdtfAttribute = fFixtureObject->AddAttribute(vwName, vwPretty);
	
	
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

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetWheelCount(size_t &count)
{
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
    
    count = fFixtureObject->GetWheelArray().size();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetWheelAt(size_t at, VectorworksMVR::IGdtfWheel ** wheel)
{
    // Check if Set
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
    
    // Check if no Overflow
    if (at >=  fFixtureObject->GetWheelArray().size()) { return kVCOMError_OutOfBounds;  }
    
    
    SceneData::GdtfWheel* gdtfWheel = fFixtureObject->GetWheelArray()[at];
   
    
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfWheelImpl* pWheelObj = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfWheel, (IVWUnknown**) & pWheelObj)))
    {
        // Check Casting
        CGdtfWheelImpl* pResultInterface = dynamic_cast<CGdtfWheelImpl* >(pWheelObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfWheel);
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
    if (*wheel)
    {
        (*wheel)->Release();
        *wheel		= NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *wheel		= pWheelObj;
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::CreateWheel(MvrString name, IGdtfWheel** wheel)
{
	// Check if Set
	if(!fFixtureObject) {return kVCOMError_NotInitialized;}
		
	SceneData::GdtfWheel* gdtfWheel = fFixtureObject->AddWheel(name);
		
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfWheelImpl* pWheelObj = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfWheel, (IVWUnknown**) & pWheelObj)))
	{
		// Check Casting
		CGdtfWheelImpl* pResultInterface = dynamic_cast<CGdtfWheelImpl* >(pWheelObj);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(gdtfWheel);
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
	if (*wheel)
	{
		(*wheel)->Release();
		*wheel		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*wheel		= pWheelObj;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetModelCount(size_t &count)
{
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
	
    count = fFixtureObject->GetModelArray().size();
	
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetModelAt(size_t at, VectorworksMVR::IGdtfModel **model)
{
    // Check if Set
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
    
    // Check if no Overflow
    if (at >=  fFixtureObject->GetModelArray().size()) { return kVCOMError_OutOfBounds;  }
    
    
    SceneData::GdtfModel* gdtfModel = fFixtureObject->GetModelArray()[at];
    
    
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfModelImpl* pModelObj = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfModel, (IVWUnknown**) & pModelObj)))
    {
        // Check Casting
        CGdtfModelImpl* pResultInterface = dynamic_cast<CGdtfModelImpl* >(pModelObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfModel);
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
    if (*model)
    {
        (*model)->Release();
        *model		= NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *model		= pModelObj;
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::CreateModel(MvrString name, IGdtfModel** model)
{
	// Check if Set
	if(!fFixtureObject) {return kVCOMError_NotInitialized;}
	
	TXString vwName (name);
	
	SceneData::GdtfModel* gdtfModel = fFixtureObject->AddModel(vwName);
	
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfModelImpl* pModelObj = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfModel, (IVWUnknown**) & pModelObj)))
	{
		// Check Casting
		CGdtfModelImpl* pResultInterface = dynamic_cast<CGdtfModelImpl* >(pModelObj);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(gdtfModel);
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
	if (*model)
	{
		(*model)->Release();
		*model		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*model		= pModelObj;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetGeometryCount(size_t &count)
{
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
	
    count = fFixtureObject->GetGeometryArray().size();
	
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetGeometryAt(size_t at, VectorworksMVR::IGdtfGeometry **geometry)
{
    // Check if Set
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
    
    // Check if no Overflow
    if (at >=  fFixtureObject->GetGeometryArray().size()) { return kVCOMError_OutOfBounds;  }
    
    
    SceneData::GdtfGeometry* gdtfGeometry = fFixtureObject->GetGeometryArray()[at];
    
    
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfGeometryImpl* pGeometryObj = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfGeometry, (IVWUnknown**) & pGeometryObj)))
    {
        // Check Casting
        CGdtfGeometryImpl* pResultInterface = dynamic_cast<CGdtfGeometryImpl* >(pGeometryObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfGeometry);
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
    if (*geometry)
    {
        (*geometry)->Release();
        *geometry		= NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *geometry		= pGeometryObj;
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::CreateGeometry(EGdtfObjectType type, MvrString name, IGdtfModel* model, const STransformMatrix& mat, IGdtfGeometry** geometry)
{
	// Check if Set
	if(!fFixtureObject) { return kVCOMError_NotInitialized;}
		
    //---------------------------------------------------------------------------
	// Extract Model
	SceneData::GdtfModelPtr scModel = nullptr;

	CGdtfModelImpl* modelInterface = dynamic_cast<CGdtfModelImpl*>(model);
	if( modelInterface)
	{
		scModel = modelInterface->GetPointer();
	}
	
	
	//---------------------------------------------------------------------------
	// Create geometry
	TXString			vwName (name);
	VWTransformMatrix	ma;
	GdtfUtil::ConvertMatrix(mat, ma);
	
	SceneData::GdtfGeometry* gdtfGeometry = nullptr;
	
	switch (type)
	{
		case eGdtfGeometryReference:	gdtfGeometry = fFixtureObject->AddGeometryReference(vwName, scModel, ma); break;
		case eGdtfGeometryLamp:			gdtfGeometry = fFixtureObject->AddGeometryWithLamp(	vwName, scModel, ma); break;
		case eGdtfGeometryAxis:			gdtfGeometry = fFixtureObject->AddGeometryWithAxis(	vwName, scModel, ma); break;
		case eGdtfGeometryShaperFilter:	gdtfGeometry = fFixtureObject->AddGeometryShaper(	vwName, scModel, ma); break;
		case eGdtfGeometryColorFilter:	gdtfGeometry = fFixtureObject->AddGeometryColor(	vwName, scModel, ma); break;
		case eGdtfGeometryGoboFilter:	gdtfGeometry = fFixtureObject->AddGeometryGobo(		vwName, scModel, ma); break;
		case eGdtfGeometryBeamFilter:	gdtfGeometry = fFixtureObject->AddGeometryBeam(		vwName, scModel, ma); break;
		case eGdtfGeometry:				gdtfGeometry = fFixtureObject->AddGeometry(			vwName, scModel, ma); break;

		default:
			return kVCOMError_InvalidArg;
			break;
	}
	
	if ( ! gdtfGeometry) { return kVCOMError_Failed; }
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfGeometryImpl* pGeometryObj = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfGeometry, (IVWUnknown**) & pGeometryObj)))
	{
		// Check Casting
		CGdtfGeometryImpl* pResultInterface = dynamic_cast<CGdtfGeometryImpl* >(pGeometryObj);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(gdtfGeometry);
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
	if (*geometry)
	{
		(*geometry)->Release();
		*geometry		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*geometry		= pGeometryObj;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetDmxModeCount(size_t &count)
{
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
    
    count = fFixtureObject->GetDmxModeArray().size();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetDmxModeAt(size_t at, VectorworksMVR::IGdtfDmxMode **dmxMode)
{
    // Check if Set
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
    
    // Check if no Overflow
    if (at >=  fFixtureObject->GetDmxModeArray().size()) { return kVCOMError_OutOfBounds;  }
    
    
    SceneData::GdtfDmxMode* gdtfDmxMode = fFixtureObject->GetDmxModeArray()[at];
    
    
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfDmxModeImpl* pDmxModeObj = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfDmxMode, (IVWUnknown**) & pDmxModeObj)))
    {
        // Check Casting
        CGdtfDmxModeImpl* pResultInterface = dynamic_cast<CGdtfDmxModeImpl* >(pDmxModeObj);
        if (pResultInterface)
        {
            pResultInterface->setPointer(gdtfDmxMode);
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
    if (*dmxMode)
    {
        (*dmxMode)->Release();
        *dmxMode		= NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *dmxMode		= pDmxModeObj;
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::CreateDmxMode(MvrString name, IGdtfDmxMode** dmxMode)
{
	// Check if Set
	if(!fFixtureObject) {return kVCOMError_NotInitialized;}
	
	TXString vwName (name);
	
	SceneData::GdtfDmxMode* gdtfDmxMode = fFixtureObject->AddDmxMode(vwName);
	
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfDmxModeImpl* pDmxModeObj = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfDmxMode, (IVWUnknown**) & pDmxModeObj)))
	{
		// Check Casting
		CGdtfDmxModeImpl* pResultInterface = dynamic_cast<CGdtfDmxModeImpl* >(pDmxModeObj);
		if (pResultInterface)
		{
			pResultInterface->setPointer(gdtfDmxMode);
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
	if (*dmxMode)
	{
		(*dmxMode)->Release();
		*dmxMode		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*dmxMode		= pDmxModeObj;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetRevisionCount(size_t &count)
{
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
	
    count = fFixtureObject->GetRevisionArray().size();
	
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetRevisionAt(size_t at, VectorworksMVR::IGdtfRevision **revision)
{
    // Check if Set
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
    
    // Check if no Overflow
    if (at >=  fFixtureObject->GetRevisionArray().size()) { return kVCOMError_OutOfBounds;  }
    
    
    SceneData::GdtfRevision* gdtfRevision = fFixtureObject->GetRevisionArray()[at];
    
    
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfRevisionImpl* pRevisionObj = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfRevision, (IVWUnknown**) & pRevisionObj)))
    {
        // Check Casting
        CGdtfRevisionImpl* pResultInterface = dynamic_cast<CGdtfRevisionImpl* >(pRevisionObj);
        if (pResultInterface)
        {
            pResultInterface->setPointer(gdtfRevision);
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
    if (*revision)
    {
        (*revision)->Release();
        *revision		= NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *revision		= pRevisionObj;
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::CreateRevision(MvrString text, STime date, IGdtfRevision** revision)
{
	// Check if Set
	if(!fFixtureObject) {return kVCOMError_NotInitialized;}
	
	TXString vwText (text);
	
	SceneData::GdtfRevision* gdtfRevision = fFixtureObject->AddRevision(vwText, date);
	
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfRevisionImpl* pRevisionObj = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfRevision, (IVWUnknown**) & pRevisionObj)))
	{
		// Check Casting
		CGdtfRevisionImpl* pResultInterface = dynamic_cast<CGdtfRevisionImpl* >(pRevisionObj);
		if (pResultInterface)
		{
			pResultInterface->setPointer(gdtfRevision);
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
	if (*revision)
	{
		(*revision)->Release();
		*revision		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*revision		= pRevisionObj;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetPresetCount(size_t &count)
{
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
	
    count = fFixtureObject->GetPresetArray().size();
	
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetPresetAt(size_t at, VectorworksMVR::IGdtfUserPreset **preset)
{
    // Check if Set
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
    
    // Check if no Overflow
    if (at >=  fFixtureObject->GetPresetArray().size()) { return kVCOMError_OutOfBounds;  }
    
    
    SceneData::GdtfUserPreset* gdtfPreset = fFixtureObject->GetPresetArray()[at];
    
    
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfUserPresetImpl* pPresetObj = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfUserPreset, (IVWUnknown**) & pPresetObj)))
    {
        // Check Casting
        CGdtfUserPresetImpl* pResultInterface = dynamic_cast<CGdtfUserPresetImpl* >(pPresetObj);
        if (pResultInterface)
        {
            pResultInterface->setPointer(gdtfPreset);
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
    if (*preset)
    {
        (*preset)->Release();
        *preset		= NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *preset		= pPresetObj;
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::CreatePreset(VectorworksMVR::IGdtfUserPreset **preset)
{
	// Check if Set
	if(!fFixtureObject) {return kVCOMError_NotInitialized;}
	
	SceneData::GdtfUserPreset* gdtfPreset = fFixtureObject->AddUserPreset();
	
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfUserPresetImpl* pPresetObj = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfUserPreset, (IVWUnknown**) & pPresetObj)))
	{
		// Check Casting
		CGdtfUserPresetImpl* pResultInterface = dynamic_cast<CGdtfUserPresetImpl* >(pPresetObj);
		if (pResultInterface)
		{
			pResultInterface->setPointer(gdtfPreset);
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
	if (*preset)
	{
		(*preset)->Release();
		*preset		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*preset		= pPresetObj;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetRDM(IGdtf_FTRDM ** value)
{
	// Check if Set
	if (!fFixtureObject) { return kVCOMError_NotInitialized; }
	

	SceneData::GdtfFTRDMPtr gdtfRdm = fFixtureObject->GetProtocollContainer().GetRDM();
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtf_FTRDMImpl* pRdm = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfTRDM, (IVWUnknown**)& pRdm)))
	{
		// Check Casting
		CGdtf_FTRDMImpl* pResultInterface = dynamic_cast<CGdtf_FTRDMImpl*>(pRdm);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(gdtfRdm);
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
	if (*value)
	{
		(*value)->Release();
		*value = NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*value = pRdm;
	
	return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::CreateRDM(VectorworksMVR::IGdtf_FTRDM ** outFTRDM)
{
	// Check if Set
	if (!fFixtureObject) { return kVCOMError_NotInitialized; }
	
	
	SceneData::GdtfFTRDMPtr gdtfRdm = fFixtureObject->GetProtocollContainer().CreateRDM();
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtf_FTRDMImpl* pRdm = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfTRDM, (IVWUnknown**)& pRdm)))
	{
		// Check Casting
		CGdtf_FTRDMImpl* pResultInterface = dynamic_cast<CGdtf_FTRDMImpl*>(pRdm);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(gdtfRdm);
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
	if (*outFTRDM)
	{
		(*outFTRDM)->Release();
		*outFTRDM = NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*outFTRDM = pRdm;
	
	return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetColorSpace(VectorworksMVR::IGdtfColorSpace **outColorSpace)
{
    // Check Pointer
    if (!fFixtureObject) { return kVCOMError_NotInitialized; }

    //---------------------------------------------------------------------------
    // Initialize Object
    SceneData::GdtfColorSpace*	gdtfColorSpace = fFixtureObject->GetPhysicalDesciptionsContainer().GetColorSpace();
    if (!gdtfColorSpace) { return kVCOMError_NotSet; }

    CGdtfColorSpaceImpl*		pColorSpaceObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfColorSpace, (IVWUnknown**)& pColorSpaceObj)))
    {
        // Check Casting
        CGdtfColorSpaceImpl* pResultInterface = dynamic_cast<CGdtfColorSpaceImpl*>(pColorSpaceObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfColorSpace);
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
    if (*outColorSpace)
    {
        (*outColorSpace)->Release();
        *outColorSpace = NULL;
    }

    //---------------------------------------------------------------------------
    // Set Out Value
    *outColorSpace = pColorSpaceObj;

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetEmitterCount(size_t &count)
{
    if (!fFixtureObject) { return kVCOMError_NotInitialized; }

    count = fFixtureObject->GetPhysicalDesciptionsContainer().GetPhysicalEmitterArray().size();

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetEmitterAt(size_t at, VectorworksMVR::IGdtfPhysicalEmitter** value)
{
    // Check if Set
    if (!fFixtureObject) { return kVCOMError_NotInitialized; }

    // Check if no Overflow
    if (at >= fFixtureObject->GetPhysicalDesciptionsContainer().GetPhysicalEmitterArray().size()) { return kVCOMError_OutOfBounds; }


    SceneData::GdtfPhysicalEmitter* gdtfEmitter = fFixtureObject->GetPhysicalDesciptionsContainer().GetPhysicalEmitterArray()[at];
    
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfPhysicalEmitterImpl* pEmitterObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfPhysicalEmitter, (IVWUnknown**)& pEmitterObj)))
    {
        // Check Casting
        CGdtfPhysicalEmitterImpl* pResultInterface = dynamic_cast<CGdtfPhysicalEmitterImpl*>(pEmitterObj);
        if (pResultInterface)
        {
            pResultInterface->setPointer(gdtfEmitter);
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
    if (*value)
    {
        (*value)->Release();
        *value = NULL;
    }

    //---------------------------------------------------------------------------
    // Set Out Value
    *value = pEmitterObj;

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::CreateEmitter(MvrString name, CieColor color, VectorworksMVR::IGdtfPhysicalEmitter **outVal)
{
    // Check if Set
    if (!fFixtureObject) { return kVCOMError_NotInitialized; }


    SceneData::GdtfPhysicalEmitter* gdtfEmitter = fFixtureObject->GetPhysicalDesciptionsContainer().AddEmitter(name, SceneData::GdtfConverter::ConvertCColor(color) );

    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfPhysicalEmitterImpl* pEmitterObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfPhysicalEmitter, (IVWUnknown**)& pEmitterObj)))
    {
        // Check Casting
        CGdtfPhysicalEmitterImpl* pResultInterface = dynamic_cast<CGdtfPhysicalEmitterImpl*>(pEmitterObj);
        if (pResultInterface)
        {
            pResultInterface->setPointer(gdtfEmitter);
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
    if (*outVal)
    {
        (*outVal)->Release();
        *outVal = NULL;
    }

    //---------------------------------------------------------------------------
    // Set Out Value
    *outVal = pEmitterObj;

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetFilterCount(size_t &count)
{
    if (!fFixtureObject) { return kVCOMError_NotInitialized; }

    count = fFixtureObject->GetPhysicalDesciptionsContainer().GetFilterArray().size();

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetFilterAt(size_t at, VectorworksMVR::IGdtfFilter** value)
{
    // Check if Set
    if (!fFixtureObject) { return kVCOMError_NotInitialized; }

    // Check if no Overflow
    if (at >=  fFixtureObject->GetPhysicalDesciptionsContainer().GetFilterArray().size()) { return kVCOMError_OutOfBounds; }


    SceneData::GdtfFilter* gdtfFilter = fFixtureObject->GetPhysicalDesciptionsContainer().GetFilterArray()[at];


    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfFilterImpl* pFilterObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfFilter, (IVWUnknown**)& pFilterObj)))
    {
        // Check Casting
        CGdtfFilterImpl* pResultInterface = dynamic_cast<CGdtfFilterImpl*>(pFilterObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfFilter);
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
    if (*value)
    {
        (*value)->Release();
        *value = NULL;
    }

    //---------------------------------------------------------------------------
    // Set Out Value
    *value = pFilterObj;

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::CreateFilter(MvrString name, CieColor color, VectorworksMVR::IGdtfFilter **outVal)
{
    // Check if Set
    if (!fFixtureObject) { return kVCOMError_NotInitialized; }
    
    SceneData::GdtfFilter* gdtfFilter = fFixtureObject->GetPhysicalDesciptionsContainer().AddFilter(name, SceneData::GdtfConverter::ConvertCColor(color));

    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfFilterImpl* pFilterObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfFilter, (IVWUnknown**)& pFilterObj)))
    {
        // Check Casting
        CGdtfFilterImpl* pResultInterface = dynamic_cast<CGdtfFilterImpl*>(pFilterObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfFilter);
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
    if (*outVal)
    {
        (*outVal)->Release();
        *outVal = NULL;
    }

    //---------------------------------------------------------------------------
    // Set Out Value
    *outVal = pFilterObj;

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetDMXProfileCount(size_t &count)
{
    if (!fFixtureObject) { return kVCOMError_NotInitialized; }

    count = fFixtureObject->GetPhysicalDesciptionsContainer().GetDmxProfileArray().size();

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetDMXProfileAt(size_t at, VectorworksMVR::IGdtfDMXProfile** value)
{
    // Check if Set
    if (!fFixtureObject) { return kVCOMError_NotInitialized; }

    // Check if no Overflow
    if (at >= fFixtureObject->GetPhysicalDesciptionsContainer().GetDmxProfileArray().size()) { return kVCOMError_OutOfBounds; }


    SceneData::GdtfDMXProfile* gdtfDMXProfile = fFixtureObject->GetPhysicalDesciptionsContainer().GetDmxProfileArray()[at];


    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfDMXProfileImpl* pDMXProfileObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfDMXProfile, (IVWUnknown**)& pDMXProfileObj)))
    {
        // Check Casting
        CGdtfDMXProfileImpl* pResultInterface = dynamic_cast<CGdtfDMXProfileImpl*>(pDMXProfileObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfDMXProfile);
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
    if (*value)
    {
        (*value)->Release();
        *value = NULL;
    }

    //---------------------------------------------------------------------------
    // Set Out Value
    *value = pDMXProfileObj;

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::CreateDMXProfile(VectorworksMVR::IGdtfDMXProfile **outVal)
{
    // Check if Set
    if (!fFixtureObject) { return kVCOMError_NotInitialized; }


    SceneData::GdtfDMXProfile* gdtfDMXProfile = fFixtureObject->GetPhysicalDesciptionsContainer().AddDmxProfile();

    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfDMXProfileImpl* pDMXProfileObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfDMXProfile, (IVWUnknown**)& pDMXProfileObj)))
    {
        // Check Casting
        CGdtfDMXProfileImpl* pResultInterface = dynamic_cast<CGdtfDMXProfileImpl*>(pDMXProfileObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfDMXProfile);
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
    if (*outVal)
    {
        (*outVal)->Release();
        *outVal = NULL;
    }

    //---------------------------------------------------------------------------
    // Set Out Value
    *outVal = pDMXProfileObj;

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetCRIGroupCount(size_t &count)
{
    if (!fFixtureObject) { return kVCOMError_NotInitialized; }

    count = fFixtureObject->GetPhysicalDesciptionsContainer().GetCRIGroupArray().size();

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetCRIGroupAt(size_t at, VectorworksMVR::IGdtfCRIGroup** value)
{
    // Check if Set
    if (!fFixtureObject) { return kVCOMError_NotInitialized; }

    // Check if no Overflow
    if (at >= fFixtureObject->GetPhysicalDesciptionsContainer().GetCRIGroupArray().size()) { return kVCOMError_OutOfBounds; }


    SceneData::GdtfCRIGroup* gdtfCRIGroup = fFixtureObject->GetPhysicalDesciptionsContainer().GetCRIGroupArray()[at];


    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfCRIGroupImpl* pCRIGroupObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfCRIGroup, (IVWUnknown**)& pCRIGroupObj)))
    {
        // Check Casting
        CGdtfCRIGroupImpl* pResultInterface = dynamic_cast<CGdtfCRIGroupImpl*>(pCRIGroupObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfCRIGroup);
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
    if (*value)
    {
        (*value)->Release();
        *value = NULL;
    }

    //---------------------------------------------------------------------------
    // Set Out Value
    *value = pCRIGroupObj;

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::CreateCRIGroup(double colorTemp, VectorworksMVR::IGdtfCRIGroup **outVal)
{
    // Check if Set
    if (!fFixtureObject) { return kVCOMError_NotInitialized; }


    SceneData::GdtfCRIGroup* gdtfCRIGroup = fFixtureObject->GetPhysicalDesciptionsContainer().AddCRIGroup(colorTemp);

    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfCRIGroupImpl* pCRIGroupObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfCRIGroup, (IVWUnknown**)& pCRIGroupObj)))
    {
        // Check Casting
        CGdtfCRIGroupImpl* pResultInterface = dynamic_cast<CGdtfCRIGroupImpl*>(pCRIGroupObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfCRIGroup);
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
    if (*outVal)
    {
        (*outVal)->Release();
        *outVal = NULL;
    }

    //---------------------------------------------------------------------------
    // Set Out Value
    *outVal = pCRIGroupObj;

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetParsingErrorCount(size_t &count)
{
    if (!fFixtureObject) { return kVCOMError_NotInitialized; }

    count = fFixtureObject->GetParsingErrorArray().size();

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetParsingErrorAt(size_t at, IGdtfXmlParsingError** value)
{
    // Check if Set
    if (!fFixtureObject) { return kVCOMError_NotInitialized; }

    // Check if no Overflow
    if (at >= fFixtureObject->GetParsingErrorArray().size()) { return kVCOMError_OutOfBounds; }


    GdtfParsingError* gdtfParsingError = & fFixtureObject->GetParsingErrorArray()[at];
    
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfXmlParsingErrorImpl* pParsingErrorObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfXmlParsingError, (IVWUnknown**)& pParsingErrorObj)))
    {
        // Check Casting
        CGdtfXmlParsingErrorImpl* pResultInterface = dynamic_cast<CGdtfXmlParsingErrorImpl*>(pParsingErrorObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfParsingError);
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
    if (*value)
    {
        (*value)->Release();
        *value = NULL;
    }

    //---------------------------------------------------------------------------
    // Set Out Value
    *value = pParsingErrorObj;

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetImageRessourcesCount(size_t& count)
{
    if (!fFixtureObject) { return kVCOMError_NotInitialized; }

    count = fFixtureObject->GetAttachedFileCount();

    return kVCOMError_NoError;
}

MvrString VectorworksMVR::CGdtfFixtureImpl::GetImageRessourcesPathAt(size_t at)
{
    if (!fFixtureObject) { return ""; }

    TXString* fullPathPtr = nullptr;

    if(fFixtureObject->GetAttachedFileCountAt(at, fullPathPtr) && fullPathPtr)
    {
        return fullPathPtr->GetCharPtr();
    }


    return "";
}

VCOMError VectorworksMVR::CGdtfFixtureImpl::GetBufferLength(size_t& length)
{
    length = 0;
    if (!fFixtureObject) { return kVCOMError_NotInitialized; }

    IFileIdentifierPtr file (IID_FileIdentifier);
    file->Set(fFullPath);

    IRawOSFilePtr rawFile (IID_RawOSFile);

    if(VCOM_SUCCEEDED(rawFile->Open(file, true, false, false, false)))
    {
        Uint64 size = 0;
        rawFile->GetFileSize(size);
        length = size;
    }    

    if(length > 0)  { return kVCOMError_NoError; }

    return kVCOMError_Failed;
}

VCOMError VectorworksMVR::CGdtfFixtureImpl::ToBuffer(char* outBuffer)
{
    if (!fFixtureObject) { return kVCOMError_NotInitialized; }

    IFileIdentifierPtr file (IID_FileIdentifier);
    file->Set(fFullPath);

    IRawOSFilePtr rawFile (IID_RawOSFile);

    if(VCOM_SUCCEEDED(rawFile->Open(file, true, false, false, false)))
    {
        Uint64 size = 0;
        rawFile->GetFileSize(size);

        if(size > 0)
        {
            char* tempBuffer = new char[size + 1];
            rawFile->Read(0, size, tempBuffer);
            memcpy( tempBuffer,  outBuffer, size );
            delete[] tempBuffer;
            return kVCOMError_NoError;
        }
    }    

    return kVCOMError_Failed;
}

VCOMError VectorworksMVR::CGdtfFixtureImpl::FromBuffer(const char* buffer, size_t length)
{

    return kVCOMError_Failed;
}