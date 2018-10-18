//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "CGeometryProviderWrapper.h"
#include "GDTFManager.h"

namespace VectorworksMVR
{
    //----------------------------------------------------------------------------------------
    class CGdtfDmxModeImpl : public VectorworksMVR::VCOMImpl<IGdtfDmxMode>
    {
    public:
        CGdtfDmxModeImpl();
        virtual ~CGdtfDmxModeImpl();
        
        virtual MvrString VCOM_CALLTYPE     GetName();
		
		virtual VCOMError VCOM_CALLTYPE     GetGeometry(VectorworksMVR::IGdtfGeometry **geo);
		virtual VCOMError VCOM_CALLTYPE     SetGeometry(IGdtfGeometry* model);
		
        virtual VCOMError VCOM_CALLTYPE     GetDmxChannelCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE     GetDmxChannelAt(size_t at, IGdtfDmxChannel** channel);
		virtual VCOMError VCOM_CALLTYPE     CreateDmxChannel(MvrString name, IGdtfDmxChannel** channel);
		
        
        virtual VCOMError VCOM_CALLTYPE     GetDmxRelationCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE     GetDmxRelationAt(size_t at, IGdtfDmxRelation** relation);
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
		virtual void*	  VCOM_CALLTYPE     GetBoundObject();
		
    private:
        SceneData::GdtfDmxMode* fDmxMode;
        
    public:
        void setPointer(SceneData::GdtfDmxMode* dmxMode);
        
    };
    const VWIID IID_GdtfDmxMode = { 0x5433d14d, 0xe4c6, 0x4a39, {0xb0, 0x2a, 0xf0, 0xa6, 0x09, 0xe6, 0x3d, 0x56}};

}
