#pragma once


// Type defs
#ifndef _GS_TYPES_
	typedef int8_t		Sint8;
	typedef	int16_t		Sint16;
	typedef	int32_t		Sint32;
	typedef int64_t		Sint64;
	typedef uint8_t		Uint8;
	typedef	uint16_t	Uint16;
	typedef	uint32_t	Uint32;
	typedef uint64_t	Uint64;
#endif

typedef  const char * MvrString;

#include "GDTFPrefix.h"
namespace VectorworksMVR
{
	//-------------------------------------------------------------------------------------------------------------
	struct STransformMatrix
	{
		double ux,uy,uz;
		double vx,vy,vz;
		double wx,wy,wz;
		double ox,oy,oz;
	};
	
	struct SDmxAdress
	{
		size_t fAbsuluteAdress;
		size_t fBreakId;
	};
	
	struct CieColor
	{
		double fx;
		double fy;
		double f_Y;
	};

	struct RGBColor
	{
		Uint16 r, g, b;
	};
	
	struct MvrUUID
	{
		MvrUUID(Uint32 a,Uint32 b,Uint32 c,Uint32 d) { this->a = a; this->b = b; this->c = c; this->d = d;}
		Uint32 a, b, c, d;
	};
	
	//-------------------------------------------------------------------------------------------------------------
	// Predefines for classes
	class ISymDef;
	class IMediaRessourceVectorInterface;
	class IGdtfFixture;
	class IGdtfAttribute;
    class IGdtfPhysicalEmitter;
    class IGdtfMacroDMXStep;
    class IGdtfMacroDMXValue;
    class IGdtfMacroVisualStep;
    class IGdtfMacroVisualValue;
    class IGDtfIGdtfRDMAbsentNotification;
    class IGdtfRDMAbsentNotification;
    class IGdtfRDMParameterNotification;
    class IGdtf_FTRDM;
	class IGdtfRDMParameter;

	//-------------------------------------------------------------------------------------------------------------
	class DYNAMIC_ATTRIBUTE ISceneDataProvider : public IVWUnknown
	{
	public:
		virtual VCOMError VCOM_CALLTYPE		AddKeyValue(MvrString key, MvrString value) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetKeyValueCount(size_t& outVal) = 0;
		virtual MvrString VCOM_CALLTYPE		GetKeyAt(size_t at) = 0;
		virtual MvrString VCOM_CALLTYPE		GetValueAt(size_t at) = 0;
	};
	typedef VCOMPtr<ISceneDataProvider>	ISceneDataProviderPtr;
	
	//-------------------------------------------------------------------------------------------------------------
	class DYNAMIC_ATTRIBUTE IPosition : public IVWUnknown
	{
	public:
		virtual MvrString VCOM_CALLTYPE		GetName() = 0;
		virtual VCOMError VCOM_CALLTYPE		GetGuid(MvrUUID& guid) = 0;
	};
	typedef VCOMPtr<IPosition>	IPositionPtr;
	
	//-------------------------------------------------------------------------------------------------------------
	class DYNAMIC_ATTRIBUTE IClass : public IVWUnknown
	{
	public:
		virtual MvrString VCOM_CALLTYPE		GetName() = 0;
		virtual VCOMError VCOM_CALLTYPE		GetGuid(MvrUUID& guid) = 0;
	};
	typedef VCOMPtr<IClass>	IClassPtr;
	

	//-------------------------------------------------------------------------------------------------------------
	enum class EGeometryFaceInfo
	{
		LineABVisible		= 0x04,
		LineBCVisible		= 0x02,
		LineCAVisible		= 0x01,
		LineAllVisible		= 0x07
	};

	//-------------------------------------------------------------------------------------------------------------
	typedef size_t(*TImportBufferCallback)(Uint16 fileID, void* inBuffer, size_t readBytesCnt, void* userData);	// return bytes read < readBytesCnt; readBytesCnt is the max bytes that can be read from inBuffer
	typedef size_t(*TExportBufferCallback)(Uint16 fileID, void* outBuffer, size_t writeBytesCnt, void* userData);		// return bytes written < writeBytesCnt; writeBytesCnt is the max bytes that can be written to outBuffer

	//-------------------------------------------------------------------------------------------------------------
	struct GeometryTexture
	{
		TImportBufferCallback	fFileCallback_Import;	// A callback that will be called when importing/exporting the texture file
		TExportBufferCallback	fFileCallback_Export;	//   providing or requesting the bytes in chunks
		Uint16					fFileCallbackID;		// The ID that will be provided to the callback.
														//   this can be utilized when the same callback will be used for several texture files
		void*					fFileCallbackUserData;	// The user data passed it to the callback

		std::string	fName;			// The texture 8.3 file name including extension
		Uint16		fTilingFlags;
		float		fBlurring;
		float		fUOffset;
		float		fUTiling;
		float		fVOffset;
		float		fVTiling;
		float		fRotation;

		GeometryTexture() { fTilingFlags = 0; fBlurring = fUOffset = fUTiling = fVOffset = fVTiling = fRotation = 0; fFileCallback_Import = nullptr; fFileCallback_Export = nullptr; fFileCallbackID = 0; fFileCallbackUserData = nullptr; }
	};

	//-------------------------------------------------------------------------------------------------------------
	class DYNAMIC_ATTRIBUTE IGeometryReceiver
	{
	public:
		virtual	~IGeometryReceiver() {}

		class Material
		{
		public:
			virtual ~Material() {}

			virtual const std::string&		GetMaterialName() const = 0;

			virtual float					GetTransparencyPercentage() const = 0;

			virtual const RGBColor&			GetAmbientColor() const = 0;
			virtual const RGBColor&			GetDiffuseColor() const = 0;
			virtual const RGBColor&			GetSpecularColor() const = 0;

			virtual bool					HasTexture() const = 0;
			virtual void					GetTexture(GeometryTexture& outTexture) const = 0;
			virtual void					GetTextureMask(GeometryTexture& outTexture) const = 0;
		};

		virtual void BeginObject(Sint16 objectID, Sint16 parentObjectID) = 0;	// parentObjectID = Uint64(-1) when object at root
		virtual void SetVerticesCount(size_t cnt) = 0;
		virtual void SetVertex(size_t vertexIndex, double x, double y, double z, double u, double v) = 0;
		virtual void SetFacesCount(size_t cnt) = 0;
		virtual void SetFace(size_t faceIndex, size_t vertexAIndex, size_t vertexBIndex, size_t vertexCIndex, EGeometryFaceInfo info) = 0;
		virtual void SetFaceMaterial(size_t faceIndex, const IGeometryReceiver::Material* material) = 0;
		virtual void EndObject() = 0;
	};
	
	//-------------------------------------------------------------------------------------------------------------
	class DYNAMIC_ATTRIBUTE IGeometryReference : public IVWUnknown
	{
	public:
		virtual VCOMError VCOM_CALLTYPE		GetIsSymbol(bool& isSymbol) = 0;
		virtual MvrString VCOM_CALLTYPE		GetFileForGeometry() = 0;
		virtual VCOMError VCOM_CALLTYPE		GetSymDef(ISymDef** outSymDef) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetTransfromMatrix(STransformMatrix& outName) = 0;
	};
	typedef VCOMPtr<IGeometryReference>	IGeometryReferencePtr;
	
	//-------------------------------------------------------------------------------------------------------------
	class DYNAMIC_ATTRIBUTE IGeometryProvider
	{
	public:
		virtual	~IGeometryProvider() {}

		class Material
		{
		public:
			virtual ~Material() {}

			virtual void	SetMaterialName(const std::string& name) = 0;

			virtual void	SetTransparencyPercentage(float value) = 0;

			virtual void	SetAmbientColor(const RGBColor& clr) = 0;
			virtual void	SetDiffuseColor(const RGBColor& clr) = 0;
			virtual void	SetSpecularColor(const RGBColor& clr) = 0;

			virtual void	SetTexture(const GeometryTexture& texture) = 0;
			virtual void	SetTextureMask(const GeometryTexture& texture) = 0;
		};

		virtual void GetObjects(std::vector<Sint16>& outObjectIDs, Sint16 parentObjectID=-1) = 0;

		virtual void BeginObject(Sint16 id) = 0;
		virtual void GetVerticesCount(size_t& outCnt) = 0;
		virtual void GetVertex(size_t vertexIndex, double& outX, double& outY, double& outZ, double& outU, double& outV) = 0;
		virtual void GetFacesCount(size_t& outCnt) = 0;
		virtual void GetFace(size_t faceIndex, size_t& outVertexAIndex, size_t& outVertexBIndex, size_t& outVertexCIndex, EGeometryFaceInfo& outInfo) = 0;
		virtual void GetFaceMaterial(size_t faceIndex, IGeometryProvider::Material* material) = 0;
		virtual void EndObject() = 0;
	};

	//-------------------------------------------------------------------------------------------------------------
	class DYNAMIC_ATTRIBUTE ISymDef : public IVWUnknown
	{
	public:
		virtual MvrString VCOM_CALLTYPE		GetName() = 0;
		virtual VCOMError VCOM_CALLTYPE		GetGeometryCount(size_t& outCount) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetGeometryAt(size_t at, IGeometryReference** outGeometryRef) = 0;
		
		virtual VCOMError VCOM_CALLTYPE		AddGeometry(const STransformMatrix& geometry) = 0;
		virtual VCOMError VCOM_CALLTYPE		AddSymbol(const STransformMatrix& geometry, ISymDef* symDef) = 0;
		
	};
	typedef VCOMPtr<ISymDef>	ISymDefPtr;
	
	//-------------------------------------------------------------------------------------------------------------
	enum class ESceneObjType
	{
		Layer,
		Group,
		SceneObj,
		FocusPoint,
		Truss,
		VideoScreen,
		Fixture,
	};
	
	class DYNAMIC_ATTRIBUTE ISceneObj : public IVWUnknown
	{
	public:
		virtual VCOMError VCOM_CALLTYPE		GetType(ESceneObjType& outType) = 0;
		
		virtual MvrString VCOM_CALLTYPE		GetName() = 0;
		virtual VCOMError VCOM_CALLTYPE		GetGuid(MvrUUID& outGuid) = 0;
		
		virtual VCOMError VCOM_CALLTYPE		GetTransfromMatrix(STransformMatrix& outName) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetGeometryCount(size_t& outCount) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetGeometryAt(size_t at, IGeometryReference** outGeometryRef) = 0;
		
		
		virtual VCOMError VCOM_CALLTYPE		AddGeometry(const STransformMatrix& geometry) = 0;
		virtual VCOMError VCOM_CALLTYPE		AddSymbol(const STransformMatrix& geometry, ISymDef* symDef) = 0;
		
		virtual VCOMError VCOM_CALLTYPE		GetClass(IClass** outClass) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetClass(IClass* clas) = 0;
		
		
		// Fixture
		virtual MvrString VCOM_CALLTYPE		GetGdtfName() = 0;
		virtual VCOMError VCOM_CALLTYPE		GetGdtfFixture(IGdtfFixture** outFixture) = 0;
		virtual MvrString VCOM_CALLTYPE		GetGdtfMode() = 0;
		virtual VCOMError VCOM_CALLTYPE		GetFocusPoint(ISceneObj** outFocusPoint) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetPosition(IPosition** outPosition) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetAdressCount(size_t& outAdresses) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetAdressAt(size_t at, SDmxAdress& adress) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetUnitNumber(Sint32& outUnitNumber) = 0;
		virtual MvrString VCOM_CALLTYPE		GetFixtureId() = 0;
		virtual VCOMError VCOM_CALLTYPE		GetColor(CieColor& outColor) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetFixtureTypeId(Sint8& outType) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetCustomId(size_t& outId) = 0;
		
		virtual VCOMError VCOM_CALLTYPE		SetGdtfName(MvrString gdtfName) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetGdtfMode(MvrString gdtfMode) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetFocusPoint(ISceneObj* focusPoint) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetPosition(IPosition* position) = 0;
		virtual VCOMError VCOM_CALLTYPE		AddAdress(const size_t& adresses, const size_t& breakId) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetUnitNumber(const Sint32& unitNumber) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetFixtureId(MvrString fixtureId) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetColor(const CieColor& color) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetFixtureTypeId(const Sint8& type) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetCustomId(const size_t& Cid) = 0;
	};
	typedef VCOMPtr<ISceneObj>	ISceneObjPtr;
	
	//-------------------------------------------------------------------------------------------------------------
	// Interface to handle Media Ressource Files
	class DYNAMIC_ATTRIBUTE IMediaRessourceVectorInterface : public IVWUnknown
	{
		//----------------------------------------------------------------------------------------
		// methods to write a file
	public:
		// Call this at the start of generating a MVR file
		virtual VCOMError VCOM_CALLTYPE		OpenForWrite(MvrString fullPath) = 0;
		virtual VCOMError VCOM_CALLTYPE		AddGdtfFolderLocation(MvrString fullPathToFolder) = 0;
		
		// After this you can generate Aux Objects
		virtual VCOMError VCOM_CALLTYPE		CreateDataProviderObject(MvrString provider,	MvrString version,	ISceneDataProvider** outSceneDataProvider) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreatePositionObject(	 const MvrUUID& guid,		MvrString name,		IPosition** outPositionObj) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateSymDefObject(		 const MvrUUID& guid,		MvrString name,		ISymDef** outSymDef) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateClassObject(		 const MvrUUID& guid,		MvrString name,		IClass** outclass) = 0;
		
		// Then you can generate all other objects
		virtual VCOMError VCOM_CALLTYPE		CreateLayerObject(	const MvrUUID& guid,								  MvrString name,								ISceneObj**	outLayerObj) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateGroupObject(	const MvrUUID& guid, const STransformMatrix& offset,					ISceneObj* addToContainer,	ISceneObj**	outGroupObj) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateFixture(		const MvrUUID& guid, const STransformMatrix& offset, MvrString name,	ISceneObj* addToContainer,	ISceneObj**	outFixture) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateSceneObject(	const MvrUUID& guid, const STransformMatrix& offset, MvrString name,	ISceneObj* addToContainer,	ISceneObj**	outSceneObj) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateFocusPoint(	const MvrUUID& guid, const STransformMatrix& offset, MvrString name,	ISceneObj* addToContainer,	ISceneObj** outFocusPoint) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateVideoScreen(	const MvrUUID& guid, const STransformMatrix& offset, MvrString name,	ISceneObj* addToContainer,	ISceneObj**outVideoScreen) = 0;
		
		// Add the end call to write the file to disk
		virtual VCOMError VCOM_CALLTYPE		Close() = 0;
		
		
		//----------------------------------------------------------------------------------------
		// methods to read a file
	public:
		// Call this at the start of generating a MVR file
		virtual VCOMError VCOM_CALLTYPE		OpenForRead(MvrString fullPath) = 0;
		
		// Get data provider objs
		virtual VCOMError VCOM_CALLTYPE		GetDataProviderObjectCount(size_t& outCount) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetDataProviderObjectAt(size_t at, ISceneDataProvider** outSceneDataProvider ) = 0;
		
		// Get data position objs
		virtual VCOMError VCOM_CALLTYPE		GetPositionObjectCount(size_t& outCount) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetPositionObjectAt(size_t at, IPosition** outPosition ) = 0;
		
		// Get SymDef objs
		virtual VCOMError VCOM_CALLTYPE		GetSymDefCount(size_t& outCount) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetSymDefAt(size_t at, ISymDef** outSymDef ) = 0;
		
		// Get Class objs
		virtual VCOMError VCOM_CALLTYPE		GetClassCount(size_t& outCount) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetClassAt(size_t at, IClass** outClass ) = 0;
		
		// Traversel call for object tree
		virtual VCOMError VCOM_CALLTYPE		GetFirstLayer(ISceneObj** firstLayer ) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetFirstChild(ISceneObj* container, ISceneObj** outChild) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetNextObject(ISceneObj* object, ISceneObj** outNextObj) = 0;
				
	};
	typedef VCOMPtr<IMediaRessourceVectorInterface>	IMediaRessourceVectorInterfacePtr;
	
	// ----------------------------------------------------------------------------------------------------
	const VWIID IID_MediaRessourceVectorInterface = { 0xe64bdd25, 0x865c, 0x4713, {0xaa, 0x5f, 0xfa, 0x76, 0xfd, 0x7a, 0xaa, 0x72}};
    
    
    class DYNAMIC_ATTRIBUTE IGdtfActivationGroup : public IVWUnknown
    {
		public:
        virtual MvrString VCOM_CALLTYPE     GetName() = 0;
		
		virtual VCOMError VCOM_CALLTYPE		GetAttributeCount(size_t& count) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetAttributeAt(size_t at, IGdtfAttribute** attribute) = 0;
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
	typedef VCOMPtr<IGdtfActivationGroup>	IGdtfActivationGroupPtr;
    
    class DYNAMIC_ATTRIBUTE IGdtfFeature : public IVWUnknown
    {
		public:
        virtual MvrString VCOM_CALLTYPE     GetName() = 0;
		
		virtual VCOMError VCOM_CALLTYPE		GetAttributeCount(size_t& count) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetAttributeAt(size_t at, IGdtfAttribute** attribute) = 0;
		
        virtual VCOMError VCOM_CALLTYPE     SetName(MvrString name) = 0;
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
	typedef VCOMPtr<IGdtfFeature>	IGdtfFeaturePtr;
    
    class DYNAMIC_ATTRIBUTE IGdtfFeatureGroup : public IVWUnknown
    {
		public:
		virtual VCOMError VCOM_CALLTYPE     CreateFeature(MvrString name, IGdtfFeature** feature) = 0;


        virtual MvrString VCOM_CALLTYPE     GetName() = 0;
        virtual MvrString VCOM_CALLTYPE     GetPrettyName() = 0;
        
        virtual VCOMError VCOM_CALLTYPE     GetFeatureCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetFeatureAt(size_t at, IGdtfFeature** feature) = 0;
		
		virtual VCOMError VCOM_CALLTYPE		SetPrettyName(MvrString name) = 0;				
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
	typedef VCOMPtr<IGdtfFeatureGroup>	IGdtfFeatureGroupPtr;
	
    class DYNAMIC_ATTRIBUTE IGdtfAttribute : public IVWUnknown
    {
		public:
        virtual MvrString VCOM_CALLTYPE     GetName() = 0;
        virtual MvrString VCOM_CALLTYPE     GetPrettyName() = 0;
        virtual VCOMError VCOM_CALLTYPE     GetActivationGroup(IGdtfActivationGroup** activationGroup) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetFeature(IGdtfFeature** feature) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetMainAttribute(IGdtfAttribute** mainAttrib) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetPhysicalUnit(GdtfDefines::EGdtfPhysicalUnit& unit) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetColor(CieColor & col) = 0;

		virtual VCOMError VCOM_CALLTYPE     SetActivationGroup(IGdtfActivationGroup* activationGroup) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetFeature(IGdtfFeature* feature) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetMainAttribute(IGdtfAttribute* mainAttrib) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetPhysicalUnit(GdtfDefines::EGdtfPhysicalUnit& unit) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetColor(const CieColor & col) = 0;

		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
	typedef VCOMPtr<IGdtfAttribute>	IGdtfAttributePtr;
    
    class DYNAMIC_ATTRIBUTE IGdtfWheelSlotPrismFacet : public IVWUnknown
    {
		public:
        virtual VCOMError VCOM_CALLTYPE     GetColor(CieColor& color) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetTransformMatrix(STransformMatrix& transformMatrix) = 0;
		
		virtual VCOMError VCOM_CALLTYPE     SetColor(const CieColor& color) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetTransformMatrix(const STransformMatrix& transformMatrix) = 0;
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
	typedef VCOMPtr<IGdtfWheelSlotPrismFacet>	IGdtfWheelSlotPrismFacetPtr;
    
    class DYNAMIC_ATTRIBUTE IGdtfWheelSlot : public IVWUnknown
    {
		public:
        virtual MvrString VCOM_CALLTYPE     GetName() = 0;
        virtual VCOMError VCOM_CALLTYPE     GetColor(CieColor& color) = 0;
        virtual MvrString VCOM_CALLTYPE     GetGobo() = 0;
		virtual MvrString VCOM_CALLTYPE     GetGoboFileFullPath() = 0;
		
        virtual VCOMError VCOM_CALLTYPE		SetName(MvrString name) = 0;				
		virtual VCOMError VCOM_CALLTYPE     SetColor(const CieColor& color) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetGobo(MvrString path) = 0;
		
        virtual VCOMError VCOM_CALLTYPE     GetPrismFacetCount(size_t& outCount) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetPrismFacetAt(size_t& at, IGdtfWheelSlotPrismFacet** outFacet) = 0;
		virtual VCOMError VCOM_CALLTYPE     CreatePrismFacet(const STransformMatrix& transformMatrix, IGdtfWheelSlotPrismFacet** outFacet) = 0;
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
	typedef VCOMPtr<IGdtfWheelSlot>	IGdtfWheelSlotPtr;
    
    class DYNAMIC_ATTRIBUTE IGdtfWheel : public IVWUnknown
    {
		public:
        virtual MvrString VCOM_CALLTYPE     GetName() = 0;        
        
        virtual VCOMError VCOM_CALLTYPE     GetWheelSlotCount(size_t& outCount) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetWheelSlotAt(size_t at, IGdtfWheelSlot** outPosition) = 0;
		virtual VCOMError VCOM_CALLTYPE     CreateWheelSlot(MvrString name, IGdtfWheelSlot** outPosition) = 0;
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
	typedef VCOMPtr<IGdtfWheel>	IGdtfWheelPtr;
    
    class DYNAMIC_ATTRIBUTE IGdtfModel : public IVWUnknown
    {
		public:
        virtual MvrString VCOM_CALLTYPE     GetName() = 0;
        virtual VCOMError VCOM_CALLTYPE     GetLength(double& length) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetWidth(double& width) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetHeight(double& height) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetPrimitiveType(GdtfDefines::EGdtfModel_PrimitiveType& type) = 0;
        virtual MvrString VCOM_CALLTYPE     Get3DSGeometryFile() = 0;
		virtual MvrString VCOM_CALLTYPE     Get3DSGeometryFileFullPath() = 0;
                
        virtual VCOMError VCOM_CALLTYPE     SetName(MvrString name) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetLength(double length) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetWidth(double width) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetHeight(double height) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetPrimitiveType(GdtfDefines::EGdtfModel_PrimitiveType type) = 0;
		virtual VCOMError VCOM_CALLTYPE     Set3DSGeometryFile(MvrString path) = 0;
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
	};
	typedef VCOMPtr<IGdtfModel>	IGdtfModelPtr;
	
	class DYNAMIC_ATTRIBUTE IGdtfBreak : public IVWUnknown
	{
	public:
		virtual VCOMError VCOM_CALLTYPE     GetDmxBreak(Sint32& dmxBreak) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetDmxAddress(GdtfDefines::DMXAddress& dmxAdress) = 0;

        virtual VCOMError VCOM_CALLTYPE     SetDmxBreak(Sint32 dmxBreak) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetDmxAddress(GdtfDefines::DMXAddress dmxAdress) = 0;
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
	};
	typedef VCOMPtr<IGdtfBreak>	IGdtfBreakPtr;
	
    class DYNAMIC_ATTRIBUTE IGdtfGeometry : public IVWUnknown
    {
		public:
		virtual VCOMError VCOM_CALLTYPE     GetGeometryType(GdtfDefines::EGdtfObjectType& type) = 0;
        virtual MvrString VCOM_CALLTYPE     GetName() = 0;
        virtual VCOMError VCOM_CALLTYPE     GetModel(IGdtfModel** model) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetTransformMatrix(STransformMatrix& transformMatrix) = 0;
		
        virtual VCOMError VCOM_CALLTYPE     GetInternalGeometryCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetInternalGeometryAt(size_t at, IGdtfGeometry** geometry) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateGeometry(GdtfDefines::EGdtfObjectType type, MvrString name, IGdtfModel* model, const STransformMatrix& mat, IGdtfGeometry** geometry) = 0;
		
		// Lamp
		virtual VCOMError VCOM_CALLTYPE     GetLampType(GdtfDefines::EGdtfLampType& lampType) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetPowerConsumption(double& powerConsumption) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetLuminousIntensity(double& luminousIntensity) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetColorTemperature(double& colorTemperature) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetBeamAngle(double& beamAngle) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetFieldAngle(double& fldAngle) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetBeamRadius(double& radius) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetBeamType(GdtfDefines::EGdtfBeamType & type) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetColorIndex(Sint32& idx) = 0;

        virtual VCOMError VCOM_CALLTYPE     SetName(MvrString name) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetModel(IGdtfModel** model) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetTransformMatrix(STransformMatrix& transformMatrix) = 0;

		virtual VCOMError VCOM_CALLTYPE     SetLampType(GdtfDefines::EGdtfLampType lampType) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetPowerConsumption(double powerConsumption) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetLuminousIntensity(double luminousIntensity) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetColorTemperature(double colorTemperature) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetBeamAngle(double beamAngle) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetFieldAngle(double fldAngle) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetBeamRadius(double radius) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetBeamType(GdtfDefines::EGdtfBeamType type) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetColorIndex(Sint32 idx) = 0;

		// Axis
		virtual VCOMError VCOM_CALLTYPE     GetStartAngle(double& angle) = 0;   //in Degrees
		virtual VCOMError VCOM_CALLTYPE     GetEndAngle(double& angle) = 0;     //in Degrees
		virtual VCOMError VCOM_CALLTYPE     GetSpeed(double& speed) = 0;        //in mm/s
		
		virtual VCOMError VCOM_CALLTYPE     SetStartAngle(double angle) = 0;   //in Degrees
		virtual VCOMError VCOM_CALLTYPE     SetEndAngle(double angle) = 0;     //in Degrees
		virtual VCOMError VCOM_CALLTYPE     SetSpeed(double speed) = 0;        //in mm/s
		
		// Reference
		virtual VCOMError VCOM_CALLTYPE     GetBreakCount(size_t& count) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetBreakAt(size_t at, IGdtfBreak** gdtfBreak) = 0;
		virtual VCOMError VCOM_CALLTYPE     CreateBreak(Sint32 dmxBreak, GdtfDefines::DMXAddress address, IGdtfBreak** gdtfBreak) = 0;
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
	};
	typedef VCOMPtr<IGdtfGeometry>	IGdtfGeometryPtr;
    
    class DYNAMIC_ATTRIBUTE IGdtfDmxChannelSet : public IVWUnknown
    {
	public:
        virtual MvrString VCOM_CALLTYPE     GetName() = 0;
        virtual VCOMError VCOM_CALLTYPE     GetDmxStartAddress(GdtfDefines::DMXAddress& address) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetDmxEndAddress(GdtfDefines::DMXAddress& address) = 0;
		
        virtual VCOMError VCOM_CALLTYPE     GetPhysicalStart(double& start) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetPhysicalEnd(double& end) = 0;        
        virtual VCOMError VCOM_CALLTYPE     GetWheelSlot(Sint32& WheelSlotIdx) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetUsePhysicalFromParent(bool& outUse) = 0;
		
		virtual VCOMError VCOM_CALLTYPE     SetPhysicalStart(double start) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetPhysicalEnd(double end) = 0;		
		virtual VCOMError VCOM_CALLTYPE     SetWheelSlot(Sint32 WheelSlotIdx) = 0;
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
	};
	typedef VCOMPtr<IGdtfDmxChannelSet>	IGdtfDmxChannelSetPtr;
    
    class DYNAMIC_ATTRIBUTE IGdtfDmxChannelFunction : public IVWUnknown
    {
		public:
        virtual MvrString VCOM_CALLTYPE     GetName() = 0;
		
        virtual VCOMError VCOM_CALLTYPE     GetAttribute(IGdtfAttribute** attribute) = 0;
        virtual MvrString VCOM_CALLTYPE     GetOriginalAttribute() = 0;
        virtual VCOMError VCOM_CALLTYPE     GetStartAddress(GdtfDefines::DMXAddress& address) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetPhysicalStart(double& start) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetPhysicalEnd(double& end) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetRealFade(double& fade) = 0;        
        virtual VCOMError VCOM_CALLTYPE     GetOnWheel(IGdtfWheel** wheel) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetEmitter(IGdtfPhysicalEmitter** emitter) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetDMXInvert(GdtfDefines::EGDTFDmxInvert& dmxInvert) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetEncoderInvert(GdtfDefines::EGDTFEncoderInvert& encoderInvert) = 0;

		virtual VCOMError VCOM_CALLTYPE     SetAttribute(IGdtfAttribute* attribute) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetOriginalAttribute(MvrString attr) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetStartAddress(GdtfDefines::DMXAddress address) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetPhysicalStart(double start) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetPhysicalEnd(double end) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetRealFade(double fade) = 0;		
		virtual VCOMError VCOM_CALLTYPE     SetOnWheel(IGdtfWheel* wheel) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetEmitter(IGdtfPhysicalEmitter* emitter) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetDMXInvert(GdtfDefines::EGDTFDmxInvert dmxInvert) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetEncoderInvert(GdtfDefines::EGDTFEncoderInvert encoderInvert) = 0;

        virtual VCOMError VCOM_CALLTYPE     GetDmxChannelSetCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetDmxChannelSetAt(size_t at, IGdtfDmxChannelSet** set) = 0;
		virtual VCOMError VCOM_CALLTYPE     CreateDmxChannelSet(MvrString name, GdtfDefines::DMXAddress start, GdtfDefines::DMXAddress end, IGdtfDmxChannelSet** set) = 0;
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
	typedef VCOMPtr<IGdtfDmxChannelFunction>	IGdtfDmxChannelFunctionPtr;
        
    class DYNAMIC_ATTRIBUTE IGdtfDmxLogicalChannel : public IVWUnknown
    {
		public:
        virtual MvrString VCOM_CALLTYPE     GetName() = 0;
		
        virtual VCOMError VCOM_CALLTYPE     GetAttribute(IGdtfAttribute** attribute) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetDmxSnap(GdtfDefines::EGdtfDmxSnap& snap) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetDmxMaster(GdtfDefines::EGdtfDmxMaster& master) = 0;		

		virtual VCOMError VCOM_CALLTYPE     SetAttribute(IGdtfAttribute* attribute) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetDmxSnap(GdtfDefines::EGdtfDmxSnap snap) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetDmxMaster(GdtfDefines::EGdtfDmxMaster master) = 0;
		
        virtual VCOMError VCOM_CALLTYPE     GetDmxFunctionCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetDmxFunctionAt(size_t at, IGdtfDmxChannelFunction** function) = 0;
		virtual VCOMError VCOM_CALLTYPE     CreateDmxFunction(MvrString name, IGdtfDmxChannelFunction** function) = 0;
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
	typedef VCOMPtr<IGdtfDmxLogicalChannel>	IGdtfDmxLogicalChannelPtr;
    
    class DYNAMIC_ATTRIBUTE IGdtfDmxChannel : public IVWUnknown
    {
		public:
        virtual MvrString VCOM_CALLTYPE     GetName() = 0;
		
        virtual VCOMError VCOM_CALLTYPE     GetDmxBreak(Sint32& dmxBreak) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetCoarse(Sint32& coarse) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetFine(Sint32& fine) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetUltra(Sint32& ultra) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetUber(Sint32& uber) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetDmxFrequency(GdtfDefines::EGdtfDmxFrequency& frequency) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetDefaultValue(GdtfDefines::DmxValue& defaultValue) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetHighlight(GdtfDefines::DmxValue& highlight) = 0;
		virtual VCOMError VCOM_CALLTYPE     HasHighlight(bool& highlight) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetMoveInBlackFrames(double& frames) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetDmxChangeTimeLimit(double& changeTimeLimit) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetGeometry(IGdtfGeometry** model) = 0;
		
		virtual VCOMError VCOM_CALLTYPE     SetDmxBreak(Sint32 dmxBreak) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetCoarse(Sint32 coarse) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetFine(Sint32 fine) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetUltra(Sint32 ultra) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetUber (Sint32  uber) = 0;		
		virtual VCOMError VCOM_CALLTYPE     SetDmxFrequency(GdtfDefines::EGdtfDmxFrequency frequency) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetDefaultValue(GdtfDefines::DmxValue defaultValue) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetHighlight(GdtfDefines::DmxValue highlight) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetMoveInBlackFrames(double frames) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetDmxChangeTimeLimit(double changeTimeLimit) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetGeometry(IGdtfGeometry* model) = 0;
		
        virtual VCOMError VCOM_CALLTYPE     GetLogicalChannelCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetLogicalChannelAt(size_t at, IGdtfDmxLogicalChannel** channel) = 0;
		virtual VCOMError VCOM_CALLTYPE     CreateLogicalChannel(MvrString name, IGdtfDmxLogicalChannel** channel) = 0;
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
	typedef VCOMPtr<IGdtfDmxChannel>	IGdtfDmxChannelPtr;
    
    class DYNAMIC_ATTRIBUTE IGdtfDmxRelation : public IVWUnknown
    {
		public:
        virtual MvrString VCOM_CALLTYPE     GetName() = 0;
        virtual VCOMError VCOM_CALLTYPE     GetMasterChannel(IGdtfDmxChannel** master) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetSlaveChannel(IGdtfDmxChannelFunction** slave) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetRelationType(GdtfDefines::EGdtfDmxRelationType& relation) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetDmxStart(Sint32& start) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetDmxEnd(Sint32& end) = 0;

		virtual VCOMError VCOM_CALLTYPE     SetName(MvrString name) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetMasterChannel(IGdtfDmxChannel* newMaster)= 0;
		virtual VCOMError VCOM_CALLTYPE     SetSlaveChannel(IGdtfDmxChannelFunction* newSlave)= 0;
		virtual VCOMError VCOM_CALLTYPE     SetRelationType(GdtfDefines::EGdtfDmxRelationType type)= 0;
		virtual VCOMError VCOM_CALLTYPE     SetDmxStart(GdtfDefines::DmxValue start)= 0;
		virtual VCOMError VCOM_CALLTYPE     SetDmxEnd(GdtfDefines::DmxValue end)= 0;

		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
	typedef VCOMPtr<IGdtfDmxRelation>	IGdtfDmxRelationPtr;
    
    class DYNAMIC_ATTRIBUTE IGdtfDmxMode : public IVWUnknown
    {
		public:
        virtual MvrString VCOM_CALLTYPE     GetName() = 0;
		
		virtual VCOMError VCOM_CALLTYPE     GetGeometry(IGdtfGeometry** model) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetGeometry(IGdtfGeometry* model) = 0;
        
        virtual VCOMError VCOM_CALLTYPE     GetDmxChannelCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetDmxChannelAt(size_t at, IGdtfDmxChannel** channel) = 0;
		virtual VCOMError VCOM_CALLTYPE     CreateDmxChannel(MvrString name, IGdtfDmxChannel** channel) = 0;
        
        virtual VCOMError VCOM_CALLTYPE     GetDmxRelationCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetDmxRelationAt(size_t at, IGdtfDmxRelation** relation) = 0;
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
	typedef VCOMPtr<IGdtfDmxMode>	IGdtfDmxModePtr;
    
    class DYNAMIC_ATTRIBUTE IGdtfRevision : public IVWUnknown
    {
		public:
        virtual MvrString VCOM_CALLTYPE     GetText() = 0;
        virtual MvrString VCOM_CALLTYPE     GetDate() = 0;

        virtual VCOMError VCOM_CALLTYPE     SetText(MvrString txt)  = 0;
    };
	typedef VCOMPtr<IGdtfRevision>	IGdtfRevisionPtr;
    
    class DYNAMIC_ATTRIBUTE IGdtfUserPreset : public IVWUnknown
    {
    };
	typedef VCOMPtr<IGdtfUserPreset>	IGdtfUserPresetPtr;
    
    class DYNAMIC_ATTRIBUTE IGdtfMacro : public IVWUnknown
    {
        public:
            virtual MvrString VCOM_CALLTYPE     GetName() = 0;
            virtual VCOMError VCOM_CALLTYPE     SetName(MvrString name) = 0;           
            
    };
	typedef VCOMPtr<IGdtfMacro>	IGdtfMacroPtr;
   
    
    class DYNAMIC_ATTRIBUTE IGdtfMacroDMX : public IVWUnknown
    {
    public:
        virtual MvrString VCOM_CALLTYPE     GetName() = 0;

        virtual VCOMError VCOM_CALLTYPE    GetStepCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE    GetStepAt(size_t at, IGdtfMacroDMXStep** outStep) = 0;
        virtual VCOMError VCOM_CALLTYPE    CreateStep(Sint32& macroDuration, IGdtfMacroDMXStep** outStep) = 0;
        
        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
        virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
    typedef VCOMPtr<IGdtfMacroDMX>	IGdtfMacroDMXPtr;


    class DYNAMIC_ATTRIBUTE IGdtfMacroDMXStep : public IVWUnknown
    {
    public:
        virtual MvrString VCOM_CALLTYPE     GetName() = 0;
        //
        virtual VCOMError VCOM_CALLTYPE     GetDuration(Sint32 outDur) = 0;

        virtual VCOMError VCOM_CALLTYPE GetDMXValueCount(size_t & count) = 0;
        virtual VCOMError VCOM_CALLTYPE GetDMXValueAt(size_t at, IGdtfMacroDMXValue**  outVal) = 0;
        virtual VCOMError VCOM_CALLTYPE CreateDMXValue(GdtfDefines::DmxValue dmxVal, IGdtfDmxChannel* dmxChannel, IGdtfMacroDMXValue** outVal) = 0;
        
        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
        virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
    typedef VCOMPtr<IGdtfMacroDMXStep>	IGdtfMacroDMXStepPtr;


    class DYNAMIC_ATTRIBUTE IGdtfMacroDMXValue : public IVWUnknown
    {
    public:
        virtual MvrString VCOM_CALLTYPE     GetName() = 0;
        
        virtual VCOMError VCOM_CALLTYPE   GetDmxValue(GdtfDefines::DmxValue& outValue) = 0;
        virtual VCOMError VCOM_CALLTYPE   GetDmxChannel(IGdtfDmxChannel** outValue) = 0;

        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
        virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
    typedef VCOMPtr<IGdtfMacroDMXValue>	IGdtfMacroDMXValuePtr;

    
    class DYNAMIC_ATTRIBUTE IGdtfMacroVisual : public IVWUnknown
    {
    public:
        virtual MvrString VCOM_CALLTYPE     GetName() = 0;

        virtual VCOMError VCOM_CALLTYPE     GetVisualStepCount(size_t& outCount) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetVisualStepAt(size_t at, IGdtfMacroVisualStep**  outVal) = 0;
        virtual VCOMError VCOM_CALLTYPE     CreateVisualStep(IGdtfMacroVisualStep** outVal) = 0;

        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
        virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
    typedef VCOMPtr<IGdtfMacroVisual>	IGdtfMacroVisualPtr;


    class DYNAMIC_ATTRIBUTE IGdtfMacroVisualStep : public IVWUnknown
    {
    public:
        virtual MvrString VCOM_CALLTYPE     GetName() = 0;
        //
        virtual VCOMError VCOM_CALLTYPE GetDuration(Sint32& duration) = 0;
        virtual VCOMError VCOM_CALLTYPE GetFade(double& fade) = 0;
        virtual VCOMError VCOM_CALLTYPE GetDelay(double& delay) = 0;
        //        
        virtual VCOMError VCOM_CALLTYPE SetDuration(Sint32 d) = 0;
        virtual VCOMError VCOM_CALLTYPE SetFade(double f) = 0;
        virtual VCOMError VCOM_CALLTYPE SetDelay(double d) = 0;

        virtual VCOMError VCOM_CALLTYPE     GetVisualValueCount(size_t& outCount) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetVisualValueAt(size_t at, IGdtfMacroVisualValue**  outVal) = 0;
        virtual VCOMError VCOM_CALLTYPE     CreateVisualValue(IGdtfMacroVisualValue** outVal) = 0;

        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
        virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
    typedef VCOMPtr<IGdtfMacroVisualStep>	IGdtfMacroVisualStepPtr;


    class DYNAMIC_ATTRIBUTE IGdtfMacroVisualValue : public IVWUnknown
    {
    public:
        virtual MvrString VCOM_CALLTYPE     GetName() = 0;

        virtual VCOMError VCOM_CALLTYPE   GetDmxValue(GdtfDefines::DmxValue& outValue) = 0;
        virtual VCOMError VCOM_CALLTYPE   GetDmxChannel(IGdtfDmxChannelFunction** outValue) = 0;

        virtual VCOMError VCOM_CALLTYPE   SetDmxValue(GdtfDefines::DmxValue newValue) = 0;
        virtual VCOMError VCOM_CALLTYPE   SetDmxChannel(IGdtfDmxChannelFunction* newValue) = 0;

        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
        virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
    typedef VCOMPtr<IGdtfMacroVisualValue>	IGdtfMacroVisualValuePtr;


    class DYNAMIC_ATTRIBUTE IGdtfMeasurementPoint : public IVWUnknown
    {
		public:
        virtual VCOMError VCOM_CALLTYPE     GetWaveLength(double& wavelength) = 0;  // in nm
        virtual VCOMError VCOM_CALLTYPE     GetEnergy(double& energy) = 0;          // Unit W/m^2*/nm
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;

        virtual VCOMError VCOM_CALLTYPE     SetWaveLength(double wavelength) = 0;  
        virtual VCOMError VCOM_CALLTYPE     SetEnergy(double energy) = 0;
    };
	typedef VCOMPtr<IGdtfMeasurementPoint>	IGdtfMeasurementPointPtr;
    
    class DYNAMIC_ATTRIBUTE IGdtfPhysicalEmitter : public IVWUnknown
    {
		public:
        virtual MvrString VCOM_CALLTYPE     GetName() = 0;
        virtual VCOMError VCOM_CALLTYPE     GetColor(CieColor& color) = 0;
        
        virtual VCOMError VCOM_CALLTYPE     GetMeasurementPointCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetMeasurementPointAt(size_t at, IGdtfMeasurementPoint** measurementPoint) = 0;
		virtual VCOMError VCOM_CALLTYPE     CreateMeasurementPoint(double wavelength, double energy, IGdtfMeasurementPoint** measurementPoint) = 0;
		
        virtual VCOMError VCOM_CALLTYPE     SetName(MvrString name) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetColor(CieColor & color) = 0;

		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
    typedef VCOMPtr<IGdtfPhysicalEmitter>	IGdtfPhysicalEmitterPtr;

    class DYNAMIC_ATTRIBUTE IGdtfCRI : public IVWUnknown
    {
    public:
        virtual MvrString VCOM_CALLTYPE     GetName() = 0;
        // Getter
        virtual VCOMError VCOM_CALLTYPE GetColorSample(GdtfDefines::EGdtfColorSample outVal) = 0;
        virtual VCOMError VCOM_CALLTYPE GetColorTemperature(Sint32& outVal) = 0;
        // Setter
        virtual VCOMError VCOM_CALLTYPE SetColorSample(GdtfDefines::EGdtfColorSample val) = 0;
        virtual VCOMError VCOM_CALLTYPE SetColorTemperature(Sint32 val) = 0;
        //
        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
        virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
    typedef VCOMPtr<IGdtfCRI>	IGdtfCRIPtr;

    class DYNAMIC_ATTRIBUTE IGdtfCRIGroup : public IVWUnknown
    {
    public:
        virtual MvrString VCOM_CALLTYPE     GetName() = 0;

        virtual VCOMError VCOM_CALLTYPE GetColorTemperature(double& outVal) = 0;
        virtual VCOMError VCOM_CALLTYPE SetColorTemperature(double value) = 0;

        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetCRICount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE CreateCRI(GdtfDefines::EGdtfColorSample ces, Sint32 colorTemp, VectorworksMVR::IGdtfCRI **outVal) = 0;
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetCRIAt(size_t at, VectorworksMVR::IGdtfCRI** value) = 0;
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
	};
    typedef VCOMPtr<IGdtfCRIGroup>	IGdtfCRIGroupPtr;
	
	class DYNAMIC_ATTRIBUTE IGdtfDMXProfile : public IVWUnknown
	{
	public:
		virtual MvrString VCOM_CALLTYPE     GetName() = 0;
		
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
	};
	typedef VCOMPtr<IGdtfDMXProfile>	IGdtfDMXProfilePtr;
	
    class DYNAMIC_ATTRIBUTE IGdtfFixture : public IVWUnknown
    {
		public:
        virtual VCOMError VCOM_CALLTYPE		ReadFromFile(MvrString fullPath) = 0;
		
		virtual VCOMError VCOM_CALLTYPE		OpenForWrite(MvrString fullPath, MvrString name, MvrString manufacturer, const MvrUUID& uuid) = 0;
		virtual VCOMError VCOM_CALLTYPE		AddFileToGdtfFile(MvrString fullPath) = 0;
		virtual VCOMError VCOM_CALLTYPE		Close() = 0;
        
        virtual MvrString VCOM_CALLTYPE		GetName() = 0;
        virtual MvrString VCOM_CALLTYPE     GetManufacturer() = 0;
		 virtual VCOMError VCOM_CALLTYPE    GetFixtureGUID(MvrUUID& uuid) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetLinkedFixtureGUID(UUID& uuid) = 0;
		virtual VCOMError VCOM_CALLTYPE		HasLinkedFixtureGUID(bool& has) = 0;
		
		virtual MvrString VCOM_CALLTYPE     GetFixtureTypeDescription() = 0;
		virtual MvrString VCOM_CALLTYPE		GetShortName() = 0;
        virtual MvrString VCOM_CALLTYPE     GetFixtureThumbnail() = 0;
		virtual MvrString VCOM_CALLTYPE     GetFixtureThumbnailFullPath() = 0;
		
		virtual VCOMError VCOM_CALLTYPE     SetFixtureTypeDescription(MvrString descrip) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetShortName(MvrString shortName) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetFixtureThumbnail(MvrString thubnail) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetLinkedFixtureGUID(const UUID& uuid) = 0;
		
        virtual VCOMError VCOM_CALLTYPE		GetActivationGroupCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetActivationGroupAt(size_t at, IGdtfActivationGroup** activationGroup) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateActivationGroup(MvrString name, IGdtfActivationGroup** activationGroup) = 0;
        
        virtual VCOMError VCOM_CALLTYPE		GetFeatureGroupCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetFeatureGroupAt(size_t at, IGdtfFeatureGroup** featureGroup ) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateFeatureGroup(MvrString name, MvrString prettyName, IGdtfFeatureGroup** featureGroup ) = 0;
		
        virtual VCOMError VCOM_CALLTYPE		GetAttributeCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetAttributeAt(size_t at, IGdtfAttribute** attribute) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateAttribute(MvrString name, MvrString prettyName, IGdtfAttribute** attribute) = 0;
        
        virtual VCOMError VCOM_CALLTYPE		GetWheelCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetWheelAt(size_t at, IGdtfWheel** wheel ) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateWheel(MvrString name, IGdtfWheel** wheel ) = 0;
		
		
        virtual VCOMError VCOM_CALLTYPE		GetModelCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetModelAt(size_t at, IGdtfModel** model ) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateModel(MvrString name,IGdtfModel** model ) = 0;
        
        virtual VCOMError VCOM_CALLTYPE		GetGeometryCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetGeometryAt(size_t at, IGdtfGeometry** geometry) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateGeometry(GdtfDefines::EGdtfObjectType type, MvrString name, IGdtfModel* model, const STransformMatrix& mat, IGdtfGeometry** geometry) = 0;
		
        virtual VCOMError VCOM_CALLTYPE		GetDmxModeCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetDmxModeAt(size_t at, IGdtfDmxMode** dmxMode ) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateDmxMode(MvrString name, IGdtfDmxMode** dmxMode ) = 0;
        
        virtual VCOMError VCOM_CALLTYPE		GetRevisionCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetRevisionAt(size_t at, IGdtfRevision** revision ) = 0;
		virtual VCOMError VCOM_CALLTYPE     CreateRevision(MvrString text,IGdtfRevision** macro) = 0;
		
        
        virtual VCOMError VCOM_CALLTYPE		GetPresetCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetPresetAt(size_t at, IGdtfUserPreset** preset ) = 0;
		virtual VCOMError VCOM_CALLTYPE     CreatePreset(IGdtfUserPreset** macro) = 0;
        
        virtual VCOMError VCOM_CALLTYPE		GetMacroCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetMacroAt(size_t at, IGdtfMacro** macro ) = 0;
		virtual VCOMError VCOM_CALLTYPE     CreateMacro(MvrString& name, IGdtfMacro** macro) = 0;
        
		virtual VCOMError VCOM_CALLTYPE     GetEmitterCount(size_t& count) = 0;

		virtual VCOMError VCOM_CALLTYPE     GetEmitterAt(size_t at, IGdtfPhysicalEmitter** emitter) = 0;		
        virtual VCOMError VCOM_CALLTYPE     CreateEmitter(MvrString name,const CieColor& color, IGdtfPhysicalEmitter** emitter) = 0;

        virtual VCOMError VCOM_CALLTYPE		GetCRIGroupCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE		CreateCRIGroup(double colorTemp, VectorworksMVR::IGdtfCRIGroup** outVal) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetCRIGroupAt(size_t at, VectorworksMVR::IGdtfCRIGroup** value) = 0;

		virtual VCOMError VCOM_CALLTYPE		GetDMXProfileCount(size_t& count) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateDMXProfile(VectorworksMVR::IGdtfDMXProfile** outVal) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetDMXProfileAt(size_t at, VectorworksMVR::IGdtfDMXProfile** value) = 0;
		
		
		// Protocoll
		virtual VCOMError VCOM_CALLTYPE GetRDM(IGdtf_FTRDM ** newFTRDM) = 0;
		virtual VCOMError VCOM_CALLTYPE CreateRDM(VectorworksMVR::IGdtf_FTRDM ** outFTRDM) = 0;
		
	};
    typedef VCOMPtr<IGdtfFixture>	IGdtfFixturePtr;
    const   VWIID IID_IGdtfFixture = { 0x8f7bba09, 0x0753, 0x4971, {0xa9, 0x1b, 0x51, 0xce, 0x96, 0xd2, 0xb6, 0x3f}};
	
	class DYNAMIC_ATTRIBUTE IGdtfRDMValueSensor : public IVWUnknown
	{
	public:
		// Getter
		virtual VCOMError VCOM_CALLTYPE  GetValue(Sint32& outVal) = 0;
		virtual VCOMError VCOM_CALLTYPE  GetLowest(Sint32& outVal) = 0;
		virtual VCOMError VCOM_CALLTYPE  GetHighest(Sint32& outVal) = 0;
		virtual VCOMError VCOM_CALLTYPE  GetRecorded(Sint32& outVal) = 0;
		virtual VCOMError VCOM_CALLTYPE  GetThresholdOperator(GdtfDefines::EGdtf_RDMValue_ThresholdOperator& outVal) = 0;
		// Setter
		virtual VCOMError VCOM_CALLTYPE  SetValue(Sint32 val) = 0;
		virtual VCOMError VCOM_CALLTYPE  SetLowest(Sint32 val) = 0;
		virtual VCOMError VCOM_CALLTYPE  SetHighest(Sint32 val) = 0;
		virtual VCOMError VCOM_CALLTYPE  SetRecorded(Sint32 val) = 0;
		virtual VCOMError VCOM_CALLTYPE  SetThresholdOperator(GdtfDefines::EGdtf_RDMValue_ThresholdOperator val) = 0;
		//
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
	};
	typedef VCOMPtr<IGdtfRDMValueSensor>	IGdtfRDMValueSensorPtr;
	
	class DYNAMIC_ATTRIBUTE IGdtfRDMSensorNotification : public IVWUnknown
	{
	public:
		virtual VCOMError VCOM_CALLTYPE GetSensorOffset(Sint32& outVal) = 0;
		virtual VCOMError VCOM_CALLTYPE SetSensorOffset(Sint32 value) = 0;
		
		virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetValueSensorCount(size_t& count) = 0;
		virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE CreateValueSensor(Sint32 value,
																		Sint32 lowest,
																		Sint32 highest,
																		Sint32 recorded,
																		GdtfDefines::EGdtf_RDMValue_ThresholdOperator thresholdOperator,
																		IGdtfRDMValueSensor** outVal) = 0;
		
		virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetValueSensorAt(size_t at, IGdtfRDMValueSensor** value) = 0;
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
	};
	typedef VCOMPtr<IGdtfRDMSensorNotification>	IGdtfRDMSensorNotificationPtr;

    class DYNAMIC_ATTRIBUTE IGdtfRDMNotifications : public IVWUnknown
    {
    public:
        virtual VCOMError GetRDMAbsentNotification(VectorworksMVR::IGdtfRDMAbsentNotification ** outRDMAbsentNotification) = 0;
        virtual VCOMError SetRDMAbsentNotification(IGdtfRDMAbsentNotification * newRDMAbsentNotification) = 0;

        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetRDMParameterNotificationCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE CreateRDMParameterNotification(Sint32 PID, VectorworksMVR::IGdtfRDMParameterNotification** outVal) = 0;
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetRDMParameterNotificationAt(size_t at, VectorworksMVR::IGdtfRDMParameterNotification** value) = 0;

        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetSensorNotificationCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE CreateSensorNotification(Sint32 sensorOffset, VectorworksMVR::IGdtfRDMSensorNotification**outVal) = 0;
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetSensorNotificationAt(size_t at, VectorworksMVR::IGdtfRDMSensorNotification **SensorNotification) = 0;

        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
        virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
    typedef VCOMPtr<IGdtfRDMNotifications>	IGdtfRDMNotificationsPtr;

    class DYNAMIC_ATTRIBUTE IGdtf_FTRDM : public IVWUnknown
    {
    public:
        virtual VCOMError VCOM_CALLTYPE GetManufacturerID(Sint32& outVal) = 0;        
        virtual VCOMError VCOM_CALLTYPE GetDeviceModelID(Sint32& outVal) = 0;
		
		virtual VCOMError VCOM_CALLTYPE GetSoftwareIDAt(size_t at ,Sint32& outVal) = 0;
		virtual VCOMError VCOM_CALLTYPE GetSoftwareIDCount(size_t& count) = 0;

        virtual VCOMError VCOM_CALLTYPE SetManufacturerID(Sint32 value) = 0;
        virtual VCOMError VCOM_CALLTYPE SetDeviceModelID(Sint32 value) = 0;
        virtual VCOMError VCOM_CALLTYPE AddSoftwareID(Sint32 softID) = 0;
        
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetRDMParameterCount(size_t& count) = 0;        
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetRDMParameterAt(size_t at, VectorworksMVR::IGdtfRDMParameter **RDMParameter) = 0;
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE CreateRDMParameter(VectorworksMVR::IGdtfRDMParameter **outVal,
                MvrString name,
                Sint32 PID, 
                GdtfDefines::EGdtf_RDMParam_Type Type,
                GdtfDefines::EGdtf_RDMParam_DataType dataType,
                GdtfDefines::EGdtf_RDMParam_Command command,
                GdtfDefines::EGdtf_RDMParam_SensorUnit sensorUnit,
                GdtfDefines::EGdtf_RDMParam_SensorUnitPrefix sensorUnitPrefix,
                Sint32 minValue,
                Sint32 maxValue, 
                Sint32 PDLSize, 
                MvrString description) = 0;

        virtual VCOMError VCOM_CALLTYPE     GetRDMNotifications(VectorworksMVR::IGdtfRDMNotifications ** outRDMNotifications) = 0;

        virtual VCOMError VCOM_CALLTYPE     SetRDMNotifications(IGdtfRDMNotifications * newRDMNotifications) = 0;

        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
        virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
    typedef VCOMPtr<IGdtf_FTRDM>	IGdtfTRDMPtr;

    class DYNAMIC_ATTRIBUTE IGdtfRDMParameterValue : public IVWUnknown
    {
    public:        
        virtual VCOMError VCOM_CALLTYPE  GetRDMValueType(GdtfDefines::EGdtfObjectType& type) = 0;

        // TODO: ThresholdOperator is a attribute NUMERIC_VALUES and RDMValueBool and RDMValue_REAL_TIME_CLOCK. So it can be used by both types. 
        virtual VCOMError VCOM_CALLTYPE  GetThresholdOperator(GdtfDefines::EGdtf_RDMValue_ThresholdOperator value) = 0;
        virtual VCOMError VCOM_CALLTYPE  SetThresholdOperator(GdtfDefines::EGdtf_RDMValue_ThresholdOperator value) = 0;

        // PersonalityDescription is an attribut of RDMValue_DMX_PERSONALITY_DESCRIPTION and RDMValue_SENSOR_DEFINITION
        virtual MvrString VCOM_CALLTYPE  GetPersonalityDescription() = 0;
        virtual VCOMError VCOM_CALLTYPE  SetPersonalityDescription(MvrString value) = 0;

        /* NUMERIC_VALUES
        RDMValue_UNSIGNED_BYTE
        RDMValue_SIGNED_BYTE
        RDMValue_UNSIGNED_WORD
        RDMValue_SIGNED_WORD
        RDMValue_UNSIGNED_DWORD
        RDMValue_SIGNED_DWORD
        RDMValue_ASCII */

        virtual VCOMError VCOM_CALLTYPE  GetValue(Sint32& value) = 0;
        virtual VCOMError VCOM_CALLTYPE  SetValue(Sint32 value) = 0;

        //-----------------------------------------------------------------------------
        //RDMValueBool
        virtual VCOMError VCOM_CALLTYPE  GetBoolValue(GdtfDefines::EGdtf_RDMValueBool_Value& value) = 0;
        virtual VCOMError VCOM_CALLTYPE  SetBoolValue(GdtfDefines::EGdtf_RDMValueBool_Value value) = 0;
        //-----------------------------------------------------------------------------
        //RDMValue_DMX_PERSONALITY_DESCRIPTION        
        virtual VCOMError VCOM_CALLTYPE  GetFootPrint(Sint32& value) = 0;

        virtual VCOMError VCOM_CALLTYPE  SetFootPrint(Sint32 value) = 0;
        //-----------------------------------------------------------------------------
        //RDMValue_SENSOR_DEFINITION
        // Getter   
        virtual VCOMError VCOM_CALLTYPE  GetSensorDefiniType(GdtfDefines::EGdtf_RDMValue_SENSOR_DEFINITION_TYPE& value) = 0;
        virtual VCOMError VCOM_CALLTYPE  GetSensorUnit(GdtfDefines::EGdtf_RDMParam_SensorUnit& value) = 0;
        virtual VCOMError VCOM_CALLTYPE  GetSensorUnitPrefix(GdtfDefines::EGdtf_RDMParam_SensorUnitPrefix& value) = 0;
        virtual VCOMError VCOM_CALLTYPE  GetRangeMinValue(Sint32& value) = 0;
        virtual VCOMError VCOM_CALLTYPE  GetRangeMaxValue(Sint32& value) = 0;
        virtual VCOMError VCOM_CALLTYPE  GetNormalMinValue(Sint32& value) = 0;
        virtual VCOMError VCOM_CALLTYPE  GetNormalMaxValue(Sint32& value) = 0;
        virtual VCOMError VCOM_CALLTYPE  GetLowesHighestDetectionSupported(GdtfDefines::EGdtf_RDMValue_LowesHighestDetectionSupported& value) = 0;
        virtual VCOMError VCOM_CALLTYPE  GetRecordValueSupported(GdtfDefines::EGdtf_RDMValue_RecordValueSupported& value) = 0;
        // Setter       
        virtual VCOMError VCOM_CALLTYPE  SetSensorDefiniType(GdtfDefines::EGdtf_RDMValue_SENSOR_DEFINITION_TYPE value) = 0;
        virtual VCOMError VCOM_CALLTYPE  SetSensorUnit(GdtfDefines::EGdtf_RDMParam_SensorUnit value) = 0;
        virtual VCOMError VCOM_CALLTYPE  SetSensorUnitPrefix(GdtfDefines::EGdtf_RDMParam_SensorUnitPrefix value) = 0;
        virtual VCOMError VCOM_CALLTYPE  SetRangeMinValue(Sint32 value) = 0;
        virtual VCOMError VCOM_CALLTYPE  SetRangeMaxValue(Sint32 value) = 0;
        virtual VCOMError VCOM_CALLTYPE  SetNormalMinValue(Sint32 value) = 0;
        virtual VCOMError VCOM_CALLTYPE  SetNormalMaxValue(Sint32 value) = 0;
        virtual VCOMError VCOM_CALLTYPE  SetLowesHighestDetectionSupported(GdtfDefines::EGdtf_RDMValue_LowesHighestDetectionSupported value) = 0;
        virtual VCOMError VCOM_CALLTYPE  SetRecordValueSupported(GdtfDefines::EGdtf_RDMValue_RecordValueSupported value) = 0;
        //-----------------------------------------------------------------------------
        //RDMValue_SLOT_INFO
        //  Getter        
        virtual VCOMError VCOM_CALLTYPE  GetDmxOffset(Sint32& value) = 0;
        virtual VCOMError VCOM_CALLTYPE  GetSlotInfoType(GdtfDefines::EGdtf_RDMValue_SLOT_INFO_Type& value) = 0;
        virtual VCOMError VCOM_CALLTYPE  GetSlotLabelID(GdtfDefines::EGdtf_RDMValue_SLOT_INFO_SlotLabelID& value) = 0;
        //  Setter       
        virtual VCOMError VCOM_CALLTYPE  SetDmxOffset(Sint32 value) = 0;
        virtual VCOMError VCOM_CALLTYPE  SetSlotInfoType(GdtfDefines::EGdtf_RDMValue_SLOT_INFO_Type value) = 0;
        virtual VCOMError VCOM_CALLTYPE  SetSlotLabelID(GdtfDefines::EGdtf_RDMValue_SLOT_INFO_SlotLabelID value) = 0;
        //-----------------------------------------------------------------------------
        //RDMValue_STATUS_ID_DESCRIPTION
        //  Getter        
        virtual VCOMError VCOM_CALLTYPE  GetStatusID(Sint32& value) = 0;
        virtual VCOMError VCOM_CALLTYPE  GetStatusDescription(MvrString value) = 0;
        //  Setter       
        virtual VCOMError VCOM_CALLTYPE  SetStatusID(Sint32 value) = 0;
        virtual VCOMError VCOM_CALLTYPE  SetStatusDescription(MvrString value) = 0;
        //-----------------------------------------------------------------------------
        //RDMValue_REAL_TIME_CLOCK
        //  Getter        
        virtual VCOMError VCOM_CALLTYPE  GetYear(Sint32& value) = 0;
        virtual VCOMError VCOM_CALLTYPE  GetMonth(Sint32& value) = 0;
        virtual VCOMError VCOM_CALLTYPE  GetDay(Sint32& value) = 0;
        virtual VCOMError VCOM_CALLTYPE  GetHours(Sint32& value) = 0;
        virtual VCOMError VCOM_CALLTYPE  GetMinute(Sint32& value) = 0;
        virtual VCOMError VCOM_CALLTYPE  GetSecond(Sint32& value) = 0;
        //  Setter
        virtual VCOMError VCOM_CALLTYPE  SetYear(Sint32 value) = 0;
        virtual VCOMError VCOM_CALLTYPE  SetMonth(Sint32 value) = 0;
        virtual VCOMError VCOM_CALLTYPE  SetDay(Sint32 value) = 0;
        virtual VCOMError VCOM_CALLTYPE  SetHours(Sint32 value) = 0;
        virtual VCOMError VCOM_CALLTYPE  SetMinute(Sint32 value) = 0;
        virtual VCOMError VCOM_CALLTYPE  SetSecond(Sint32 value) = 0;

        //-----------------------------------------------------------------------------
        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
        virtual void*	  VCOM_CALLTYPE    GetBoundObject() = 0;

    };
    typedef VCOMPtr<IGdtfRDMParameterValue>	IGdtfRDMParameterValuePtr;

    class DYNAMIC_ATTRIBUTE IGdtfRDMParameter : public IVWUnknown
    {
    public:
        // Getter
        virtual VCOMError VCOM_CALLTYPE GetName(MvrString& outVal) = 0;
        virtual VCOMError VCOM_CALLTYPE GetPID(Sint32& outVal) = 0;
        virtual VCOMError VCOM_CALLTYPE GetType(GdtfDefines::EGdtf_RDMParam_Type& outVal) = 0;
        virtual VCOMError VCOM_CALLTYPE GetDataType(GdtfDefines::EGdtf_RDMParam_DataType& outVal) = 0;
        virtual VCOMError VCOM_CALLTYPE GetCommand(GdtfDefines::EGdtf_RDMParam_Command& outVal) = 0;
        virtual VCOMError VCOM_CALLTYPE GetSensorUnit(GdtfDefines::EGdtf_RDMParam_SensorUnit& outVal) = 0;
        virtual VCOMError VCOM_CALLTYPE GetSensorUnitPrefix(GdtfDefines::EGdtf_RDMParam_SensorUnitPrefix& outVal) = 0;
        virtual VCOMError VCOM_CALLTYPE GetMinValue(Sint32& outVal) = 0;
        virtual VCOMError VCOM_CALLTYPE GetMaxValue(Sint32& outVal) = 0;
        virtual VCOMError VCOM_CALLTYPE GetDescription(MvrString& outVal) = 0;
        // Setter
        virtual VCOMError VCOM_CALLTYPE SetName(const MvrString& value) = 0;
        virtual VCOMError VCOM_CALLTYPE SetPID(Sint32 value) = 0;
        virtual VCOMError VCOM_CALLTYPE SetType(GdtfDefines::EGdtf_RDMParam_Type value) = 0;
        virtual VCOMError VCOM_CALLTYPE SetDataType(GdtfDefines::EGdtf_RDMParam_DataType value) = 0;
        virtual VCOMError VCOM_CALLTYPE SetCommand(GdtfDefines::EGdtf_RDMParam_Command value) = 0;        
        virtual VCOMError VCOM_CALLTYPE SetSensorUnit(GdtfDefines::EGdtf_RDMParam_SensorUnit value) = 0;
        virtual VCOMError VCOM_CALLTYPE SetSensorUnitPrefix(GdtfDefines::EGdtf_RDMParam_SensorUnitPrefix value) = 0;
        virtual VCOMError VCOM_CALLTYPE SetMinValue(Sint32 value) = 0;
        virtual VCOMError VCOM_CALLTYPE SetMaxValue(Sint32 value) = 0;
        virtual VCOMError VCOM_CALLTYPE GetPDLSize(Sint32& outVal) = 0;
        virtual VCOMError VCOM_CALLTYPE SetPDLSize(Sint32 value) = 0;
        virtual VCOMError VCOM_CALLTYPE SetDescription(const MvrString& value) = 0;
        // Arrays
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetRDMParameterValueCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE CreateRDMParameterValue(GdtfDefines::EGdtfObjectType type, VectorworksMVR::IGdtfRDMParameterValue** outVal) = 0;
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetRDMParameterValueAt(size_t at, VectorworksMVR::IGdtfRDMParameterValue** value) = 0;
        //
        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
        virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
    typedef VCOMPtr<IGdtfRDMParameter>	IGdtfRDMParameterPtr;

    class DYNAMIC_ATTRIBUTE IGdtfRDMAbsentNotification : public IVWUnknown
    {
    public:
        virtual MvrString VCOM_CALLTYPE     GetName() = 0;

        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
        virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
    typedef VCOMPtr<IGdtfRDMAbsentNotification>	IGdtfRDMAbsentNotificationPtr;

    class DYNAMIC_ATTRIBUTE IGdtfRDMParameterNotification : public IVWUnknown
    {
    public:
        virtual VCOMError VCOM_CALLTYPE GetPID(Sint32& outVal) = 0;
        virtual VCOMError VCOM_CALLTYPE SetPID(Sint32 value) = 0;
        // Arrays
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetRDMParameterValueCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE CreateRDMParameterValue(GdtfDefines::EGdtfObjectType type, VectorworksMVR::IGdtfRDMParameterValue** outVal) = 0;
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetRDMParameterValueAt(size_t at, VectorworksMVR::IGdtfRDMParameterValue** value) = 0;
        //        
        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
        virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
    typedef VCOMPtr<IGdtfRDMParameterNotification>	IGdtfRDMParameterNotificationPtr;


}
