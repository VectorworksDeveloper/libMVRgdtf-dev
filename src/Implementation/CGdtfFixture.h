//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"
#include "GDTFManager.h"

namespace VectorworksMVR
{	
	//----------------------------------------------------------------------------------------
	class CGdtfFixtureImpl : public VCOMImpl<IGdtfFixture>
	{
	public:
		CGdtfFixtureImpl();
		virtual ~CGdtfFixtureImpl();
		
        virtual VCOMError VCOM_CALLTYPE		ReadFromFile(MvrString fullPath);
		
		virtual VCOMError VCOM_CALLTYPE		OpenForWrite(MvrString fullPath, MvrString name, MvrString manufacturer, const MvrUUID& uuid);
		virtual VCOMError VCOM_CALLTYPE		AddFileToGdtfFile(MvrString fullPath, ERessourceType resType);
		virtual VCOMError VCOM_CALLTYPE		Close();
		
        virtual MvrString VCOM_CALLTYPE		GetName();
        virtual MvrString VCOM_CALLTYPE		GetShortName();
		virtual MvrString VCOM_CALLTYPE		GetLongName();
        virtual MvrString VCOM_CALLTYPE     GetManufacturer();
        virtual MvrString VCOM_CALLTYPE     GetFixtureTypeDescription();
        virtual VCOMError VCOM_CALLTYPE     GetFixtureGUID(MvrUUID& uuid);
        
        virtual MvrString VCOM_CALLTYPE     GetFixtureThumbnail();
		virtual MvrString VCOM_CALLTYPE     GetFixtureThumbnail_PNG_FullPath();
        virtual MvrString VCOM_CALLTYPE     GetFixtureThumbnail_SVG_FullPath();

		virtual VCOMError VCOM_CALLTYPE		GetLinkedFixtureGUID(MvrUUID& uuid);
		virtual VCOMError VCOM_CALLTYPE		HasLinkedFixtureGUID(bool& has);
		
		
		virtual VCOMError VCOM_CALLTYPE     SetFixtureTypeDescription(MvrString descrip);
		virtual VCOMError VCOM_CALLTYPE		SetShortName(MvrString shortName);
		virtual VCOMError VCOM_CALLTYPE		SetLongName(MvrString longname);
		virtual VCOMError VCOM_CALLTYPE     SetFixtureThumbnail(MvrString thubnail);
		virtual VCOMError VCOM_CALLTYPE		SetLinkedFixtureGUID(const MvrUUID& uuid);
		
        
        virtual VCOMError VCOM_CALLTYPE		GetActivationGroupCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE		GetActivationGroupAt(size_t at, IGdtfActivationGroup** activationGroup);
		virtual VCOMError VCOM_CALLTYPE		CreateActivationGroup(MvrString name, IGdtfActivationGroup** activationGroup);
        
        virtual VCOMError VCOM_CALLTYPE		GetFeatureGroupCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE		GetFeatureGroupAt(size_t at, IGdtfFeatureGroup** featureGroup );
		virtual VCOMError VCOM_CALLTYPE		CreateFeatureGroup(MvrString name, MvrString prettyName, IGdtfFeatureGroup** featureGroup );
        
        virtual VCOMError VCOM_CALLTYPE		GetAttributeCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE		GetAttributeAt(size_t at, IGdtfAttribute** attribute);
		virtual VCOMError VCOM_CALLTYPE		CreateAttribute(MvrString name, MvrString prettyName, IGdtfAttribute** attribute);
        
        virtual VCOMError VCOM_CALLTYPE		GetWheelCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE		GetWheelAt(size_t at, IGdtfWheel** wheel );
		virtual VCOMError VCOM_CALLTYPE		CreateWheel(MvrString name, IGdtfWheel** wheel );
        
        virtual VCOMError VCOM_CALLTYPE		GetModelCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE		GetModelAt(size_t at, IGdtfModel** model );
		virtual VCOMError VCOM_CALLTYPE		CreateModel(MvrString name,IGdtfModel** model );
        
        virtual VCOMError VCOM_CALLTYPE		GetGeometryCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE		GetGeometryAt(size_t at, IGdtfGeometry** geometry);
		virtual VCOMError VCOM_CALLTYPE		CreateGeometry(EGdtfObjectType type, MvrString name, IGdtfModel* model, const STransformMatrix& mat, IGdtfGeometry** geometry);
        
        virtual VCOMError VCOM_CALLTYPE		GetDmxModeCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE		GetDmxModeAt(size_t at, IGdtfDmxMode** dmxMode );
		virtual VCOMError VCOM_CALLTYPE		CreateDmxMode(MvrString name, IGdtfDmxMode** dmxMode);
        
        virtual VCOMError VCOM_CALLTYPE		GetRevisionCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE		GetRevisionAt(size_t at, IGdtfRevision** revision );
		virtual VCOMError VCOM_CALLTYPE     CreateRevision(MvrString text, STime date, IGdtfRevision** revision);
        
        virtual VCOMError VCOM_CALLTYPE		GetPresetCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE		GetPresetAt(size_t at, IGdtfUserPreset** preset );
		virtual VCOMError VCOM_CALLTYPE     CreatePreset(IGdtfUserPreset** macro);
        
        virtual VCOMError VCOM_CALLTYPE		GetMacroCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE		GetMacroAt(size_t at, IGdtfMacro** macro );
		virtual VCOMError VCOM_CALLTYPE     CreateMacro(MvrString& name, IGdtfMacro** macro);        
		
		// Protocoll
		virtual VCOMError VCOM_CALLTYPE GetRDM(IGdtf_FTRDM ** newFTRDM);
		virtual VCOMError VCOM_CALLTYPE CreateRDM(VectorworksMVR::IGdtf_FTRDM ** outFTRDM);
        
		// Parsing Errors
        virtual VCOMError VCOM_CALLTYPE		GetParsingErrorCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE		GetParsingErrorAt(size_t at, IGdtfXmlParsingError** value);

		//Internal
		VectorworksMVR::VCOMError			ReadFromFile(IFileIdentifierPtr file);
		
	private:
        SceneData::GdtfFixture* fFixtureObject;
		IZIPFilePtr				fZipFile;
	};
	

}
