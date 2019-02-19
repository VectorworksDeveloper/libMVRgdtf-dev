//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once
#include "Prefix/StdAfx.h"
#include "CieColor.h"
#include "GdtfError.h"
#include "Include/GDTFPrefix.h"

using namespace VectorWorks::Filing;
using namespace VectorworksMVR::GdtfDefines;

typedef VWFC::Tools::VWUUID	GdtfFixtureGUID;
typedef TXString			GdtfPNGFile;
typedef TXString			Gdtf3DSFile;
typedef Sint32				StatusID;

namespace SceneData
{
	// Forward declarations
	class GdtfPhysicalEmitter;
	class GdtfFeatureGroup;
	class GdtfAttribute;
	class GdtfWheel;	
	class GdtfFixture;
	class GdtfDmxLogicalChannel;
	class GdtfDmxChannel;
    class GdtfMacroDMX;   
    class GdtfMacroVisual;	
	class GdtfDmxChannelFunction;	
    class GdtfFTRDM;
    class GdtfArtNet;
    class GdtfsAcn;
    class GdtfKiNET;
    class GdtfPosiStageNet;
    class GdtfOpenSoundControl;
    class GdtfCITP;
    class GdtfRDMNotifications;
    class GdtfDmxMode;

    class GdtfRDMParameterValue;        
    typedef GdtfRDMParameterValue*	GdtfRDMParameterValuePtr;
    typedef std::vector<GdtfRDMParameterValue*>	TGdtfRDMParameterValueArray;

    class GdtfRDMParameter;    
    typedef GdtfRDMParameter*	GdtfRDMParameterPtr;
    typedef std::vector<GdtfRDMParameter*>	TGdtfRDMParameterArray;

    class GdtfRDMValue_SENSOR_DEFINITION;
    typedef GdtfRDMValue_SENSOR_DEFINITION*	GdtfRDMValue_SENSOR_DEFINITIONPtr;
    typedef std::vector<GdtfRDMValue_SENSOR_DEFINITION*>	TGdtfRDMValue_SENSOR_DEFINITIONArray;

    class GdtfRDMAbsentNotification;

    class GdtfRDMValueSensor;
    typedef std::vector<GdtfRDMValueSensor*>	TGdtfRDMValueSensorArray;

    //-----------------------------------------------------------------------------
	//------------------------------------------------------------------------------------
	// Attributes	
	
	class GdtfObject
	{
	public:
		GdtfObject();
		virtual ~GdtfObject();
		
	private:
		void*		    fBindValue;
        IXMLFileNodePtr fNode;
		
		
	public:
		// Write
		void			WriteToNode(IXMLFileNodePtr pContainerNode);
		void			ReadFromNode(const IXMLFileNodePtr& pNode);

        void			GetNode(IXMLFileNodePtr& pNode);
		
		
		// Bind Behavoir
		void	SetBind(void* ptr);
		void*	GetBind();
		
	public:
		virtual EGdtfObjectType			GetObjectType() = 0;
		virtual TXString				GetNodeReference();
		
	protected:
		virtual	TXString				GetNodeName() = 0;
		
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);
		
	};
	
	//------------------------------------------------------------------------------------
	// Attribute Definitions
	
	
	//------------------------------------------------------------------------------------
	// GdtfActivationGroup
	class GdtfActivationGroup : public GdtfObject
	{
	public:
        GdtfActivationGroup();
		GdtfActivationGroup(const TXString& name);
		~GdtfActivationGroup();
		
	private:
		TXString					fName;
		
		std::vector<GdtfAttribute*>	fLinkedAttributes;
		
	public:
		
	public:
        const TXString&						GetName() const;
		virtual EGdtfObjectType				GetObjectType();
		virtual TXString					GetNodeReference();
		
		void								SetName(const TXString& name);
	
		const std::vector<GdtfAttribute*>&  GetLinkedAttributes() const;
		void								AddLinkedAttribute(GdtfAttribute* attr);
		
	protected:
		virtual	TXString				    GetNodeName();
		virtual	void					    OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					    OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					    OnErrorCheck(const IXMLFileNodePtr& pNode);

	};
	typedef GdtfActivationGroup*				GdtfActivationGroupPtr;
	typedef std::vector<GdtfActivationGroupPtr>	TGdtfActivationGroupArray;
		
	//------------------------------------------------------------------------------------
	// Feature Groups
	class GdtfFeature : public GdtfObject
	{
	public:
		GdtfFeature(GdtfFeatureGroup* parent);
		~GdtfFeature();
		
	private:
		TXString					fName;
		GdtfFeatureGroup*			fParent;
		
		std::vector<GdtfAttribute*>	fLinkedAttributes;
		
	public:
        const TXString&							GetName() const;
        GdtfFeatureGroup*						GetFeatureGroup() const;
		void									SetName(const TXString& name);
		
		const std::vector<GdtfAttribute*>&		GetLinkedAttributes() const;
		void									AddLinkedAttribute(GdtfAttribute* attr);
		
	public:
		virtual EGdtfObjectType			GetObjectType();
		virtual TXString				GetNodeReference();
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);

	};

    typedef GdtfFeature*                GdtfFeaturePtr;
	typedef std::vector<GdtfFeature*>   TGdtfFeatureArray;

	class GdtfFeatureGroup : public GdtfObject
	{
	public:
		GdtfFeatureGroup();
		GdtfFeatureGroup(const TXString& name, const TXString& prettyName);
		~GdtfFeatureGroup();
		
	private:
		TXString			fName;
		TXString			fPrettyName;
		//		
		TGdtfFeatureArray	fFeatures;

	public:
		
	public:
        const TXString&                 GetName() const;
        const TXString&                 GetPrettyName() const;
        const TGdtfFeatureArray         GetFeatureArray();
		virtual EGdtfObjectType			GetObjectType();
		
		GdtfFeature*					AddFeature(const TXString& name);
		void							SetName(const TXString& name);
		void							SetPrettyName(const TXString& prettyName);
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);

	};	
	typedef GdtfFeatureGroup*				GdtfFeatureGroupPtr;
	typedef std::vector<GdtfFeatureGroupPtr>TGdtfFeatureGroupArray;

	
	class GdtfAttribute : public GdtfObject
	{
	public:
		GdtfAttribute(const TXString& name, const TXString& prettyName);
		GdtfAttribute();
		~GdtfAttribute();
		
	private:
		TXString				fName;
		TXString				fPrettyName;
		GdtfActivationGroupPtr	fActivationGroup;
		GdtfFeaturePtr          fFeature;
        GdtfAttribute*          fMainAttribute;
        EGdtfPhysicalUnit       fPhysicalUnit;
        CCieColor               fColor;
		//		
		
	private:
		// Unresolved Ptrs
		TXString fUnresolvedActGroup;
		TXString fUnresolvedFeature;
        TXString fUnresolvedMainAttrib;
		
	public:
        // Getter
        const TXString&                 GetName() const;
        const TXString&                 GetPrettyName() const;
        GdtfActivationGroupPtr          GetActivationGroup() const;
        GdtfFeaturePtr                  GetFeature() const;
        GdtfAttribute*                  GetMainAttribute();
        EGdtfPhysicalUnit               GetPhysicalUnit();
        CCieColor                       GetColor();		
        // Setter
		void							SetName(const TXString& name);
		void							SetPrettyName(const TXString& name);
		void							SetFeature(GdtfFeaturePtr newFeat);
		void							SetActivationGroup(GdtfActivationGroupPtr ptr);
        void                            SetMainAttribute(GdtfAttribute* attr);
        void                            SetPhysicalUnit(EGdtfPhysicalUnit unit);
        void                            SetColor(const CCieColor & col);
		
		virtual EGdtfObjectType			GetObjectType();
		virtual TXString				GetNodeReference();

		const TXString&					GetUnresolvedActGroup() const;
		const TXString&					GetUnresolvedFeature() const;
		const TXString&					GetUnresolvedMainAttribute() const;

	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);

	};
	typedef GdtfAttribute*				GdtfAttributePtr;
	typedef std::vector<GdtfAttribute*> TGdtfAttributeArray;

	
	//------------------------------------------------------------------------------------
	// Wheel Definition
	class GdtfWheelSlotPrismFacet : public GdtfObject
	{
	public:
		GdtfWheelSlotPrismFacet();
		~GdtfWheelSlotPrismFacet();
		
	private:
		CCieColor			fColor;
		VWTransformMatrix	fTransform; // RotationMatrix
		
    public:
        CCieColor           GetColor();
        VWTransformMatrix   GetTransformMatrix();
		
		void				SetColor(const CCieColor& color);
		void				SetTransformMatrix(const VWTransformMatrix& ma);
	public:
		virtual EGdtfObjectType			GetObjectType();
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);
		
	};
	typedef GdtfWheelSlotPrismFacet*				GdtfWheelSlotPrismFacetPtr;
	typedef std::vector<GdtfWheelSlotPrismFacetPtr>	TGdtfWheelSlotPrismFacetArray;
	
	class GdtfWheelSlot : public GdtfObject
	{
	public:

		GdtfWheelSlot(GdtfWheel* parent);
		GdtfWheelSlot(const TXString& name, GdtfWheel* parent);

		~GdtfWheelSlot();
		
	private:
		TXString						fName;
		CCieColor						fColor;
		TXString						fGobo;
		TGdtfWheelSlotPrismFacetArray	fPrismFacts;
		GdtfWheel*                      fWheelParent;		
		TXString						fGoboFile; // MediaFileName
		
	public:
		const TXString&                 GetGobo() const;
		const TXString&                 GetGoboFileFullPath();
		CCieColor                       GetColor() const;
		const TXString&                 GetName() const;
        TGdtfWheelSlotPrismFacetArray   GetPrismFacets();
		
		void							SetName(const TXString& name);
		void							SetGobo(const GdtfPNGFile& png);
		void							SetColor(const CCieColor& color);
		GdtfWheelSlotPrismFacet*		AddPrismFacet();

		virtual TXString				GetNodeReference();

        
	public:
		virtual EGdtfObjectType			GetObjectType();
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);
		
	};
	typedef GdtfWheelSlot*					GdtfWheelSlotPtr;
	typedef std::vector<GdtfWheelSlotPtr>	TGdtfWheelSlotArray;
	
	class GdtfWheel : public GdtfObject
	{
	public:
		GdtfWheel(GdtfFixture* parentFixture);
		GdtfWheel(GdtfFixture* parentFixture, const TXString& name);

		~GdtfWheel();
		
	private:
		TXString			fName;		
		TGdtfWheelSlotArray	fWheelSlots;
		
		GdtfFixture*		fParentFixture;
		
	public:
		GdtfWheelSlotPtr            AddWheelSlot(const TXString& name);
		void						SetName(const TXString& name);
		
        const TXString&             GetName() const;        

		const TGdtfWheelSlotArray&	GetWheelSlotArray() const;
		bool						IsGoboWheel() const;
		virtual TXString			GetNodeReference();
		
		
		GdtfFixture*				GetParentFixture() const;

		
	public:
		virtual EGdtfObjectType			GetObjectType();
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);
		
	};
	typedef GdtfWheel*                  GdtfWheelPtr;
	typedef std::vector<GdtfWheelPtr>	TGdtfWheelArray;
	
	//------------------------------------------------------------------------------------
	// Model Defintion

	
	class GdtfModel : public GdtfObject
	{
	public:
		GdtfModel(GdtfFixture* fixture);
		GdtfModel(const TXString& name, GdtfFixture* fixture);
		~GdtfModel();
		
	private:
		TXString					fUniqueName;
		double						fLength;
		double						fWidth;
		double						fHeight;
		EGdtfModel_PrimitiveType	fPrimitiveType;
		Gdtf3DSFile					fGeometryFile;
		TXString					fFullPath;
		//
		GdtfFixture*				fParentFixture;
		
	public:
		// Getter
        const TXString&                 GetName() const;
        double                          GetLength() const;
        double                          GetWidth() const;
        double                          GetHeight() const;
        EGdtfModel_PrimitiveType		GetPrimitiveType() const;
		const TXString&					GetGeometryFile() const;
		const TXString&					GetGeometryFileFullPath();
		// Setter
		void						    SetName(const TXString& name);
		void					    	SetLength(const double& length);
		void						    SetWidth(const double& width);
		void						    SetHeight(const double& height);
		void						    SetPrimitiveType(const EGdtfModel_PrimitiveType& type);
		void						    SetGeometryFile(const Gdtf3DSFile& file);
		
	public:
		virtual EGdtfObjectType			GetObjectType();
		virtual TXString				GetNodeReference();
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);	
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);
				
	};
	typedef GdtfModel*					GdtfModelPtr;
	typedef std::vector<GdtfModelPtr>	TGdtfModelArray;
	
	//------------------------------------------------------------------------------------
	// Geometry Definition
	class GdtfGeometryAxis;
	class GdtfGeometryBeamFilter;
	class GdtfGeometryColorFilter;
	class GdtfGeometryGoboFilter;
	class GdtfGeometryShaperFilter;
	class GdtfGeometryLamp;
	
	class GdtfGeometry : public GdtfObject
	{
	public:

		GdtfGeometry(GdtfGeometry* parent);
		GdtfGeometry(const TXString& name, GdtfModelPtr refToModel,const VWTransformMatrix& ma, GdtfGeometry* parent);

		~GdtfGeometry();
		
	private:
		TXString					fUniqueName;
		GdtfModelPtr				fModelReference;
		TXString					fUnresolvedModelRef;
		VWTransformMatrix			fMatrix;
		//
		std::vector<GdtfGeometry*>	fInternalGeometries;
		GdtfGeometry*				fParent;		
		
	public:
		// Getter
		const TXString&						GetName() const;
		GdtfModelPtr						GetModelRef() const;
		void								GetTransformMatrix(VWTransformMatrix& ma) const;        
        const std::vector<GdtfGeometry*>	GetInternalGeometries();
		virtual TXString					GetNodeReference();
		// Setter	
		void								SetName(const TXString& name);
		void								SetModel(GdtfModelPtr model);
		void								SetTransformMatrix(const VWTransformMatrix& ma);
		
		GdtfGeometry*						AddGeometry(		const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometry*						AddGeometryReference(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometry*						AddGeometryShaper(	const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometry*						AddGeometryColor(	const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometry*						AddGeometryGobo(	const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometry*						AddGeometryBeam(	const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometry*						AddGeometryWithAxis(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometry*						AddGeometryWithLamp(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);

	public:
		virtual EGdtfObjectType			GetObjectType();
		
		
	public:
		//----------------------------------------------------------------------------------------------------------------------------------------------------------------
		// Resolve Model Ref
		TXString					GetUnresolvedModelRef() const;
		void						SetUnresolvedModelRef(GdtfModelPtr ref);
	};
	typedef GdtfGeometry*					GdtfGeometryPtr;
	typedef std::vector<GdtfGeometryPtr>	TGdtfGeometryArray;
	
	class GdtfGeometryAxis : public GdtfGeometry
	{
	public:
		GdtfGeometryAxis(GdtfGeometry* parent);
		GdtfGeometryAxis(const TXString& name, GdtfModelPtr refToModel,const VWTransformMatrix& ma, GdtfGeometry* parent);

		~GdtfGeometryAxis();
		
	private:
		double	fAngleStart;	// Unit ?? -> Degree
		double	fAngleEnd;		// Unit ?? -> Degree
		double	fSpeed;			// Unit ?? -> mm/s
		
	public:
		virtual EGdtfObjectType			GetObjectType();
        double                          GetStartAngle();
        double                          GetEndAngle();
        double                          GetSpeed();
		
		void							SetStartAngle(double start);
		void							SetEndAngle(double end);
		void							SetSpeed(double speed);
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);
	};
	
	class GdtfGeometryBeamFilter : public GdtfGeometry
	{
	public:
		GdtfGeometryBeamFilter(GdtfGeometry* parent);
		GdtfGeometryBeamFilter(const TXString& name, GdtfModelPtr refToModel,const VWTransformMatrix& ma, GdtfGeometry* parent);

		~GdtfGeometryBeamFilter();
		
	public:
		virtual EGdtfObjectType			GetObjectType();
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual void                    OnErrorCheck(const IXMLFileNodePtr& pNode);
	};
	
	class GdtfGeometryColorFilter : public GdtfGeometry
	{
	public:
		GdtfGeometryColorFilter(GdtfGeometry* parent);
		GdtfGeometryColorFilter(const TXString& name, GdtfModelPtr refToModel,const VWTransformMatrix& ma, GdtfGeometry* parent);

		~GdtfGeometryColorFilter();
		
	public:
		virtual EGdtfObjectType			GetObjectType();
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);
	};
	
	class GdtfGeometryGoboFilter : public GdtfGeometry
	{
	public:
		GdtfGeometryGoboFilter(GdtfGeometry* parent);
		GdtfGeometryGoboFilter(const TXString& name, GdtfModelPtr refToModel,const VWTransformMatrix& ma, GdtfGeometry* parent);

		~GdtfGeometryGoboFilter();
		
	public:
		virtual EGdtfObjectType			GetObjectType();
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);
	};
	
	class GdtfGeometryShaperFilter : public GdtfGeometry
	{
	public:
		GdtfGeometryShaperFilter(GdtfGeometry* parent);
		GdtfGeometryShaperFilter(const TXString& name, GdtfModelPtr refToModel,const VWTransformMatrix& ma, GdtfGeometry* parent);

		~GdtfGeometryShaperFilter();
		
	public:
		virtual EGdtfObjectType			GetObjectType();
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);
	};	
	
	class GdtfGeometryLamp : public GdtfGeometry
	{
	public:
		GdtfGeometryLamp(GdtfGeometry* parent);
		GdtfGeometryLamp(const TXString& name, GdtfModelPtr refToModel,const VWTransformMatrix& ma, GdtfGeometry* parent);
        
		~GdtfGeometryLamp();
		
	private:
		EGdtfLampType	fLampType;
		double			fPowerConsuption;	// Unit ?? -> W cos phi???
		double			fLuminousIntensity;
		double			fColorTemperature;
		double			fBeamAngle;			// Unit ?? -> Degree
        double          fFieldAngle;
		double			fBeamRadius;		// Unit Meter
		EGdtfBeamType	fBeamType;			// Unit Meter
		Sint32			fColorIndex;
		
	public:
		// Getter
		virtual EGdtfObjectType			GetObjectType();
        EGdtfLampType                   GetLampType();
        double                          GetPowerConsumption();
        double                          GetLuminousIntensity();
        double                          GetColorTemperature();
        double                          GetBeamAngle();
        double                          GetFieldAngle();
        double                          GetBeamRadius();
        EGdtfBeamType                   GetBeamType();
        Sint32                          GetColorIndex();

		// Setter
		void							SetLampType(EGdtfLampType type);
		void							SetPowerConsumption(double powerConsumption);
		void							SetLuminousIntensity(double intensity);
		void							SetColorTemperature(double temperature);
		void							SetBeamAngle(double angle);
        void                            SetFieldAngle(double angle);
        void                            SetBeamRadius(double radius);
        void                            SetBeamType(EGdtfBeamType type);
        void                            SetColorIndex(Sint32 idx);
		
	protected:
        void                            InitializeMembersWithDefaultsVals();
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);
	};
	
	class GdtfBreak : public GdtfObject
	{
	public:
		GdtfBreak();
		~GdtfBreak();
		
	private:
		Sint32		fDmxBreak;
		DMXAddress	fDmxAdress;
		
		
	public:
		// Getter
		virtual EGdtfObjectType			GetObjectType();
        Sint32                          GetDmxBreak();
        DMXAddress                      GetDmxAddress();
		// Setter
		void							SetDmxBreak(Sint32 dmxBreak);
		void							SetDmxAddress(DMXAddress dmxAddress);
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);
	};
	typedef GdtfBreak*				GdtfBreakPtr;
	typedef std::vector<GdtfBreak*> TGdtfBreakArray;
	
	class GdtfGeometryReference : public GdtfGeometry
	{
		friend GdtfGeometry;
	public:
		GdtfGeometryReference(GdtfGeometry* parent);
		GdtfGeometryReference(const TXString& name, GdtfModelPtr refToModel,const VWTransformMatrix& ma, GdtfGeometry* parent);
		~GdtfGeometryReference();
		
	private:
		TGdtfBreakArray fBreaks;
        GdtfGeometry*   fLinkedGeometry;
        
        TXString        fUnresolvedGeoRef;
		
	public:
		virtual EGdtfObjectType			GetObjectType();
        TGdtfBreakArray                 GetBreakArray();
		GdtfBreakPtr					AddBreak();

        GdtfGeometry*					GetLinkedGeometry();
        void					        SetLinkedGeometry(GdtfGeometry* ptr);
		
        const TXString&					GetUnresolvedLinkedGeometry();

	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);
	};
	typedef GdtfGeometryReference*		GdtfGeometryReferencePtr;
	
	//------------------------------------------------------------------------------------
	// DMX Definition
	class GdtfDmxChannelSet : public GdtfObject
	{
	public:
		GdtfDmxChannelSet(GdtfDmxChannelFunction* parent);
		GdtfDmxChannelSet(const TXString& name, GdtfDmxChannelFunction* parent);
		~GdtfDmxChannelSet();
		
	private:
		TXString			fUniqueName;
		DmxValue			fDmxStart;
		DmxValue			fDmxEnd;
		bool				fSetPhysical;
		double				fPhysicalStart;
		double				fPhysicalEnd;
		Sint32				fWheelSlotIdx;

		GdtfDmxChannelFunction* fParentChnlFunction; 
        GdtfDmxChannelSet*      fNextChannelSet;

	public:
		// Getter
		virtual EGdtfObjectType			GetObjectType();
		//
        const TXString&                 GetName() const;
        DmxValue                        GetDmxStart() const;
        DmxValue                        GetDmxEnd() const;
        double                          GetPhysicalStart() const;
        double                          GetPhysicalEnd() const;        
		Sint32							GetWheelSlot();
		bool							GetUsePhysicalFromParent() const;
		//
		GdtfDmxChannel*					GetParentDMXChannel() const;		
		// Setter
		void							SetName(const TXString& name);
		void							SetDmxStart(DmxValue start);
		void							SetDmxEnd(DmxValue end);
		void							SetPhysicalStart(double start);
		void							SetPhysicalEnd(double end);		
		void							SetWheelSlot(Sint32 slotIndex);

        void					        SetNextChannelSet(GdtfDmxChannelSet* next);	
				
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);

	};
	typedef GdtfDmxChannelSet*				GdtfDmxChannelSetPtr;
	typedef std::vector<GdtfDmxChannelSet*>	TGdtfDmxChannelSetArray;
	
	class GdtfDmxChannelFunction : public GdtfObject
	{
	public:
		GdtfDmxChannelFunction(GdtfDmxLogicalChannel* parent);
		GdtfDmxChannelFunction(const TXString& name, GdtfDmxLogicalChannel* parent);
		~GdtfDmxChannelFunction();
	private:
		TXString				fName;
		GdtfAttribute*		    fAttribute;
		TXString				fOrignalAttribute;
		DmxValue				fAdressStart;   
		double					fPhysicalStart;
		double					fPhysicalEnd;
		double					fRealFade;			
		GdtfWheelPtr			fOnWheel;
		GdtfPhysicalEmitter*	fEmitter;
		EGDTFDmxInvert			fDmxInvert;

        GdtfDmxChannel*         fModeMaster_Channel;
        GdtfDmxChannelFunction* fModeMaster_Function;
        DmxValue                fDmxModeStart;
        DmxValue                fDmxModeEnd;

		//
		TGdtfDmxChannelSetArray	fChannelSets;		
		
		// Unresolved Refs
		TXString				fUnresolvedAttrRef;
		TXString				fUnresolvedWheelRef;
		TXString				fUnresolvedEmitterRef;
        TXString                fUnresolvedDmxModeStart;
        TXString                fUnresolvedDmxModeEnd;
        TXString                fUnresolvedModeMaster;
		
		// Parent Logical Channel
		GdtfDmxLogicalChannel*	fParentLogicalChannel;
        GdtfDmxChannelFunction* fNextFunction;

	public:
		virtual EGdtfObjectType			GetObjectType();
		virtual TXString				GetNodeReference();
		//
        const TXString&					GetName() const;
        GdtfAttribute*				    GetAttribute();
		const TXString&					GetOriginalAttribute();
        DmxValue						GetStartAdress() const;
        DmxValue						GetEndAdress() const;
        double							GetPhysicalStart() const;
        double							GetPhysicalEnd() const;
        double							GetRealFade() const;        
        GdtfWheelPtr					GetOnWheel() const;
        GdtfPhysicalEmitter*            GetEmitter() const;
        EGDTFDmxInvert                  GetDmxInvert()const;

        GdtfDmxChannel*                 GetModeMaster_Channel() const;
        GdtfDmxChannelFunction*         GetModeMaster_Function() const;
        DmxValue                        GetModeMasterDmxStart() const;
        DmxValue                        GetModeMasterDmxEnd() const;

        size_t					        GetNumberInParent() const;
        
        //
		const TGdtfDmxChannelSetArray	GetChannelSets();		
		//
		TXString						getUnresolvedAttrRef() const;
		TXString						getUnresolvedWheelRef() const;
		TXString						getUnresolvedEmitterRef() const;
        TXString						getUnresolvedModeMasterRef() const;
		GdtfDmxChannel*					GetParentDMXChannel() const;
        GdtfDmxLogicalChannel*			GetParentLogicalChannel() const;
        void						    ResolveModeMasterDmx(EGdtfChannelBitResolution resolution);

        void                            SetNextFunction(GdtfDmxChannelFunction* next);
        GdtfDmxChannelFunction*         GetNextFunction() const;

		
		void							SetWheel(GdtfWheelPtr newWhl);
		void							SetName(const TXString& name);
		void							SetOriginalAttribute(const TXString& attribute);
		void							SetAttribute(GdtfAttribute* newAttr);		
		void							SetStartAddress(DmxValue address);
		void							SetPhysicalStart(double start);
		void							SetPhysicalEnd(double end);
		void							SetRealFade(double fade);				
		void							SetEmitter(GdtfPhysicalEmitter* newEmit);
        void                            SetDmxInvert(EGDTFDmxInvert dmxInvert);        

        void                            SetModeMaster_Channel(GdtfDmxChannel* channel);
        void                            SetModeMaster_Function(GdtfDmxChannelFunction* function);
        void                            SetModeMasterDmxStart(DmxValue start);
        void                            SetModeMasterDmxEnd(DmxValue end);   

		//
		GdtfDmxChannelSet*				AddChannelSet(const TXString& name);
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);

	};
	typedef GdtfDmxChannelFunction*					GdtfDmxChannelFunctionPtr;
	typedef std::vector<GdtfDmxChannelFunctionPtr>	TGdtfDmxChannelFuntionArray;
	
	class GdtfDmxLogicalChannel : public GdtfObject
	{
	public:
		GdtfDmxLogicalChannel(GdtfDmxChannel* parent);
		~GdtfDmxLogicalChannel();
	private:
		TXString					fName_AutoGenerated;
		GdtfAttribute*				fAttribute;
		TXString					fUnresolvedAttribRef;
		EGdtfDmxSnap				fSnap;
		EGdtfDmxMaster				fDmxMaster;
		//
		TGdtfDmxChannelFuntionArray	fFunctions;		
		
		GdtfDmxChannel*  			fParentDmxChannel;
        GdtfDmxLogicalChannel*      fNextLogicalChannel;
		double						fMoveInBlackFrames;							//is frames here the best unit
		double						fDmxChangeTimeLimit;		
		
	public:

		virtual EGdtfObjectType				GetObjectType();
		virtual TXString					GetNodeReference();
		
        const TXString&						GetName();
        GdtfAttribute*						GetAttribute();
		EGdtfDmxSnap						GetDmxSnap() const;
		EGdtfDmxMaster						GetDmxMaster() const;
        const TGdtfDmxChannelFuntionArray	GetDmxChannelFunctions();		
		TXString							GetUnresolvedAttribRef() const;
		GdtfDmxChannel*						GetParentDMXChannel() const;        
		GdtfDmxLogicalChannel*			    GetNextLogicalChannel() ;
        double                              GetMoveInBlackFrames() const;
        double								GetDmxChangeTimeLimit() const;				

		void								SetName(const TXString& name);
		void								SetAttribute(GdtfAttributePtr newAttr);
		void								SetDmxSnap(EGdtfDmxSnap snap);
		void								SetDmxMaster(EGdtfDmxMaster master);
		GdtfDmxChannelFunctionPtr			AddDmxChannelFunction(const TXString& name);
        void						        SetNextLogicalChannel(GdtfDmxLogicalChannel* next) ;
        void								SetMoveInBlackFrames(double moveInBlackFrames);
        void								SetDmxChangeTimeLimit(double changeLimit);
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);

	};
	typedef GdtfDmxLogicalChannel*				GdtfDmxLogicalChannelPtr;
	typedef std::vector<GdtfDmxLogicalChannel*>	TGdtfDmxLogicalChannelArray;
	
	class GdtfDmxChannel : public GdtfObject
	{
	public:
		GdtfDmxChannel(GdtfDmxMode* parent);
		~GdtfDmxChannel();
	private:
		TXString					fName_AutoGenerated;
		Sint32						fDmxBreak;
		Sint32						fCoarse;		bool fCoarseNone;			// None is not defined as value???
		Sint32						fFine;			bool fFineNone;				// None is not defined as value???
		Sint32						fUltra;			bool fUltraNone;			// None is not defined as value???
		Sint32                      fUber;			bool fUberNone;		
		DmxValue					fDefaultValue;
		DmxValue					fHeighlight;	bool fHeighlightNone;
		GdtfGeometryPtr				fGeomRef;
		TXString					fUnresolvedGeomRef;
		//
		TGdtfDmxLogicalChannelArray	fLogicalChannels;		

        //
        GdtfDmxMode*                fParent;
		
		
	public:
		virtual EGdtfObjectType				GetObjectType();
		virtual TXString					GetNodeReference();
		
        const TXString&						GetName();
        Sint32								GetDmxBreak() const;
        Sint32								GetCoarse() const;
        Sint32								GetFine() const;
        Sint32								GetUltra() const;
		Sint32								GetUber() const;        
        DmxValue							GetDefaultValue() const;
        DmxValue							GetHighlight() const;
		bool								HasHighlight() const;
        const TGdtfDmxLogicalChannelArray	GetLogicalChannelArray();
		GdtfGeometryPtr						GetGeomRef();
		TXString							GetUnresolvedGeomRef() const;
		EGdtfChannelBitResolution			GetChannelBitResolution();
		DmxValue							GetChannelMaxDmx();

		void								SetName(const TXString& name);
		void								SetDmxBreak(Sint32 dmxBreak);
		void								SetDmxCoarse(Sint32 coarse);
		void								SetDmxFine(Sint32 fine);
		void								SetDmxUltra(Sint32 ultra);
		void								SetDmxUber(Sint32 uber);		
		void								SetDefaultValue(DmxValue defaultValue);
		void								SetHighlight(DmxValue highlight);
		void								SetModel(GdtfModelPtr ptr);
		GdtfDmxLogicalChannel*				AddLogicalChannel();
		void								SetGeomRef(GdtfGeometryPtr newGeom);

        // Get Parent
        GdtfDmxMode*						GetParentMode();
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);

	};
	typedef GdtfDmxChannel*					GdtfDmxChannelPtr;
	typedef std::vector<GdtfDmxChannelPtr>	TGdtfDmxChannelArray;
	
	class GdtfDmxRelation : public GdtfObject
	{
	public:
		GdtfDmxRelation();
		GdtfDmxRelation(GdtfDmxChannelPtr master, GdtfDmxChannelFunctionPtr slave, const TXString& name);
		~GdtfDmxRelation();
	private:
		TXString					fUniqueName;
		GdtfDmxChannelPtr			fMasterDmxChannel;
		GdtfDmxChannelFunctionPtr	fSlaveChannelFunction;
		EGdtfDmxRelationType		fRelationType;
		
		// Pointer Resolve
		TXString					fUnresolvedMasterRef;
		TXString					fUnresolvedSlaveRef;
		
	public:
		TXString					GetUnresolvedMasterRef() const;
		TXString					GetUnresolvedSlaveRef() const;
        		
	public:
		// Getter
		virtual EGdtfObjectType			GetObjectType();
        const TXString&                 GetName() const;		
        GdtfDmxChannelPtr               GetMasterChannel() const;        		
		GdtfDmxChannelFunctionPtr       GetSlaveChannel() const;
        EGdtfDmxRelationType            GetRelationType() const;
        DmxValue                        GetDmxStart() const;
        DmxValue                        GetDmxEnd() const;
		// Setter
		void							SetName(const TXString& name);
		void							SetMasterChannel(GdtfDmxChannelPtr newMaster);
		void							SetSlaveChannel(GdtfDmxChannelFunctionPtr newSlave);		
		void							SetRelationType(EGdtfDmxRelationType type);
		void							SetDmxStart(DmxValue start);
		void							SetDmxEnd(DmxValue end);
		
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);

	};
	typedef GdtfDmxRelation*				GdtfDmxRelationPtr;
	typedef std::vector<GdtfDmxRelation*>	TGdtfDmxRelationArray;
	
	class GdtfDmxMode : public GdtfObject
	{
	public:
		GdtfDmxMode();
		GdtfDmxMode(const TXString& name);
		~GdtfDmxMode();
		
	private:
		TXString				fName;			
		GdtfGeometryPtr			fGeomRef;
		TXString				fUnresolvedGeomRef;
		//
		TGdtfDmxChannelArray	fChannels;
		TGdtfDmxRelationArray	fRelations;	  	

	public:		
		const TXString&				GetModeName() const;
		const TGdtfDmxChannelArray	GetChannelArray() const;		
		GdtfDmxChannelPtr			GetMasterByRef(const TXString& ref) const;
		GdtfDmxChannelFunctionPtr	GetSlaveByRef(const TXString& ref) const;
		GdtfGeometryPtr				GetGeomRef();
		
        const TXString&				GetUnresolvedGeomRef();
		const TGdtfDmxRelationArray GetDmxRelations();
		
		void						SetName(const TXString& name);
		GdtfDmxChannelPtr			AddChannel();
		void						SetGeomRef(GdtfGeometryPtr ptr);
		void						SetModel(GdtfGeometryPtr ptr);
		GdtfDmxRelation*			AddDmxRelation(GdtfDmxChannel* master, GdtfDmxChannelFunctionPtr slave, const TXString &name);
		
		
	public:
		virtual EGdtfObjectType			GetObjectType();
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);

	};
	typedef GdtfDmxMode*				GdtfDmxModePtr;
	typedef std::vector<GdtfDmxMode*>	TGdtfDmxModeArray;	
	
	//------------------------------------------------------------------------------------
	// GdtfRevision Definition
	class GdtfRevision : public GdtfObject
	{
	public:
		GdtfRevision();
		~GdtfRevision();
		
	private:
		TXString	fText;
		STime       fDateS;
		
	public:
		virtual EGdtfObjectType			GetObjectType();
		
	public:
        // Getter
		const STime&    GetDate() const;
		const TXString&	GetText() const;
        // Setter        
		void			SetText(const TXString& text);
        void            SetDate(const STime& date);
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);

	};
	typedef GdtfRevision*	GdtfRevisionPtr;
	typedef std::vector<GdtfRevision*>	TGdtfRevisionArray;
	
    //------------------------------------------------------------------------------------
    // Protocolls Definitions
    
    class GdtfProtocols : public GdtfObject
    {
    public:
        GdtfProtocols();
        ~GdtfProtocols();
    private:
        // Childs
        GdtfFTRDM*                  fRDM;             
        GdtfArtNet*                 fArtNet;          
        GdtfsAcn*                   fsACN;            
        GdtfKiNET*                  fKiNET;           
        GdtfPosiStageNet*           fPosiStageNet;    
        GdtfOpenSoundControl*       fOpenSoundControl;
        GdtfCITP*                   fCITP;            
    public:
        virtual EGdtfObjectType			GetObjectType();

    public:
        // Getter        
        GdtfFTRDM*                  GetRDM();              
        GdtfArtNet*                 GetArtNet();            
        GdtfsAcn*                   Get_sACN();              
        GdtfKiNET*                  GetKiNET();             
        GdtfPosiStageNet*           GetPosiStageNet();      
        GdtfOpenSoundControl*       GetOpenSoundControl();  
        GdtfCITP*                   GetCITP();              
        // Setter    
        GdtfFTRDM*                  CreateRDM();
        void                        SetArtNet(GdtfArtNet* val);
        void                        Set_sACN(GdtfsAcn* val);
        void                        SetKiNET(GdtfKiNET* val);
        void                        SetPosiStageNet(GdtfPosiStageNet* val);
        void                        SetOpenSoundControl(GdtfOpenSoundControl* val);
        void                        SetCITP(GdtfCITP* val);

    protected:
        virtual	TXString				GetNodeName();
        virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
        virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);
    };
    typedef GdtfProtocols*	GdtfProtocolsPtr;    

    class GdtfFTRDM : public GdtfObject
    {
    public:
        GdtfFTRDM();
        GdtfFTRDM(Sint32 manufacturerID, Sint32 deviceModelID);
        ~GdtfFTRDM();
    private:
        // Attributes
        Sint32      fManufacturerID;  // Manufacturer ESTA ID; Size: 2 bytes
        Sint32      fDeviceModelID;   // Unique device model ID; Size: 2 bytes        
        TSint32Array  fSoftwareVersIDs; // Array of software versions IDs; Size of each version: 4 bytes
        // Childs
        TGdtfRDMParameterArray   fRDMParameters;     // Instead of using the <RDMParameterS> we directly use a list off <RDMParameter> here.
        GdtfRDMNotifications*    fRDMNotifications;
    public:
        virtual EGdtfObjectType			GetObjectType();

    public:
        // Getter
        Sint32                        GetManufacturerID() const;
        Sint32                        GetDeviceModelID()  const;
        const TSint32Array&           GetSoftwareVersIDs() const;        
        const TGdtfRDMParameterArray& GetRDMParametersArray() const;
        GdtfRDMNotifications*         GetRDMNotifications() const;
        // Setter
        void SetManufacturerID(Sint32 val);
        void SetDeviceModelID(Sint32 val);
        void AddSoftwareVersID(Sint32 ID);
        GdtfRDMParameterPtr AddRDMParameter(
            const TXString& name, 
            Sint32 PID,            
            EGdtf_RDMParam_Type              Type,
            EGdtf_RDMParam_DataType          dataType,
            EGdtf_RDMParam_Command           command,
            EGdtf_RDMParam_SensorUnit        sensorUnit,
            EGdtf_RDMParam_SensorUnitPrefix  sensorUnitPrefix,        
            Sint32                           minValue,        
            Sint32                           maxValue,
            Sint32                           PDLSize,
            const TXString&                        description);
        
        void SetRDMNotifications(GdtfRDMNotifications* notifications);
    protected:
        virtual	TXString				GetNodeName();
        virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
        virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);
    };
    typedef GdtfFTRDM*	GdtfFTRDMPtr;    

    class GdtfRDMParameter : public GdtfObject
    {
    public:
        GdtfRDMParameter();
        GdtfRDMParameter(const TXString& name, 
                         Sint32 PID,            
                         EGdtf_RDMParam_Type              Type,
                         EGdtf_RDMParam_DataType          dataType,
                         EGdtf_RDMParam_Command           command,
                         EGdtf_RDMParam_SensorUnit        sensorUnit,
                         EGdtf_RDMParam_SensorUnitPrefix  sensorUnitPrefix,        
                         Sint32                           minValue,        
                         Sint32                           maxValue,
                         Sint32                           PDLSize,
                         const TXString&                        description);
        ~GdtfRDMParameter();
    private:
        // Attributes
        TXString                        fName;        
        Sint32                          fPID;                
        EGdtf_RDMParam_Type             fType;
        EGdtf_RDMParam_DataType         fDataType;
        EGdtf_RDMParam_Command          fCommand;
        EGdtf_RDMParam_SensorUnit       fSensorUnit;
        EGdtf_RDMParam_SensorUnitPrefix fSensorUnitPrefix;        
        Sint32                          fMinValue;        
        Sint32                          fMaxValue;
        Sint32                          fPDLSize;
        TXString                        fDescription;
        // Children
        TGdtfRDMParameterValueArray    fParameterValueArray;
    public:
        virtual EGdtfObjectType			GetObjectType();

    public:
        // Getter        
        const TXString&                 GetName() const;
        Sint32                          GetPID() const;
        EGdtf_RDMParam_Type             GetType() const;
        EGdtf_RDMParam_DataType         GetDataType() const;
        EGdtf_RDMParam_Command          GetCommand() const;
        EGdtf_RDMParam_SensorUnit       GetSensorUnit() const;
        EGdtf_RDMParam_SensorUnitPrefix GetSensorUnitPrefix() const;        
        Sint32                          GetMinValue() const;        
        Sint32                          GetMaxValue() const;
        Sint32                          GetPDLSize() const;
        const TXString&                 GetDescription() const;        
        const TGdtfRDMParameterValueArray &   GetParameterValueArray() const;
        // Setter       
        void SetName(const TXString& val);
        void SetPID(Sint32 val);
        void SetType(EGdtf_RDMParam_Type val);
        void SetDataType(EGdtf_RDMParam_DataType val);
        void SetCommand(EGdtf_RDMParam_Command val);
        void SetSensorUnit(EGdtf_RDMParam_SensorUnit val);
        void SetSensorUnitPrefix(EGdtf_RDMParam_SensorUnitPrefix val);        
        void SetMinValue(Sint32 val);        
        void SetMaxValue(Sint32 val);
        void SetPDLSize(Sint32 val);
        void SetDescription(const TXString& val); 

        GdtfRDMParameterValue* AddRMDValueBool();
        GdtfRDMParameterValue* AddDmxPersoalityDescription();
        GdtfRDMParameterValue* AddSensorDefinition();
        GdtfRDMParameterValue* AddSlotInfo();
        GdtfRDMParameterValue* AddStatusID_Desciption();

    protected:
        virtual	TXString				GetNodeName();
        virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
        virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual void                    OnErrorCheck(const IXMLFileNodePtr& pNode);
    };

    class GdtfRDMParameterNotification : public GdtfObject
    {
    public:
        GdtfRDMParameterNotification();
        GdtfRDMParameterNotification(Sint32 PID);
        ~GdtfRDMParameterNotification();
    private:
        // Attributes
        Sint32 fPID;
        // Childs
        TGdtfRDMParameterValueArray fParameterValueArray; 
    public:
        virtual EGdtfObjectType			GetObjectType();        
    public:
        // Getter
        Sint32	    	                GetPID() const;
        TGdtfRDMParameterValueArray     GetParameterValueArray() const;
        // Setter
        void						    SetPID(Sint32 val);
        GdtfRDMParameterValue*          AddRMDValueBool();
        GdtfRDMParameterValue*          AddRealTimeClock();
    protected:
        virtual	TXString				GetNodeName();
        virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
        virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual void                    OnErrorCheck(const IXMLFileNodePtr& pNode);
    };
    typedef GdtfRDMParameterNotification*	GdtfRDMParameterNotificationPtr;
    typedef std::vector<GdtfRDMParameterNotification*>	TGdtfRDMParameterNotificationArray;

    class GdtfRDMSensorNotification : public GdtfObject
    {
    public:
        GdtfRDMSensorNotification();
        GdtfRDMSensorNotification(Sint32 sensorOffset);
        ~GdtfRDMSensorNotification();
    private:
        // Attributes
        Sint32 fSensorOffset;
        // Childs                
        TGdtfRDMValueSensorArray fSensorValueArray;

    public:
        virtual EGdtfObjectType			     GetObjectType();
    public:
        // Getter        
        Sint32                               GetSensorOffset() const;
        TGdtfRDMValueSensorArray             GetSensorValueArray(); 
        // Setter       
        void						         SetSensorOffset(Sint32 val);
        GdtfRDMValueSensor*                  AddValueSensor(Sint32 value, Sint32 lowest, Sint32 highest, Sint32 recorded, EGdtf_RDMValue_ThresholdOperator thresholdOperator);

    protected:
        virtual	TXString				     GetNodeName();
        virtual	void					     OnPrintToFile(IXMLFileNodePtr pNode);
        virtual	void					     OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual void                         OnErrorCheck(const IXMLFileNodePtr& pNode);
    }; 
    typedef GdtfRDMSensorNotification*	GdtfRDMSensorNotificationPtr;
    typedef std::vector<GdtfRDMSensorNotification*>	TGdtfRDMSensorNotificationArray;

    class GdtfRDMNotifications : public GdtfObject
    {
    public:
        GdtfRDMNotifications();
        ~GdtfRDMNotifications();
    private:        
        // Childs        
        GdtfRDMAbsentNotification*         fRDMAbsentNotification;
        TGdtfRDMParameterNotificationArray fRDMParamNotificationArray;
        TGdtfRDMSensorNotificationArray    fRDMSensorNotificationArray;
    public:
        virtual EGdtfObjectType			GetObjectType();

    public:
        // Getter        
        GdtfRDMAbsentNotification*              GetAbsentNotification() const;
        TGdtfRDMParameterNotificationArray      GetParameterNotificationArray() const; 
        TGdtfRDMSensorNotificationArray         GetSensorNotificationArray() const;
        // Setter       
        void                                    SetAbsentNotification(GdtfRDMAbsentNotification* val); 
        GdtfRDMParameterNotification*           AddRDMParameterNotification(Sint32 PID);
        GdtfRDMSensorNotification*              AddDMSensorNotification(Sint32 sensorOffset);
    protected:
        virtual	TXString				        GetNodeName();
        virtual	void					        OnPrintToFile(IXMLFileNodePtr pNode);
        virtual	void					        OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual void                            OnErrorCheck(const IXMLFileNodePtr& pNode);
    };
    typedef GdtfRDMNotifications*	GdtfRDMNotificationsPtr;   


    class GdtfRDMAbsentNotification : public GdtfObject
    {
    public:
        GdtfRDMAbsentNotification();
        ~GdtfRDMAbsentNotification();
    private:                
        // See Issue: "GdtfRDMAbsentNotification #200"

        /* TODO: Check at another time again. The RDM Absent notification currently 
        does not have any attributes and does not have any children. (26.09.2018) */
    public:
        virtual EGdtfObjectType			GetObjectType();

    public:
        // Getter        
        // ..
        // Setter       
        // ..
    protected:
        virtual	TXString				GetNodeName();
    };
    typedef GdtfRDMAbsentNotification*	GdtfRDMAbsentNotificationPtr;
    typedef std::vector<GdtfRDMAbsentNotification*>	TGdtfRDMAbsentNotificationArray;
    
//-----------------------------------------------------------------------------
// RDM Values
//-----------------------------------------------------------------------------
    class GdtfRDMParameterValue : public GdtfObject
    {
    /*
        # ABSTRACT CLASS # 
        
        The following GdtfTypes inherit from this class:

            RDMValueBool
            RDMValue_UNSIGNED_BYTE
            RDMValue_SIGNED_BYTE
            RDMValue_UNSIGNED_WORD
            RDMValue_SIGNED_WORD
            RDMValue_UNSIGNED_DWORD
            RDMValue_SIGNED_DWORD
            RDMValue_ASCII
            RDMValue_DMX_PERSONALITY_DESCRIPTION
            RDMValue_SENSOR_DEFINITION
            RDMValue_SLOT_INFO
            RDMValue_STATUS_ID_ DESCRIPTION            
            RDMValue_REAL_TIME_CLOCK
    */ 
    public:
        GdtfRDMParameterValue();        
        ~GdtfRDMParameterValue();
    public:
        // Getter        
        // - 
        // Setter       
        // -
    public:
            virtual EGdtfObjectType			GetObjectType() = 0;
    protected:
            virtual	TXString				GetNodeName() = 0;
    };
  
    class GdtfRDMParameterValue_Numeric : public GdtfRDMParameterValue
    {
    /*
            # ABSTRACT CLASS #

            The following GdtfTypes inherit from this class (they are basically the same as we do not deffer between intBytes and the signedFlag):

            RDMValue_UNSIGNED_BYTE
            RDMValue_SIGNED_BYTE
            RDMValue_UNSIGNED_WORD
            RDMValue_SIGNED_WORD
            RDMValue_UNSIGNED_DWORD
            RDMValue_SIGNED_DWORD
            RDMValue_ASCII
    */
    public:
        GdtfRDMParameterValue_Numeric();
        GdtfRDMParameterValue_Numeric(Sint32 value, EGdtf_RDMValue_ThresholdOperator thresholdOperator);
        ~GdtfRDMParameterValue_Numeric();
    protected:
        // Attributes
        Sint32                           fValue;
        EGdtf_RDMValue_ThresholdOperator fThresholdOperator;
    public:
        // Getter        
        Sint32		                        GetValue() const;
        EGdtf_RDMValue_ThresholdOperator	GetThresholdOperator() const;
		
        // Setter
        void		                        SetValue(Sint32 value);
        void                            	SetThresholdOperator(EGdtf_RDMValue_ThresholdOperator value);
protected:
        virtual	TXString				    GetNodeName() = 0;
        virtual EGdtfObjectType			    GetObjectType() = 0;

        virtual	void					    OnPrintToFile(IXMLFileNodePtr pNode);
        virtual	void					    OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual void                        OnErrorCheck(const IXMLFileNodePtr& pNode);
    };    

    class GdtfRDMValueBool : public GdtfRDMParameterValue
    {
    public:
        GdtfRDMValueBool();
        GdtfRDMValueBool(EGdtf_RDMValueBool_Value value, EGdtf_RDMValue_ThresholdOperator thresholdOperator);
        ~GdtfRDMValueBool();
    private:        
        EGdtf_RDMValueBool_Value         fValue;
        EGdtf_RDMValue_ThresholdOperator fThresholdOperator;
    public:
        virtual EGdtfObjectType			 GetObjectType();
    public:
        // Getter        
        EGdtf_RDMValueBool_Value		        GetValue() const;
        EGdtf_RDMValue_ThresholdOperator        GetThresholdOperator() const;
        // Setter       
        void SetValue(EGdtf_RDMValueBool_Value value);
        void SetThresholdOperator(EGdtf_RDMValue_ThresholdOperator value);
    protected:
        virtual	TXString				GetNodeName();
        virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
        virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual void                    OnErrorCheck(const IXMLFileNodePtr& pNode);
    };
    typedef GdtfRDMValueBool*	GdtfRDMValueBoolPtr;

    // RDMParameterValue_Numeric

    class GdtfRDMValue_UNSIGNED_BYTE : public GdtfRDMParameterValue_Numeric
    {
    public:
        GdtfRDMValue_UNSIGNED_BYTE();
        GdtfRDMValue_UNSIGNED_BYTE(Sint32 value, EGdtf_RDMValue_ThresholdOperator thresholdOperator);
        ~GdtfRDMValue_UNSIGNED_BYTE();
    public:
        virtual EGdtfObjectType			GetObjectType();

    public:
        // Getter        
        // -
        // Setter       
        // -
    protected:
        virtual	TXString				GetNodeName();
    };
    typedef GdtfRDMValue_UNSIGNED_BYTE*	GdtfRDMValue_UNSIGNED_BYTEPtr;
    
    class GdtfRDMValue_SIGNED_BYTE : public GdtfRDMParameterValue_Numeric
    {
    public:
        GdtfRDMValue_SIGNED_BYTE();
        GdtfRDMValue_SIGNED_BYTE(Sint32 value, EGdtf_RDMValue_ThresholdOperator thresholdOperator);
        ~GdtfRDMValue_SIGNED_BYTE();
    private:       

    public:
        virtual EGdtfObjectType			GetObjectType();

    public:
        // Getter        
        // -
        // Setter       
        // -
    protected:
        virtual	TXString				GetNodeName();
    };
    typedef GdtfRDMValue_SIGNED_BYTE*	GdtfRDMValue_SIGNED_BYTEPtr;
        
    class GdtfRDMValue_UNSIGNED_WORD : public GdtfRDMParameterValue_Numeric
    {
    public:
        GdtfRDMValue_UNSIGNED_WORD();
        GdtfRDMValue_UNSIGNED_WORD(Sint32 value, EGdtf_RDMValue_ThresholdOperator thresholdOperator);
        ~GdtfRDMValue_UNSIGNED_WORD();
    private:       

    public:
        virtual EGdtfObjectType			GetObjectType();

    public:
        // Getter        
        // -
        // Setter       
        // -
    protected:
        virtual	TXString				GetNodeName();
    };
    typedef GdtfRDMValue_UNSIGNED_WORD*	GdtfRDMValue_UNSIGNED_WORDPtr;
     
    class GdtfRDMValue_SIGNED_WORD : public GdtfRDMParameterValue_Numeric
    {
    public:
        GdtfRDMValue_SIGNED_WORD();
        GdtfRDMValue_SIGNED_WORD(Sint32 value, EGdtf_RDMValue_ThresholdOperator thresholdOperator);
        ~GdtfRDMValue_SIGNED_WORD();
    private:       

    public:
        virtual EGdtfObjectType			GetObjectType();

    public:
        // Getter        
        // -
        // Setter       
        // -
    protected:
        virtual	TXString				GetNodeName();
    };
    typedef GdtfRDMValue_SIGNED_WORD*	GdtfRDMValue_SIGNED_WORDPtr;

    class GdtfRDMValue_UNSIGNED_DWORD : public GdtfRDMParameterValue_Numeric
    {
    public:
        GdtfRDMValue_UNSIGNED_DWORD();
        GdtfRDMValue_UNSIGNED_DWORD(Sint32 value, EGdtf_RDMValue_ThresholdOperator thresholdOperator);
        ~GdtfRDMValue_UNSIGNED_DWORD();
    private:       

    public:
        virtual EGdtfObjectType			GetObjectType();

    public:
        // Getter        
        // -
        // Setter       
        // -
    protected:
        virtual	TXString				GetNodeName();
    };
    typedef GdtfRDMValue_UNSIGNED_DWORD*	GdtfRDMValue_UNSIGNED_DWORDPtr;
        
    class GdtfRDMValue_SIGNED_DWORD : public GdtfRDMParameterValue_Numeric
    {
    public:
        GdtfRDMValue_SIGNED_DWORD();
        GdtfRDMValue_SIGNED_DWORD(Sint32 value, EGdtf_RDMValue_ThresholdOperator thresholdOperator);
        ~GdtfRDMValue_SIGNED_DWORD();
    private:       

    public:
        virtual EGdtfObjectType			GetObjectType();

    public:
        // Getter        
        // -
        // Setter       
        // -
    protected:
        virtual	TXString				GetNodeName();
    };
    typedef GdtfRDMValue_SIGNED_DWORD*	GdtfRDMValue_SIGNED_DWORDPtr;

    class GdtfRDMValue_ASCII : public GdtfRDMParameterValue_Numeric
    {
    public:
        GdtfRDMValue_ASCII();
        GdtfRDMValue_ASCII(Sint32 value, EGdtf_RDMValue_ThresholdOperator thresholdOperator);
        ~GdtfRDMValue_ASCII();
    private:       

    public:
        virtual EGdtfObjectType			GetObjectType();

    public:
        // Getter        
        // -
        // Setter       
        // -
    protected:
        virtual	TXString				GetNodeName();
    };
    typedef GdtfRDMValue_ASCII*	GdtfRDMValue_ASCIIPtr;

    class GdtfGdtfRDMValue_DMX_PERSONALITY_DESCRIPTION : public GdtfRDMParameterValue
    {
    public:
        GdtfGdtfRDMValue_DMX_PERSONALITY_DESCRIPTION();
        GdtfGdtfRDMValue_DMX_PERSONALITY_DESCRIPTION(Sint32 footPrint, TXString& description);
        ~GdtfGdtfRDMValue_DMX_PERSONALITY_DESCRIPTION();
    private:       
        Sint32   fFootPrint;
        TXString fDescription;
    public:
        virtual EGdtfObjectType			GetObjectType();

    public:
        // Getter        
        Sint32          GetFootPrint() const;
        const TXString& GetDescription() const;
        // Setter       
        void            SetFootPrint(Sint32 val);
        void            SetDescription(const TXString& val);
    protected:
        virtual	TXString				GetNodeName();
        virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
        virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual void                    OnErrorCheck(const IXMLFileNodePtr& pNode);
    };
    typedef GdtfGdtfRDMValue_DMX_PERSONALITY_DESCRIPTION*	GdtfGdtfRDMValue_DMX_PERSONALITY_DESCRIPTIONPtr;    
    
    class GdtfRDMValue_SENSOR_DEFINITION : public GdtfRDMParameterValue
    {
    public:
        GdtfRDMValue_SENSOR_DEFINITION();
        GdtfRDMValue_SENSOR_DEFINITION(
            EGdtf_RDMValue_SENSOR_DEFINITION_TYPE         type,
            EGdtf_RDMParam_SensorUnit                     unit,
            EGdtf_RDMParam_SensorUnitPrefix               prefix,
            Sint32                                        rangeMinValue,
            Sint32                                        rangeMaxValue,
            Sint32                                        normalMinValue,
            Sint32                                        normalMaxValue,
            EGdtf_RDMValue_LowesHighestDetectionSupported lowesHighestDetectionSupported,
            EGdtf_RDMValue_RecordValueSupported           recordValueSupported,
            TXString&                                     description);

        ~GdtfRDMValue_SENSOR_DEFINITION();
    private:        
        EGdtf_RDMValue_SENSOR_DEFINITION_TYPE fType;
        EGdtf_RDMParam_SensorUnit             fUnit;   // Defines the SI unit of the sensor data. Predefined values are the same as for the SensorUnit attribute of the RDM parameter. 
        EGdtf_RDMParam_SensorUnitPrefix       fPrefix; // Defines the SI prefix and the multiplication factor of the units. Sensor unit prefix; The predefined values are the same as for SensorUnitPrefix attribute of the RDM parameter. 
        Sint32 fRangeMinValue;
        Sint32 fRangeMaxValue;
        Sint32 fNormalMinValue;
        Sint32 fNormalMaxValue;
        EGdtf_RDMValue_LowesHighestDetectionSupported fLowesHighestDetectionSupported;
        EGdtf_RDMValue_RecordValueSupported           fRecordValueSupported;
        TXString fDescription;
    public:
        virtual EGdtfObjectType			GetObjectType();

    public:
        // Getter        
        EGdtf_RDMValue_SENSOR_DEFINITION_TYPE GetType() const;
        EGdtf_RDMParam_SensorUnit             GetUnit() const;
        EGdtf_RDMParam_SensorUnitPrefix       GetPrefix() const;
        Sint32 GetRangeMinValue() const;
        Sint32 GetRangeMaxValue() const;
        Sint32 GetNormalMinValue() const;
        Sint32 GetNormalMaxValueype() const;
        EGdtf_RDMValue_LowesHighestDetectionSupported GetLowesHighestDetectionSupported() const;
        EGdtf_RDMValue_RecordValueSupported           GetRecordValueSupported() const;
        const TXString& GetDescription() const;
        // Setter       
        void SetType(EGdtf_RDMValue_SENSOR_DEFINITION_TYPE val) ;
        void SetUnit(EGdtf_RDMParam_SensorUnit val) ;
        void SetPrefix(EGdtf_RDMParam_SensorUnitPrefix val) ;
        void SetRangeMinValue(Sint32 val) ;
        void SetRangeMaxValue(Sint32 val) ;
        void SetNormalMinValue(Sint32 val) ;
        void SetNormalMaxValueype(Sint32 val) ;
        void SetLowesHighestDetectionSupported(EGdtf_RDMValue_LowesHighestDetectionSupported val);
        void SetRecordValueSupported(EGdtf_RDMValue_RecordValueSupported val);
        void SetDescription(const TXString& val) ;
        // 
    protected:
        virtual	TXString				GetNodeName();
        virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
        virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual void                    OnErrorCheck(const IXMLFileNodePtr& pNode);
    };
    
    class GdtfRDMValue_SLOT_INFO : public GdtfRDMParameterValue
    {
    public:
        GdtfRDMValue_SLOT_INFO();
        GdtfRDMValue_SLOT_INFO(
            Sint32 offset,
            EGdtf_RDMValue_SLOT_INFO_Type  type,
            EGdtf_RDMValue_SLOT_INFO_SlotLabelID slotLabelID);
        
        ~GdtfRDMValue_SLOT_INFO();
    private:        
        Sint32                               fOffset;
        EGdtf_RDMValue_SLOT_INFO_Type        fType;
        EGdtf_RDMValue_SLOT_INFO_SlotLabelID fSlotLabelID;
    public:
        virtual EGdtfObjectType			    GetObjectType();

    public:
        // Getter        
        Sint32                               GetOffset()const;
        EGdtf_RDMValue_SLOT_INFO_Type        GetType()const;
        EGdtf_RDMValue_SLOT_INFO_SlotLabelID GetSlotLabelID()const;        
        // Setter       
        void SetOffset(Sint32 val);
        void SetType (EGdtf_RDMValue_SLOT_INFO_Type val);
        void SetSlotLabelID(EGdtf_RDMValue_SLOT_INFO_SlotLabelID val);
    protected:
        virtual	TXString				GetNodeName();
        virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
        virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual void                    OnErrorCheck(const IXMLFileNodePtr& pNode);
    };
    typedef GdtfRDMValue_SLOT_INFO*	GdtfGdtfRDMValue_SLOT_INFOPtr;

    class GdtfRDMValue_STATUS_ID_DESCRIPTION : public GdtfRDMParameterValue
    {
    public:
        GdtfRDMValue_STATUS_ID_DESCRIPTION();
        GdtfRDMValue_STATUS_ID_DESCRIPTION(Sint32 statusID, const TXString& description);
        ~GdtfRDMValue_STATUS_ID_DESCRIPTION();
    private:
        StatusID   fStatusID;
        TXString   fDescription;            
    public:
        virtual EGdtfObjectType			GetObjectType();

    public:
        // Getter        
        StatusID                    GetStatusID() const;
        const TXString&		        GetDescription() const;
        // Setter       
       void                         SetStatusID(StatusID val);
       void         		        SetDescription(const TXString& val);
    protected:
        virtual	TXString				GetNodeName();
        virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
        virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual void                    OnErrorCheck(const IXMLFileNodePtr& pNode);
    };
    typedef GdtfRDMValue_STATUS_ID_DESCRIPTION*	GdtfRDMValue_STATUS_ID_DESCRIPTIONPtr;
         
//-----------------------------------------------------------------------------    

    class GdtfRDMValue_RealTimeClock : public GdtfRDMParameterValue
    {
    public:        
        GdtfRDMValue_RealTimeClock();
        GdtfRDMValue_RealTimeClock(Sint32 year, Sint32 month, Sint32 day, Sint32 hours, Sint32 minute, Sint32 second, EGdtf_RDMValue_ThresholdOperator thresholdOperator);
        ~GdtfRDMValue_RealTimeClock();
    private:        
        Sint32 fYear; 
        Sint32 fMonth;
        Sint32 fDay;
        Sint32 fHours;
        Sint32 fMinute;
        Sint32 fSecond;
        EGdtf_RDMValue_ThresholdOperator fThresholdOperator;
    public:
        virtual EGdtfObjectType			GetObjectType();

    public:
        // Getter        
        Sint32                           GetYear() const; 
        Sint32                           GetMonth() const;
        Sint32                           GetDay() const;
        Sint32                           GetHours() const;
        Sint32                           GetMinute() const;
        Sint32                           GetSecond() const;
        EGdtf_RDMValue_ThresholdOperator GetThresholdOperator() const;
        // Setter
        void SetYear(Sint32 val); 
        void SetMonth(Sint32 val);
        void SetDay(Sint32 val);
        void SetHours(Sint32 val);
        void SetMinute(Sint32 val);
        void SetSecond(Sint32 val);
        void SetThresholdOperator(EGdtf_RDMValue_ThresholdOperator val);
    protected:
        virtual	TXString				GetNodeName();
        virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
        virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual void                    OnErrorCheck(const IXMLFileNodePtr& pNode);
    };
    typedef GdtfRDMValue_RealTimeClock*	GdtfRDMValue_RealTimeClockPtr;
    
    class GdtfRDMValueSensor : public GdtfObject
    {
    public:
        GdtfRDMValueSensor();
        GdtfRDMValueSensor(Sint32 value, Sint32 lowest, Sint32 highest, Sint32 recorded, EGdtf_RDMValue_ThresholdOperator thresholdOperator);
        ~GdtfRDMValueSensor();
    private:
        Sint32 fValue;
        Sint32 fLowest;
        Sint32 fHighest;
        Sint32 fRecorded;
        EGdtf_RDMValue_ThresholdOperator fThresholdOperator;
    public:
        virtual EGdtfObjectType			GetObjectType();

    public:
        // Getter        
        Sint32		                                    GetValue() const;
        Sint32		                                    GetLowest() const;
        Sint32		                                    GetHighest() const;
        Sint32		                                    GetRecorded() const;
        EGdtf_RDMValue_ThresholdOperator		        GetThresholdOperator() const;
        // Setter       
        void				SetValue(Sint32 val);
        void				SetLowest(Sint32 val);
        void				SetHighest(Sint32 val);
        void				SetRecorded(Sint32 val);
        void				SetThresholdOperator(EGdtf_RDMValue_ThresholdOperator val);
    protected:
        virtual	TXString				GetNodeName();
        virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
        virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual void                    OnErrorCheck(const IXMLFileNodePtr& pNode);
    };
    typedef GdtfRDMValueSensor*	GdtfRDMValueSensorPtr;

    class GdtfArtNet : public GdtfObject
    {
    public:
        GdtfArtNet();
        ~GdtfArtNet();
    private:
        // Atributes
        // TODO: This TYPE not defined in the docu to this day(26.09.18). Implement later.
    public:
        virtual EGdtfObjectType			GetObjectType();

    public:
        // Getter        
        //...
        // Setter       
        // ...
    protected:
        virtual	TXString				    GetNodeName();
        // virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
        // virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
    };
    typedef GdtfArtNet*	GdtfArtNetPtr;
    
    class GdtfsAcn : public GdtfObject
    {
    public:
        GdtfsAcn();
        ~GdtfsAcn();
    private:
        // Atributes
        // TODO: This TYPE not defined in the docu to this day(26.09.18). Implement later.
    public:
        virtual EGdtfObjectType			GetObjectType();

    public:
        // Getter        
        // ...
        // Setter       
        // ...
    protected:
        virtual	TXString				GetNodeName();
        // virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
        // virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
    };
    typedef GdtfsAcn*	GdtfsAcnPtr;    

    class GdtfKiNET : public GdtfObject
    {
    public:
        GdtfKiNET();
        ~GdtfKiNET();
    private:
        // Atributes
        // TODO: This TYPE not defined in the docu to this day(26.09.18). Implement later.
    public:
        virtual EGdtfObjectType			GetObjectType();

    public:
        // Getter        
        // ...
        // Setter       
        // ...
    protected:
        virtual	TXString				GetNodeName();
        //virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
        //virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
    };
    typedef GdtfKiNET*	GdtfKiNETPtr;

    class GdtfPosiStageNet : public GdtfObject
    {
    public:
        GdtfPosiStageNet();
        ~GdtfPosiStageNet();
    private:
        // Atributes
        // TODO: This TYPE not defined in the docu to this day(26.09.18). Implement later.
    public:
        virtual EGdtfObjectType			GetObjectType();

    public:
        // Getter        
        // ...
        // Setter       
        // ...
    protected:
        virtual	TXString				GetNodeName();
        //virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
        //virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
    };
    typedef GdtfPosiStageNet*	GdtfPosiStageNetPtr;

    class GdtfOpenSoundControl : public GdtfObject
    {
    public:
        GdtfOpenSoundControl();
        ~GdtfOpenSoundControl();
    private:
        // Atributes
        // TODO: This TYPE not defined in the docu to this day(26.09.18). Implement later.
    public:
        virtual EGdtfObjectType			GetObjectType();

    public:
        // Getter        
        // ...
        // Setter       
        // ...
    protected:
        virtual	TXString				GetNodeName();
        //virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
        //virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
    };
    typedef GdtfOpenSoundControl*	GdtfOpenSoundControlPtr;

    class GdtfCITP : public GdtfObject
    {
    public:
        GdtfCITP();
        ~GdtfCITP();
    private:
        // Atributes
        // TODO: This TYPE not defined in the docu to this day(26.09.18). Implement later.
    public:
        virtual EGdtfObjectType			GetObjectType();

    public:
        // Getter        
        // ...
        // Setter       
        // ...
    protected:
        virtual	TXString				GetNodeName();
        //virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
        //virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
    };
    typedef GdtfCITP*	GdtfCITPPtr;

	//------------------------------------------------------------------------------------
	// GdtfUserPreset Definition
	class GdtfUserPreset : public GdtfObject
	{
	public:
		GdtfUserPreset();
		~GdtfUserPreset();
		
	public:
		virtual EGdtfObjectType			GetObjectType();
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);

	};
	typedef GdtfUserPreset*					GdtfUserPresetPtr;
	typedef std::vector<GdtfUserPresetPtr>	TGdtfUserPresetArray;
	
	//------------------------------------------------------------------------------------
	// Macro Definitions

	class GdtfMacro : public GdtfObject
	{
	public:
		GdtfMacro(const TXString& name);
		~GdtfMacro();
		
	private:
        TXString fName;
        // Childs
        GdtfMacroDMX*    fMacroDMX;   
        GdtfMacroVisual* fMacroVisual;
    public:
        virtual EGdtfObjectType			GetObjectType();    
    public:
        // Getter
        const TXString&  GetName() const;        
        GdtfMacroDMX*    GetMacroDMX() const;
        GdtfMacroVisual* GetMacroVisual() const;
        // Setter
        void SetName(const TXString & name);
        void SetMacroDMX(GdtfMacroDMX* val);
        void SetMacroVisual(GdtfMacroVisual* val);
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);
	};
	typedef GdtfMacro*					GdtfMacroPtr;
	typedef std::vector<GdtfMacroPtr>	TGdtfMacroArray;
    
    class GdtfMacroDMXValue : public GdtfObject
    {
    public:
        GdtfMacroDMXValue();
        GdtfMacroDMXValue(DmxValue dmxVal, GdtfDmxChannelPtr dmxChannel);
        ~GdtfMacroDMXValue();
    private:
        DmxValue				fValue;
        TXString                funresolvedDMXChannel;   
        GdtfDmxChannelPtr       fDMXChannel;
    public:
        virtual EGdtfObjectType			GetObjectType();

    public:
        // Getter        
        DmxValue		            GetValue() const;
        const TXString&				GetUnresolvedDMXChannel() const;
        GdtfDmxChannelPtr           GetDMXChannel() const;
        // Setter       
        void						SetValue(DmxValue val);
        void                        SetDMXChannel(GdtfDmxChannelPtr chnl);

    protected:
        virtual	TXString				GetNodeName();
        virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
        virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual void                    OnErrorCheck(const IXMLFileNodePtr& pNode);
    };
    typedef GdtfMacroDMXValue*	GdtfMacroDMXValuePtr;
    typedef std::vector<GdtfMacroDMXValue*>	TGdtfMacroDMXValueArray;

    class GdtfMacroDMXStep : public GdtfObject
    {
    public:
        GdtfMacroDMXStep();
        GdtfMacroDMXStep(Sint32 duration);
        ~GdtfMacroDMXStep();
    private:
        Sint32 fDuration;
        // Childs
        TGdtfMacroDMXValueArray fDMXValues;
    public:
        virtual EGdtfObjectType	GetObjectType();

    public:
        // Getter        
        Sint32 GetDuration() const;
        TGdtfMacroDMXValueArray GetDMXValueArray() const;
        // Setter               
        void SetDuration(Sint32 d);
        //
        GdtfMacroDMXValuePtr AddDmxValue(DmxValue dmxVal, GdtfDmxChannelPtr dmxChannel);
    protected:
        virtual	TXString				GetNodeName();
        virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
        virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual void                    OnErrorCheck(const IXMLFileNodePtr& pNode);
    };
    typedef GdtfMacroDMXStep*	GdtfMacroDMXStepPtr;
    typedef std::vector<GdtfMacroDMXStep*>	TGdtfMacroDMXStepArray;
    
    class GdtfMacroDMX : public GdtfObject
    {
    public:
        GdtfMacroDMX();
        ~GdtfMacroDMX();
    private:
        TGdtfMacroDMXStepArray fDMXSetps;        
    public:
        virtual EGdtfObjectType			GetObjectType();
        virtual TGdtfMacroDMXStepArray  GetStepArray();
    public:
        GdtfMacroDMXStepPtr AddDmxStep(Sint32& duration);
    protected:
        virtual	TXString				GetNodeName();
        virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
        virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
    };

    class GdtfMacroVisualValue : public GdtfObject
    {
    public:
        GdtfMacroVisualValue();
        GdtfMacroVisualValue(DmxValue dmxVal, GdtfDmxChannelFunctionPtr channelFunctionRef);
        ~GdtfMacroVisualValue();
    private:
        DmxValue				  fDmxValue;
        TXString                  fUnresolvedChannelFunctionRef;
        GdtfDmxChannelFunctionPtr fChannelFunctionRef;
    public:
        virtual EGdtfObjectType			GetObjectType();

    public:
        // Getter        
        DmxValue                     GetDmxValue() const;
        const TXString&			     GetUnresolvedChannelFunctionRef() const;
        GdtfDmxChannelFunctionPtr    GetChannelFunctionRef() const;
        // Setter               
        void                         SetDmxValue(DmxValue val);
        void	        			 SetUnresolvedChannelFunctionRef(const TXString& ref);
        void                         SetChannelFunction(GdtfDmxChannelFunctionPtr ref);

    protected:
        virtual	TXString			GetNodeName();
        virtual	void				OnPrintToFile(IXMLFileNodePtr pNode);
        virtual	void				OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual void                OnErrorCheck(const IXMLFileNodePtr& pNode);
    };

    typedef GdtfMacroVisualValue*	GdtfMacroVisualValuePtr;
    typedef std::vector<GdtfMacroVisualValue*>	TGdtfMacroVisualValueArray;
    
    class GdtfMacroVisualStep : public GdtfObject
    {
    public:
        GdtfMacroVisualStep();
        ~GdtfMacroVisualStep();
    private:
        Sint32 fDuration;
        double  fFade;
        double  fDelay;
        // Childs
        TGdtfMacroVisualValueArray fVisualValues; 

    public:
        TGdtfMacroVisualValueArray GetVisualValueArray();
        virtual EGdtfObjectType	   GetObjectType();

    public:
        // Getter        
        Sint32  getDuration();
        double  getFade();
        double  getDelay();
        // Setter
        void setDuration(Sint32 d);
        void setFade(double f);
        void setDelay(double d);
        //
        GdtfMacroVisualValue* AddVisualValue(DmxValue& dmxVal, GdtfDmxChannelFunctionPtr channelFunctionRef);

    protected:
        virtual	TXString				GetNodeName();
        virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
        virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual void                    OnErrorCheck(const IXMLFileNodePtr& pNode);
    };
    typedef GdtfMacroVisualStep*	GdtfMacroVisualStepPtr;
    typedef std::vector<GdtfMacroVisualStep*>	TGdtfMacroVisualStepArray;
    
    class GdtfMacroVisual : public GdtfObject
    {
    public:
        GdtfMacroVisual();
        ~GdtfMacroVisual();
    private:        
        TGdtfMacroVisualStepArray fVisualSteps;
    public:
        virtual EGdtfObjectType			GetObjectType();

    public:
        TGdtfMacroVisualStepArray GetVisualStepArray();
        
        GdtfMacroVisualStepPtr AddVisualStep();

    protected:
        virtual	TXString				GetNodeName();
        virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
        virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
    };
    typedef GdtfMacroVisual*	GdtfMacroVisualPtr;

	//------------------------------------------------------------------------------------
	// GdtfPhysicalDescription Definition
	class GdtfMeasurementPoint : public GdtfObject
	{
	public:
		GdtfMeasurementPoint();
		~GdtfMeasurementPoint();
		
	private:
		double			fWaveLength;	// Unit nm
		double			fEngergy;		// Unit W/m^2*/nm		
		
	public:
		virtual EGdtfObjectType			GetObjectType();
        double                          GetWavelength();
        double                          GetEnergy();
		
		void							SetWavelength(double wavelength);
		void							SetEnergy(double energy);
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
		virtual void                    OnErrorCheck(const IXMLFileNodePtr& pNode);

	};
	typedef GdtfMeasurementPoint*				GdtfMeasurementPointPtr;
	typedef std::vector<GdtfMeasurementPoint*>	TGdtfMeasurementPointArray;

	
	class GdtfPhysicalEmitter : public GdtfObject
	{
	public:
		GdtfPhysicalEmitter();
		GdtfPhysicalEmitter(const TXString& name);
		~GdtfPhysicalEmitter();
		
	private:
		TXString					fName;
		CCieColor					fColor;
		//		
		TGdtfMeasurementPointArray	fMeasurePoints;
		
	public:
		virtual EGdtfObjectType				GetObjectType();
        const TXString&						GetName() const;
        CCieColor							GetColor() const;
        const TGdtfMeasurementPointArray    GetMeasurementPoints();
		virtual TXString					GetNodeReference();
		
		void							SetName(const TXString& name);
		void							SetColor(CCieColor color);
		GdtfMeasurementPoint*			AddMeasurementPoint();

	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);

	};
	typedef GdtfPhysicalEmitter*				GdtfPhysicalEmitterPtr;
	typedef std::vector<GdtfPhysicalEmitter*>	TGdtfPhysicalEmitterArray;
	
    class GdtfCRI : public GdtfObject
    {
    public:
        GdtfCRI();
        GdtfCRI(EGdtfColorSample ces, Sint32 colorTemp);
        ~GdtfCRI();
    private:
        // Attributes
        EGdtfColorSample fCES;
        Sint32           fColorTemperature;
    public:
        virtual EGdtfObjectType			GetObjectType();

    public:
        // Getter                
        EGdtfColorSample GetColorSample() const;
        Sint32           GetColorTemperature() const;
        // Setter       
        void SetColorSample(EGdtfColorSample val);
        void SetColorTemperature(Sint32 val);
    protected:
        virtual	TXString				GetNodeName();
        virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
        virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual void                    OnErrorCheck(const IXMLFileNodePtr& pNode);
    };
    typedef GdtfCRI*	GdtfCRIPtr;
    typedef std::vector<GdtfCRI*>	TGdtf_CRIArray;

    class GdtfCRIGroup : public GdtfObject
    {
    public:
        GdtfCRIGroup();
        GdtfCRIGroup(double colorTsemp);
        ~GdtfCRIGroup();
    private:
        // Attributes
        double fColorTemperature; // Color temperature; Default value : 6000; Unit: kelvin
		
		// Childs
        TGdtf_CRIArray fCRI_Array;
    public:
        virtual EGdtfObjectType			GetObjectType();

    public:
        // Getter        
        double         GetColorTemperature() const;
        TGdtf_CRIArray GetCRI_Array() const;
        // Setter       
        void            SetColorTemperature(double val);
        GdtfCRIPtr      Add_CRI(EGdtfColorSample ces, Sint32 colorTemp);
    protected:
        virtual	TXString				GetNodeName();
        virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
        virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual void                    OnErrorCheck(const IXMLFileNodePtr& pNode);
    };
    typedef GdtfCRIGroup*	GdtfCRIGroupPtr;
    typedef std::vector<GdtfCRIGroup*>	TGdtf_CRIGroupArray;

	class GdtfDMXProfile : public GdtfObject
     {
     public:
         GdtfDMXProfile();
         ~GdtfDMXProfile();
     private:
         // Attributes
     public:
         virtual EGdtfObjectType			GetObjectType();

     public:
         // Getter        
         //
         // Setter       
         //
     protected:
         virtual	TXString				GetNodeName();
         virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
         virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
     };
     typedef GdtfDMXProfile*	GdtfDMXProfilePtr;
     typedef std::vector<GdtfDMXProfile*>	TGdtfDMXProfileArray;
	

	//------------------------------------------------------------------------------------
	// GdtfFixture Definition
	class GdtfFixture : public GdtfObject
	{
	public:
		GdtfFixture(IFileIdentifierPtr file);
		GdtfFixture();
		~GdtfFixture();
		
	private:
		//------------------------------------------------
		// Parameters for a GdtfFixture
		TXString		fName;
		TXString		fShortName;
		TXString		fManufacturer;
		TXString		fFixtureTypeDescription;
		GdtfFixtureGUID	fGuid;
		GdtfPNGFile		fTumbnail;
		TXString		fTumbnailFullPath;
		GdtfFixtureGUID	fLinkedGuid;
		bool			fHasLinkedGuid;

		//------------------------------------------------
		// Storage
        
        // This are not seperated here and placed in the AttributeDefinitions node
        // there is no special class for this
		TGdtfActivationGroupArray		fActivationGroups;
		TGdtfFeatureGroupArray			fFeatureGroups;
		TGdtfAttributeArray				fAttributes;
        
		TGdtfWheelArray					fWheels;
		TGdtfModelArray					fModels;
		TGdtfGeometryArray				fGeometries;
		TGdtfDmxModeArray				fDmxModes;
		TGdtfRevisionArray				fRevisions;
		TGdtfUserPresetArray			fPresets;
		TGdtfMacroArray					fMacros;
		
		TGdtfPhysicalEmitterArray		fEmitters;
        TGdtfDMXProfileArray            fDmxProfiles;
        TGdtf_CRIGroupArray             fCRI_Groups;
		

		GdtfProtocols					fProtocollContainer;
		
		//------------------------------------------------
		// Reading support
		TVWArray_IFileIdentifier		fLocalFiles;
		bool							fReaded;
		IFolderIdentifierPtr			fWorkingFolder;
        TGdtfParsingErrorArray          fParsingErrors;

public:
        static void                     AddError(const GdtfParsingError& error);
        static TGdtfParsingErrorArray*  __ERROR_CONTAINER_POINTER;
        TGdtfParsingErrorArray&         GetParsingErrorArray();
        
private:
        TGdtfParsingErrorArray          fErrorContainer;
        
		
	public:
		//----------------------------------------------------------------------------------------------------------------------------------------------------------------
		// Getter
		const TXString&		GetName() const;
        const TXString&		GetShortName() const;
        const TXString&		GetManufacturer() const;
        const TXString&		GetFixtureTypeDescription() const;
        GdtfFixtureGUID		GetGuid() const;
		GdtfFixtureGUID		GetLinkedGuid() const;
		bool				HasLinkedGuid() const;
        const GdtfPNGFile&  GetPNGFile() const;
		const GdtfPNGFile&  GetPNGFileFullPath();		
        // Setter
		void				SetName(const TXString& name);
		void				SetShortName(const TXString& shortName);
		void				SetManufacturer(const TXString& manu);
		void				SetFixtureTypeDescription(const TXString& desc);
		void				SetGuid(const VWFC::Tools::VWUUID& uuid);
		void				SetLinkedGuid(const VWFC::Tools::VWUUID& uuid);
		void				SetPNGFile(const GdtfPNGFile& png);
	public:
		//----------------------------------------------------------------------------------------------------------------------------------------------------------------
		// Add calls
		GdtfRevisionPtr			AddRevision(const TXString& text, const STime& date);
		GdtfAttributePtr		AddAttribute(const TXString& name, const TXString& prettyName);
		
		GdtfModelPtr			AddModel(const TXString& name);
		GdtfGeometryPtr			AddGeometry(		const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometryPtr			AddGeometryReference(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometryPtr			AddGeometryShaper(	const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometryPtr			AddGeometryColor(	const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometryPtr			AddGeometryGobo(	const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometryPtr			AddGeometryBeam(	const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometryPtr			AddGeometryWithAxis(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometryPtr			AddGeometryWithLamp(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
				
		GdtfWheelPtr			AddWheel(TXString name);
		GdtfDmxModePtr			AddDmxMode(const TXString& name);
		GdtfPhysicalEmitterPtr	AddEmitter(const TXString& name);
		GdtfMacroPtr			AddMacro(const TXString& name);
        GdtfDMXProfilePtr       AddDmxProfile();

		GdtfUserPresetPtr		AddUserPreset();
		GdtfFeatureGroupPtr		AddFeatureGroup(const TXString& name, const TXString& prettyName);
		GdtfActivationGroupPtr	AddActivationGroup(const TXString& name);
        GdtfCRIGroupPtr         AddCRIGroup(double colorTsemp);

		//----------------------------------------------------------------------------------------------------------------------------------------------------------------
		// Read calls
		const TGdtfWheelArray&                  GetWheelArray();
		const TGdtfGeometryArray&               GetGeometryArray();
        const TGdtfActivationGroupArray&        GetActivationGroupArray();
        const TGdtfFeatureGroupArray&           GetFeatureGroupArray();
        const TGdtfAttributeArray&              GetAttributeArray();
        const TGdtfModelArray&                  GetModelArray();
        const TGdtfDmxModeArray&                GetDmxModeArray();
        const TGdtfRevisionArray&               GetRevisionArray();
        const TGdtfUserPresetArray&             GetPresetArray();
        const TGdtfMacroArray&                  GetMacroArray();
        const TGdtfPhysicalEmitterArray&		GetPhysicalEmitterArray();
        const TGdtfDMXProfileArray&             GetDmxProfileArray();
        const TGdtf_CRIGroupArray&              GetCRIGroupArray();
		
		GdtfProtocols&							GetProtocollContainer();

        
        
	public:
		virtual EGdtfObjectType			GetObjectType();
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void			        OnErrorCheck(const IXMLFileNodePtr& pNode);

		        
        GdtfAttributePtr            getAttributeByRef(const TXString& ref);
        GdtfWheelPtr                getWheelByRef(const TXString& ref);		
		GdtfPhysicalEmitterPtr      getEmiterByRef(const TXString& ref);
        GdtfDmxChannelFunctionPtr   getDmxFunctionByRef(const TXString& ref, GdtfDmxModePtr mode);
		GdtfDmxChannelPtr           getDmxChannelByRef(const TXString& ref, GdtfDmxModePtr mode);

		//
		void AutoGenerateNames(GdtfDmxModePtr dmxMode);
		
		// Resolve References		
		void ResolveAllReferences();
		void ResolveGeometryRefs();
		void ResolveGeometryRefs_Recursive(GdtfGeometryPtr geometry);
		
		void ResolveAttribRefs();		
		void ResolveDmxModeRefs();
        void ResolveDMXModeMasters();
		void ResolveDmxRelationRefs(GdtfDmxModePtr dmxMode);
		void ResolveDmxChannelRefs(GdtfDmxModePtr dmxMode);
		GdtfGeometryPtr ResolveGeometryRef(const TXString& unresolvedGeoRef, const TGdtfGeometryArray& geometryArray);
		
		void ResolveDmxLogicalChanRefs(GdtfDmxChannelPtr dmxChnl);
		void ResolveDmxChanelFunctionRefs(GdtfDmxLogicalChannelPtr dmxLogChnl);		
		//----------------------------------------------------------------------------------------------------------------------------------------------------------------
		
	public:
		bool							ExportToFile(IZIPFilePtr& zipfile);
		
		bool							IsReaded();
		void							GetWorkingFolder(IFolderIdentifierPtr& folder);
	};
}