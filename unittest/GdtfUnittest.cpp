//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Unittest.h"
#include "GdtfUnittest.h"
#include <iostream>
#include "Utility.h"
#include "Include/VectorworksMVR.h"
using namespace VectorworksMVR;
using namespace VectorworksMVR::GdtfDefines;


#define __checkVCOM(x) this->checkVCOM(x, #x)
#define __checkVCOM_NotSet(x) this->checkVCOM_NotSet(x, #x)


GdtfUnittest::GdtfUnittest(const std::string& currentDir)
{
    fAppDataFolder = currentDir;
	#ifdef GS_MAC
	fAppDataFolder += "/Library/Application Support/mvrexchange"; 
	#endif

    fTestGdtf_Path = currentDir + kSeparator + "testGdtf.gdtf";

    fTestResourcesFolder = UnitTestUtil::GetTestResourceFolder();

    std::cout << "Export File to " << fTestGdtf_Path << std::endl; 
}

GdtfUnittest::~GdtfUnittest()
{
}

bool GdtfUnittest::ExecuteTest()
{
	std::cout << "=                                        GdtfUnittest                                      =" << std::endl;
    WriteFile();
    ReadFile();

    return true;
}

void GdtfUnittest::WriteFile()
{
	//------------------------------------------------------------------------------------------------
	// Create Pointer to GDTF Interface
	IGdtfFixturePtr gdtfWrite (IID_IGdtfFixture);
    
    MvrUUID uuid		(225204211	, 177198167	, 1575790	, 96627);

    checkifTrue("Check UUID exual operator: ", uuid == uuid);

	MvrUUID linkedUuid	(2227440	, 1542265	, 1573622	, 2328410);
    if(__checkVCOM(gdtfWrite->OpenForWrite(fTestGdtf_Path.c_str(),"My FixtureName","My Manufacturer", uuid)))
    {
		__checkVCOM(gdtfWrite->SetFixtureTypeDescription("My Description"));
		__checkVCOM(gdtfWrite->SetShortName("My shortName"));
		__checkVCOM(gdtfWrite->SetLongName("My Long Long Name"));
		__checkVCOM(gdtfWrite->SetFixtureThumbnail("MyThumbnail"));
		__checkVCOM(gdtfWrite->SetLinkedFixtureGUID(linkedUuid));

		__checkVCOM(gdtfWrite->SetCanHaveChildren(EGdtfCanHaveChildren::eNO));

        //------------------------------------------------------------------------------    
        // Add Test Resources
        __checkVCOM( gdtfWrite->AddFileToGdtfFile( GetTestPNG_ThumbNail().c_str(), ERessourceType::RessoureFixture) );
        __checkVCOM( gdtfWrite->AddFileToGdtfFile( GetTestSVG_ThumbNail().c_str(), ERessourceType::RessoureFixture) );
        __checkVCOM( gdtfWrite->AddFileToGdtfFile( GetTestWheel_PNG().c_str(),     ERessourceType::ImageWheel) );
        __checkVCOM( gdtfWrite->AddFileToGdtfFile( GetTest3DS_Model().c_str(),     ERessourceType::Model3DS) );
        __checkVCOM( gdtfWrite->AddFileToGdtfFile( GetTestSVG_Model().c_str(),     ERessourceType::ModelSVG) );
        
		//------------------------------------------------------------------------------    
		// Set Attributes
		IGdtfActivationGroupPtr gdtfActGroup;
		__checkVCOM(gdtfWrite->CreateActivationGroup("My actGroupName", &gdtfActGroup));

		IGdtfFeatureGroupPtr	gdtfFeatureGroup;
		IGdtfFeaturePtr			gdtfFeature;
		if (__checkVCOM(gdtfWrite->CreateFeatureGroup("My featureGroupName", "My featureGroupPrettyName", &gdtfFeatureGroup)))
		{
			__checkVCOM(gdtfFeatureGroup->CreateFeature("My featureName", &gdtfFeature));
		}

		IGdtfAttributePtr		gdtfMainAttribute;
		if (__checkVCOM(gdtfWrite->CreateAttribute("My MainAttributeName", "My MainAttributePrettyName", &gdtfMainAttribute)))
		{
			__checkVCOM(gdtfMainAttribute->SetActivationGroup(gdtfActGroup));
			__checkVCOM(gdtfMainAttribute->SetFeature(gdtfFeature));
			__checkVCOM(gdtfMainAttribute->SetPhysicalUnit(EGdtfPhysicalUnit::Acceleration));

			CieColor cieCol;
			cieCol.fx	= 0.1;
			cieCol.fy	= 0.2;
			cieCol.f_Y	= 0.3;
			__checkVCOM(gdtfMainAttribute->SetColor(cieCol));
		}
		
		IGdtfAttributePtr		gdtfAttribute;
		if (__checkVCOM(gdtfWrite->CreateAttribute("My attributeName", "My attributePrettyName", &gdtfAttribute)))
		{
			__checkVCOM(gdtfAttribute->SetActivationGroup(gdtfActGroup));
			__checkVCOM(gdtfAttribute->SetFeature(gdtfFeature));
			__checkVCOM(gdtfAttribute->SetPhysicalUnit(EGdtfPhysicalUnit::Angle));


			__checkVCOM(gdtfAttribute->SetMainAttribute(gdtfMainAttribute));
			// TODO: CHeck if this comes thru
		}

        //------------------------------------------------------------------------------------------------------------------
        // Filters

        CieColor filterColor; 
		filterColor.fx	= 0.1;
		filterColor.fy	= 0.2;
		filterColor.f_Y	= 0.3;

        IGdtfFilterPtr gdtfFilter; gdtfWrite->CreateFilter( "My Filter", filterColor, &gdtfFilter);

        // Filter.Measurements
        // (The Meaurement attributes are check in the Emitter test.)        

        IGdtfMeasurementPtr gdtfMeasureA;  __checkVCOM(gdtfFilter->CreateMeasurement(&gdtfMeasureA));
        IGdtfMeasurementPtr gdtfMeasureB;  __checkVCOM(gdtfFilter->CreateMeasurement(&gdtfMeasureB) );
        IGdtfMeasurementPtr gdtfMeasureC;  __checkVCOM(gdtfFilter->CreateMeasurement(&gdtfMeasureC) );


		//------------------------------------------------------------------------------    
		// Set Wheels
		IGdtfWheelPtr gdtfWheelObj;
		if (__checkVCOM(gdtfWrite->CreateWheel("My Wheel1", &gdtfWheelObj)))
		{
			IGdtfWheelSlotPtr wheelSlotContainer;
			if (__checkVCOM(gdtfWheelObj->CreateWheelSlot("My WheelSlot1Wheel1", &wheelSlotContainer)))
			{
				CieColor cieCol;
				cieCol.fx  = 0.5;
				cieCol.fy  = 0.424242;
				cieCol.f_Y = 1.0;
				__checkVCOM(wheelSlotContainer->SetColor(cieCol));

				// Set PrismFacet
				// no "ox, oy, oz" entries here
				STransformMatrix ma;
				ma.ux = 1;ma.vx = 4;ma.wx = 7;
				ma.uy = 2;ma.vy = 5;ma.wy = 8;
				ma.uz = 3;ma.vz = 6;ma.wz = 9;

				CieColor facetCol;
				facetCol.fx  = 0.424242;
				facetCol.fy  = 1.0;
				facetCol.f_Y = 0.5;

				IGdtfWheelSlotPrismFacetPtr gdtfFacet;
				if (__checkVCOM(wheelSlotContainer->CreatePrismFacet(ma, &gdtfFacet)))
				{
					__checkVCOM(gdtfFacet->SetColor(facetCol));
				}

				// Set Gobo
				wheelSlotContainer->SetGobo("MWheel_Img1");

				//Set AnimationSystem
				IGdtfWheelSlotAnimationSystemPtr gdtfAnimationSystem;
				__checkVCOM(wheelSlotContainer->CreateAnimationSystem(1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0 /*radius*/, &gdtfAnimationSystem));


				// Set Filter link
				__checkVCOM(wheelSlotContainer->SetFilter(gdtfFilter));
			}
		}


		//------------------------------------------------------------------------------    
		// Set Emitter
		IGdtfPhysicalEmitterPtr gdtfEmitter;
		CieColor color;
		color.fx = 1.0;
		color.fy = 0.5;
		color.f_Y = 0.424242;
		if (__checkVCOM(gdtfWrite->CreateEmitter("My emitterName", color, &gdtfEmitter)))
		{
            gdtfEmitter->SetDominantWaveLength(66.6);
            gdtfEmitter->SetDiodePart("MyDiodePart");

			IGdtfMeasurementPtr gdtfMeasurement;            
			__checkVCOM(gdtfEmitter->CreateMeasurement(&gdtfMeasurement));
            gdtfMeasurement->SetPhysical(1.23);
            gdtfMeasurement->SetLuminousIntensity(2.34);
            gdtfMeasurement->SetTransmission(4.56);
            gdtfMeasurement->SetInterpolationTo(EGdtfInterpolationTo::Log);
            
            //-----------------------------------------------------------------------------
            // MeasurementPoint
            IGdtfMeasurementPointPtr gdtfMeasurPoint;
            gdtfMeasurement->CreateMeasurementPoint(&gdtfMeasurPoint);
            gdtfMeasurPoint->SetEnergy(1.23);
            gdtfMeasurPoint->SetWaveLength(2.34);
		}


		//------------------------------------------------------------------------------------------------------------------
		// Set ColorSpace Space
		IGdtfColorSpacePtr colorSpace;
		__checkVCOM(gdtfWrite->GetColorSpace( & colorSpace));
		__checkVCOM(colorSpace->SetColorSpace(EGdtfColorSpace::ANSI));

        //------------------------------------------------------------------------------------------------------------------
		// Handle Models
		IGdtfModelPtr gdtfModel;
		if (__checkVCOM(gdtfWrite->CreateModel("My modelName", &gdtfModel)))
		{
			__checkVCOM(gdtfModel->SetGeometryFile("MyModel"));
			__checkVCOM(gdtfModel->SetHeight(10));
			__checkVCOM(gdtfModel->SetWidth(20));
			__checkVCOM(gdtfModel->SetLength(30));
			__checkVCOM(gdtfModel->SetPrimitiveType(EGdtfModel_PrimitiveType::eGdtfModel_PrimitiveType_Sphere));
		}


		//------------------------------------------------------------------------------------------------------------------
		// Handle Geometry
		STransformMatrix ma;
		ma.ux = 1;ma.vx = 4;ma.wx = 7;ma.ox = 10;
		ma.uy = 2;ma.vy = 5;ma.wy = 8;ma.oy = 11;
		ma.uz = 3;ma.vz = 6;ma.wz = 9;ma.oz = 12;

		// Create First child
		IGdtfGeometryPtr childGeo;
		__checkVCOM(gdtfWrite->CreateGeometry(EGdtfObjectType::eGdtfGeometry, "My nameGeometry", gdtfModel, ma, &childGeo));

		// Create Child in Child
		IGdtfGeometryPtr innerChildGeo;
		__checkVCOM(childGeo->CreateGeometry(EGdtfObjectType::eGdtfGeometry, "My Inner Geo", gdtfModel, ma, &innerChildGeo));

		IGdtfGeometryPtr geoRef1;
		__checkVCOM(gdtfWrite->CreateGeometry(EGdtfObjectType::eGdtfGeometryReference, "My Reference", gdtfModel, ma, &geoRef1));
		__checkVCOM(geoRef1->SetGeometryReference(childGeo));

		IGdtfGeometryPtr geoRef2;
		__checkVCOM(gdtfWrite->CreateGeometry(EGdtfObjectType::eGdtfGeometryReference, "My Ref to Inner Obj", gdtfModel, ma, &geoRef2));
		__checkVCOM(geoRef2->SetGeometryReference(innerChildGeo));

		IGdtfBreakPtr gdtfBreak;
		__checkVCOM(geoRef2->CreateBreak(3,4,& gdtfBreak));

        // Beam Geometry
        IGdtfGeometryPtr beamGeo;        
        __checkVCOM(gdtfWrite->CreateGeometry(EGdtfObjectType::eGdtfGeometryLamp, "My Lamp Geometry", gdtfModel, ma, &beamGeo));
        beamGeo->SetLuminousIntensity(5);

		//------------------------------------------------------------------------------
		// Get dmxModes
		IGdtfDmxModePtr gdtfDmxMode;
		if (__checkVCOM(gdtfWrite->CreateDmxMode("My DmxModeName", &gdtfDmxMode)))
		{
			__checkVCOM(gdtfDmxMode->SetGeometry(childGeo));
			
			IGdtfDmxChannelPtr 			gdtfDmxChannel;
			IGdtfDmxChannelFunctionPtr	gdftChannelFunction;
			if (__checkVCOM(gdtfDmxMode->CreateDmxChannel(childGeo, &gdtfDmxChannel)))
			{
				__checkVCOM(gdtfDmxChannel->SetCoarse(1));
				__checkVCOM(gdtfDmxChannel->SetFine(2));
				__checkVCOM(gdtfDmxChannel->SetUltra(3));
				__checkVCOM(gdtfDmxChannel->SetUber(4));
				__checkVCOM(gdtfDmxChannel->SetDefaultValue(5));
				__checkVCOM(gdtfDmxChannel->SetHighlight(6));
				__checkVCOM(gdtfDmxChannel->SetDmxBreak(7));
				__checkVCOM(gdtfDmxChannel->SetGeometry(childGeo));

				IGdtfDmxLogicalChannelPtr gdtfLogicalChannel;
				if (__checkVCOM(gdtfDmxChannel->CreateLogicalChannel(gdtfAttribute, &gdtfLogicalChannel)))
				{
					__checkVCOM(gdtfLogicalChannel->SetAttribute(gdtfAttribute));
					__checkVCOM(gdtfLogicalChannel->SetDmxMaster(EGdtfDmxMaster::eGdtfDmxMaster_Grand));
					__checkVCOM(gdtfLogicalChannel->SetDmxSnap(EGdtfDmxSnap::eGdtfDmxMaster_On));
				    __checkVCOM(gdtfLogicalChannel->SetMoveInBlackFrames(8));
				    __checkVCOM(gdtfLogicalChannel->SetDmxChangeTimeLimit(9));

					
					if (__checkVCOM(gdtfLogicalChannel->CreateDmxFunction("My nameDmxFunction", &gdftChannelFunction)))
					{
						IGdtfAttributePtr attribute;
						__checkVCOM(gdftChannelFunction->SetAttribute(gdtfAttribute));
						__checkVCOM(gdftChannelFunction->SetOriginalAttribute("My orginalAttribute"));
						__checkVCOM(gdftChannelFunction->SetStartAddress(0));
						__checkVCOM(gdftChannelFunction->SetPhysicalStart(2));
						__checkVCOM(gdftChannelFunction->SetPhysicalEnd(3));
						__checkVCOM(gdftChannelFunction->SetRealFade(4));
						__checkVCOM(gdftChannelFunction->SetRealAcceleration(5));
						__checkVCOM(gdftChannelFunction->SetOnWheel(gdtfWheelObj));
						__checkVCOM(gdftChannelFunction->SetEmitter(gdtfEmitter));

                        // Set the Linked Filter
                        __checkVCOM(gdftChannelFunction->SetFilter(gdtfFilter));

						IGdtfDmxChannelSetPtr gdtfChannelSet;
						if (__checkVCOM(gdftChannelFunction->CreateDmxChannelSet("My nameDmxChannelSet", 1, 2, &gdtfChannelSet)))
						{
							__checkVCOM(gdtfChannelSet->SetPhysicalEnd(20));
							__checkVCOM(gdtfChannelSet->SetPhysicalStart(10));
							__checkVCOM(gdtfChannelSet->SetWheelSlot(11));
						}
					}
				}
			}

			// Add Relation
			IGdtfDmxRelationPtr relation;
			__checkVCOM(gdtfDmxMode->CreateDmxRelation("My Relation", EGdtfDmxRelationType::eGdtfDmxRelationType_Multiply, gdtfDmxChannel, gdftChannelFunction, & relation));

			// Add Macro
			IGdtfMacroPtr macro;
			__checkVCOM(gdtfDmxMode->CreateDmxMacro("My Macro", &macro));
		}

		// Add Revision
		IGdtfRevisionPtr rev;
		STime timestamp;
		timestamp.fYear = 2020; timestamp.fMonth = 12; timestamp.fDay = 2;
		timestamp.fHour = 22; timestamp.fMinute = 33; timestamp.fSecond = 44;
		__checkVCOM(gdtfWrite->CreateRevision("Revision TestText", timestamp, &rev));
		__checkVCOM(rev->SetUserId(254));

        //------------------------------------------------------------------------------    
        // Add RDM 
        IGdtfTRDMPtr rdm;
        __checkVCOM (gdtfWrite->CreateRDM(&rdm) );        
        __checkVCOM (rdm->SetDeviceModelID(1) );
        __checkVCOM (rdm->SetManufacturerID(2) );        

        //------------------------------------------------------------------------------    
        // Add SoftwareVersionID
        IGdtfSoftwareVersionIDPtr softID;
        __checkVCOM (rdm->CreateSoftwareVersionID( 22, &softID));        

        //------------------------------------------------------------------------------    
        // Add DMXPersonality

        IGdtfDMXPersonalityPtr dmxPerso;
        __checkVCOM (softID->CreateDMXPersonality( 11, gdtfDmxMode, &dmxPerso));        

		//------------------------------------------------------------------------------    
		// Close the stream and dump to disk
        __checkVCOM(gdtfWrite->Close());
    }
}

void GdtfUnittest::ReadFile()
{
	//------------------------------------------------------------------------------    
	// Read Fixture Information
	IGdtfFixturePtr gdtfRead (IID_IGdtfFixture);
    if(__checkVCOM(gdtfRead->ReadFromFile(fTestGdtf_Path.c_str())))
    {
		//Check those written UUIDs
		MvrUUID fixtureUUID	(225204211, 177198167, 	1575790, 	96627);
		MvrUUID linkedUUID	(2227440, 	1542265, 	1573622,	2328410);
		MvrUUID resultUUID	(0,0,0,0);


		// Check Fixture Name
		MvrString fixtureName		= gdtfRead->GetName();
		MvrString fixtureLongName	= gdtfRead->GetLongName();
		MvrString fixtureShortName	= gdtfRead->GetShortName();
		MvrString manufacturer		= gdtfRead->GetManufacturer();
		MvrString description		= gdtfRead->GetFixtureTypeDescription();

		this->checkifEqual("GetName "					, fixtureName		, "My FixtureName");
		this->checkifEqual("GetShortName "				, fixtureShortName	, "My shortName");
		this->checkifEqual("GetManufacturer "			, manufacturer		, "My Manufacturer");
		this->checkifEqual("GetFixtureTypeDescription "	, description		, "My Description");
		this->checkifEqual("GetLongName "				, fixtureLongName	, "My Long Long Name");

		__checkVCOM(gdtfRead->GetFixtureGUID(resultUUID));
		this->checkifEqual("GetFixtureGUID fixtureUUID ", fixtureUUID, resultUUID);

		EGdtfCanHaveChildren canHaveChildren;
		__checkVCOM(gdtfRead->GetCanHaveChildren(canHaveChildren));
		this->checkifEqual("GetCanHaveChildren ", (size_t) canHaveChildren, (size_t) EGdtfCanHaveChildren::eNO);

		//-----------------------------------------------------------------------------
		// Check the file content
		size_t ressourceFiles = 0;
		__checkVCOM(gdtfRead->GetImageRessourcesCount(ressourceFiles));
		this->checkifEqual("GetImageRessourcesCount", ressourceFiles, size_t(5));

		CheckAttachedFiles(gdtfRead, 0, this->GetTestPNG_ThumbNail(true));
		CheckAttachedFiles(gdtfRead, 1, this->GetTestSVG_ThumbNail(true));
		CheckAttachedFiles(gdtfRead, 2, this->GetTestWheel_PNG(true));
		CheckAttachedFiles(gdtfRead, 3, this->GetTest3DS_Model(true));
		CheckAttachedFiles(gdtfRead, 4, this->GetTestSVG_Model(true));


		
        //-----------------------------------------------------------------------------
		// Get the Thumbnail-Image from GDTF File
		MvrString thumbFileName		= gdtfRead->GetFixtureThumbnail();
		MvrString fullPath_PNG		= gdtfRead->GetFixtureThumbnail_PNG_FullPath();
        MvrString fullPath_SVG      = gdtfRead->GetFixtureThumbnail_SVG_FullPath();        

		this->checkifEqual("GetFixtureThumbnail "		, thumbFileName,  "MyThumbnail"); 
        
        // Check if the Resource Files have been unpacked correctly.
		this->checkifEqual("GetFixtureThumbnail "		, fullPath_PNG, fAppDataFolder + kSeparator + "GdtfGroup" + kSeparator + "MyThumbnail.png" ); 
        this->checkifEqual("GetFixtureThumbnail "		, fullPath_SVG, fAppDataFolder + kSeparator + "GdtfGroup" + kSeparator + "MyThumbnail.svg");        
        
        this->checkifTrue("Testwheel PNG exists.", UnitTestUtil::FileExists (fullPath_PNG) );
        this->checkifTrue("Testmodel SVG exits.", UnitTestUtil::FileExists (fullPath_SVG) );
        //-----------------------------------------------------------------------------

		bool hasLinkedFixture = false;
		__checkVCOM(gdtfRead->HasLinkedFixtureGUID(hasLinkedFixture));
		__checkVCOM(gdtfRead->GetLinkedFixtureGUID(resultUUID));
		this->checkifEqual("GetFixtureGUID linkedUuid ", linkedUUID, resultUUID);

		//--------------------------------------------------------------------------------
		// Read Attribute
		size_t countAttribute = 0;
		__checkVCOM(gdtfRead->GetAttributeCount(countAttribute));
		this->checkifEqual("GetWheelSlot1Wheel1ColorFY ",countAttribute, size_t(2));

		IGdtfAttributePtr attribute1;
		__checkVCOM(gdtfRead->GetAttributeAt(0, &attribute1));
		this->CheckAttibute(attribute1, true);


		IGdtfAttributePtr attribute2;
		__checkVCOM(gdtfRead->GetAttributeAt(1, &attribute2));
		this->CheckAttibute(attribute2, false);

		//--------------------------------------------------------------------------------
		// Read Wheels
		size_t countWheels = 0;
		__checkVCOM(gdtfRead->GetWheelCount(countWheels));
		{
			// Wheels loop
			for (size_t i = 0; i < countWheels; i++)
			{
				IGdtfWheelPtr gdtfWheel;
				if (__checkVCOM(gdtfRead->GetWheelAt(i, &gdtfWheel)))
				{
					MvrString wheelName = gdtfWheel->GetName();
					this->checkifEqual("GetGdtfWheelName ", wheelName, "My Wheel1");

					// WheelSlot loop
					size_t countSlots = 0;
					__checkVCOM(gdtfWheel->GetWheelSlotCount(countSlots));
					for (size_t j = 0; j < countSlots; j++)
					{
						IGdtfWheelSlotPtr gdtfSlot;
						__checkVCOM(gdtfWheel->GetWheelSlotAt(j, &gdtfSlot));

						MvrString slotName = gdtfSlot->GetName();
						this->checkifEqual("GetGdtfSlotName ", slotName, "My WheelSlot1Wheel1");

						CieColor color;
						color.fx = 0;
						color.fy = 0;
						color.f_Y = 0;
						__checkVCOM(gdtfSlot->GetColor(color));
						this->checkifEqual("GetWheelSlot1Wheel1ColorFx ",color.fx, 0.500000);
						this->checkifEqual("GetWheelSlot1Wheel1ColorFy ",color.fy, 0.424242);
						this->checkifEqual("GetWheelSlot1Wheel1ColorFY ",color.f_Y, 1.000000);

						// Wheel Image
						this->checkifEqual("GetGdtfSlotName ", gdtfSlot->GetGobo(), "MWheel_Img1");

						MvrString goboImage = gdtfSlot->GetGoboFileFullPath();
						this->checkifTrue("Gobo Image exists", UnitTestUtil::FileExists(goboImage));

						// Check Filter Link
						IGdtfFilterPtr gdtfLinkedFilter;
						__checkVCOM(gdtfSlot->GetFilter(&gdtfLinkedFilter));
						if(gdtfLinkedFilter)
						{
							checkifEqual("Linked Filter Name", gdtfLinkedFilter->GetName(), "My Filter");
						}

						// PrismFacets loop
						size_t prismFacetCount = 0;
						__checkVCOM(gdtfSlot->GetPrismFacetCount(prismFacetCount));
						for (size_t k = 0; k < prismFacetCount; k++)
						{
							IGdtfWheelSlotPrismFacetPtr prismFacet;
							if (__checkVCOM(gdtfSlot->GetPrismFacetAt(k, &prismFacet)))
							{
								CieColor color;
								color.fx = 0;
								color.fy = 0;
								color.f_Y = 0;
								__checkVCOM(prismFacet->GetColor(color));
								this->checkifEqual("GetWheelSlotPrismFacetColorFx ",color.fx, 0.424242);
								this->checkifEqual("GetWheelSlotPrismFacetColorFy ",color.fy, 1.000000);
								this->checkifEqual("GetWheelSlotPrismFacetColorFY ",color.f_Y, 0.500000);

								// no "ox, oy, oz" entries here
								STransformMatrix matrix;
								__checkVCOM(prismFacet->GetTransformMatrix(matrix));
								this->checkifEqual("GetTransformMatrix.ux ", matrix.ux, double(1));
								this->checkifEqual("GetTransformMatrix.uy ", matrix.uy, double(2));
								this->checkifEqual("GetTransformMatrix.uz ", matrix.uz, double(3));

								this->checkifEqual("GetTransformMatrix.vx ", matrix.vx, double(4));
								this->checkifEqual("GetTransformMatrix.vy ", matrix.vy, double(5));
								this->checkifEqual("GetTransformMatrix.vz ", matrix.vz, double(6));

								this->checkifEqual("GetTransformMatrix.wx ", matrix.wx, double(7));
								this->checkifEqual("GetTransformMatrix.wy ", matrix.wy, double(8));
								this->checkifEqual("GetTransformMatrix.wz ", matrix.wz, double(9));
							}
						} // PrismFacets loop

						//Animation System
						IGdtfWheelSlotAnimationSystemPtr gdtfAnimationSystem;
						if(__checkVCOM(gdtfSlot->GetAnimationSystem(&gdtfAnimationSystem)))
						{
							double p1_X = 0.0;
							double p1_Y = 0.0;
							double p2_X = 0.0;
							double p2_Y = 0.0;
							double p3_X = 0.0;
							double p3_Y = 0.0;
							__checkVCOM(gdtfAnimationSystem->GetP1_X(p1_X));
							__checkVCOM(gdtfAnimationSystem->GetP1_Y(p1_Y));
							__checkVCOM(gdtfAnimationSystem->GetP2_X(p2_X));
							__checkVCOM(gdtfAnimationSystem->GetP2_Y(p2_Y));
							__checkVCOM(gdtfAnimationSystem->GetP3_X(p3_X));
							__checkVCOM(gdtfAnimationSystem->GetP3_Y(p3_Y));
							this->checkifEqual("GetWheelSlotAnimationSystemP1_X ", p1_X, 1.0);
							this->checkifEqual("GetWheelSlotAnimationSystemP1_Y ", p1_Y, 1.5);
							this->checkifEqual("GetWheelSlotAnimationSystemP2_X ", p2_X, 2.0);
							this->checkifEqual("GetWheelSlotAnimationSystemP2_Y ", p2_Y, 2.5);
							this->checkifEqual("GetWheelSlotAnimationSystemP3_X ", p3_X, 3.0);
							this->checkifEqual("GetWheelSlotAnimationSystemP3_Y ", p3_Y, 3.5);

							double radius = 0.0;
							__checkVCOM(gdtfAnimationSystem->GetRadius(radius));
							this->checkifEqual("GetWheelSlotAnimationSystemRadius ", radius, 4.0);

						}

					} // WheelSlot loop
				}
			} // Wheels loop
		}

		
		//------------------------------------------------------------------------------    
		// Read Emitters
		size_t emitterCount = 0;
		__checkVCOM(gdtfRead->GetEmitterCount(emitterCount));
		for (size_t i = 0; i < emitterCount; i++)
		{
			IGdtfPhysicalEmitterPtr gdtfEmitter;
			if (__checkVCOM(gdtfRead->GetEmitterAt(i, &gdtfEmitter)))
			{
				MvrString emitterName = gdtfEmitter->GetName();
				this->checkifEqual("gdtfEmitterGetName ", emitterName, "My emitterName");

                double emitterWave; gdtfEmitter->GetDominantWaveLength(emitterWave);
                this->checkifEqual("Emitter DominantWaveLength", emitterWave, 66.6);

                MvrString emitterDiodePart = gdtfEmitter->GetDiodePart();
                this->checkifEqual("Emitter DiodePart", emitterDiodePart, "MyDiodePart");

				CieColor color;
				color.fx = 0;
				color.fy = 0;
				color.f_Y = 0;
				gdtfEmitter->GetColor(color);
				this->checkifEqual("gdtfEmitterColorFx ", color.fx, 1.0);
				this->checkifEqual("gdtfEmitterColorFy ", color.fy, 0.5);
				this->checkifEqual("gdtfEmitterColorFY ", color.f_Y, 0.424242);

				size_t measurementsCount = 0;
				__checkVCOM(gdtfEmitter->GetMeasurementCount(measurementsCount));  // XXX TODO: check the count here!
				for (size_t j = 0; j < measurementsCount; j++)
				{
					IGdtfMeasurementPtr emitterMeasurement;
					if (__checkVCOM(gdtfEmitter->GetMeasurementAt(j, &emitterMeasurement)))
					{
                        double physical=0; __checkVCOM( emitterMeasurement->GetPhysical(physical));
                        this->checkifEqual("Physical",         physical, 1.23);

                        double luminousIntensity=0; __checkVCOM(emitterMeasurement->GetLuminousIntensity(luminousIntensity));
                        this->checkifEqual("LuminousIntensity",   luminousIntensity, 2.34);

                        double transmission=0; __checkVCOM(emitterMeasurement->GetTransmission(transmission));
                        this->checkifEqual("Transmission is not allowed to be set",  transmission, 0.0);

                        EGdtfInterpolationTo interpolationTo = EGdtfInterpolationTo::Linear; __checkVCOM(emitterMeasurement->GetInterpolationTo(interpolationTo));
                        this->checkifEqual("InterpolationTo",  size_t(interpolationTo), size_t(EGdtfInterpolationTo::Log) );

                        //-----------------------------------------------------------------------------
                        // MeasurementPoint
                        size_t mpCount; __checkVCOM(emitterMeasurement->GetMeasurementPointCount(mpCount));
                        this->checkifEqual("MeasurementPoint Count", mpCount, size_t(1));
                        
                        IGdtfMeasurementPointPtr gdtfMeasurPoint;
                        
                        __checkVCOM(emitterMeasurement->GetMeasurementPointAt(0, &gdtfMeasurPoint));               
                        
						double waveLength_Val = 0;
						__checkVCOM(gdtfMeasurPoint->GetWaveLength(waveLength_Val));
						this->checkifEqual("GetWaveLength ", waveLength_Val, double(2.34));		// only for object valid, because of hardcoded wavelength and energy

						double energy_Val = 0;
						__checkVCOM(gdtfMeasurPoint->GetEnergy(energy_Val));
						this->checkifEqual("GetEnergy ", energy_Val, double(1.23));				// only for object valid, because of hardcoded wavelength and energy
					}
				} // measurements loop
			}
		} // emitter loop


        //------------------------------------------------------------------------------------------------------------------
        // Filters        
        size_t filterCount; __checkVCOM(gdtfRead->GetFilterCount(filterCount));
        
        this->checkifEqual("Filter Count", filterCount, size_t(1));

        IGdtfFilterPtr gdtfFilter; __checkVCOM(gdtfRead->GetFilterAt(0, &gdtfFilter));

        MvrString filterNam = gdtfFilter->GetName();
        this->checkifEqual("Filter Name", filterNam, "My Filter");
                
        CieColor filterColor;  filterColor.fx = 0; filterColor.fy = 0; filterColor.f_Y = 0;
        __checkVCOM(gdtfFilter->GetColor(filterColor));
        
        CieColor filterColorCompare; 
		filterColorCompare.fx	= 0.1;
		filterColorCompare.fy	= 0.2;
		filterColorCompare.f_Y	= 0.3;

        this->checkifEqual("Filter Color", filterColor, filterColorCompare);


        // Filter.Measurements
        // (The Meaurement attributes are check in the Emitter test.)
        size_t measruementCount; __checkVCOM(gdtfFilter->GetMeasurementCount(measruementCount));
        this->checkifEqual(" Filter.Measurements Count", measruementCount, size_t(3) );

		//------------------------------------------------------------------------------------------------------------------
		// Set ColorSpace Space
		IGdtfColorSpacePtr colorSpace;
		__checkVCOM(gdtfRead->GetColorSpace( & colorSpace));

		EGdtfColorSpace thisSpace = EGdtfColorSpace::sRGB;
		__checkVCOM(colorSpace->GetColorSpace(thisSpace));

		checkifEqual("ColorSpace", (size_t)thisSpace, (size_t)EGdtfColorSpace::ANSI);

		CieColor ansiColor_Red;		ansiColor_Red.fx   = 0.7347; 	ansiColor_Red.fy   = 0.2653;	ansiColor_Red.f_Y   = 100;
		CieColor ansiColor_Green;	ansiColor_Green.fx = 0.1596;	ansiColor_Green.fy = 0.8404; 	ansiColor_Green.f_Y = 100;
		CieColor ansiColor_Blue;	ansiColor_Blue.fx  = 0.0366; 	ansiColor_Blue.fy  = 0.001; 	ansiColor_Blue.f_Y  = 100;
		CieColor ansiColor_White;	ansiColor_White.fx = 0.4254; 	ansiColor_White.fy = 0.4044;	ansiColor_White.f_Y = 100;

		CieColor gdtfColor_Red;
		__checkVCOM(colorSpace->GetRed(gdtfColor_Red));

		CieColor gdtfColor_Green;
		__checkVCOM(colorSpace->GetGreen(gdtfColor_Green));

		CieColor gdtfColor_Blue;
		__checkVCOM(colorSpace->GetBlue(gdtfColor_Blue));

		CieColor gdtfColor_White;
		__checkVCOM(colorSpace->GetWhite(gdtfColor_White));

		checkifEqual("ANSI Color Red", 		ansiColor_Red, 		gdtfColor_Red);
		checkifEqual("ANSI Color Green", 	ansiColor_Green, 	gdtfColor_Green);
		checkifEqual("ANSI Color Blue", 	ansiColor_Blue, 	gdtfColor_Blue);
		checkifEqual("ANSI Color White", 	ansiColor_White,	gdtfColor_White);
		

		//------------------------------------------------------------------------------    
		// Fill with DMX
		size_t dmxModesCount = 0;
		__checkVCOM(gdtfRead->GetDmxModeCount(dmxModesCount));
		for (size_t i = 0; i < dmxModesCount; i++)
		{
			IGdtfDmxModePtr gdtfDmxMode;
			if (__checkVCOM(gdtfRead->GetDmxModeAt(i, &gdtfDmxMode)))
			{
				// Set the name
				MvrString dmxModeName = gdtfDmxMode->GetName();
				this->checkifEqual("gdtfDmxModeGetName ", dmxModeName, "My DmxModeName");

				// Set the Geomytry
				IGdtfGeometryPtr gdtfGeometry;
				if (__checkVCOM(gdtfDmxMode->GetGeometry(&gdtfGeometry)))
				{
					MvrString dmxModeGeometry = gdtfGeometry->GetName();
					this->checkifEqual("dmxModeGeometryGetName ", dmxModeGeometry, "My nameGeometry");
				}

				//------------------------------------------------------------------------------ 
				// Add the Dmx Channels
				size_t countDmxChannels = 0;
				__checkVCOM(gdtfDmxMode->GetDmxChannelCount(countDmxChannels));
				for (size_t i = 0; i < countDmxChannels; i++)
				{
					IGdtfDmxChannelPtr gdtfDmxChannel;
					__checkVCOM(gdtfDmxMode->GetDmxChannelAt(i, &gdtfDmxChannel));

					// Set the name
					MvrString dmxChannelName = gdtfDmxChannel->GetName();
					this->checkifEqual("gdtfDmxChannelGetName ", dmxChannelName, "My nameGeometry_My attributeName");

					// Set the geometry
					IGdtfGeometryPtr	geometryPtr;
					if (__checkVCOM(gdtfDmxChannel->GetGeometry(&geometryPtr)))
					{
						MvrString geometryName = geometryPtr->GetName();
						this->checkifEqual("geometryPtrGetName ", geometryName, "My nameGeometry");
					}

					// Coarse
					Sint32 coarse;
					__checkVCOM(gdtfDmxChannel->GetCoarse(coarse));
					this->checkifEqual("gdtfDmxChannelGetCoarse ", coarse, 1);

					// Fine
					Sint32 fine;
					__checkVCOM(gdtfDmxChannel->GetFine(fine));
					this->checkifEqual("gdtfDmxChannelGetFine ", fine, 2);

					// Ultra
					Sint32 ultra;
					__checkVCOM(gdtfDmxChannel->GetUltra(ultra));
					this->checkifEqual("gdtfDmxChannelGetUltra ", ultra, 3);

					// Uber
					Sint32 uber;
					__checkVCOM(gdtfDmxChannel->GetUber(uber));
					this->checkifEqual("gdtfDmxChannelGetUber ", uber, 4);

					// Default Value
					GdtfDefines::DmxValue def;
					__checkVCOM(gdtfDmxChannel->GetDefaultValue(def));
					this->checkifEqual("gdtfDmxChannelGetDefaultValue ", def, GdtfDefines::DmxValue(5));

					// Highlight
					GdtfDefines::DmxValue highlight;
					__checkVCOM(gdtfDmxChannel->GetHighlight(highlight));
					this->checkifEqual("gdtfDmxChannelGetHighlight ", highlight, GdtfDefines::DmxValue(6));

					bool hasHighlight = false;
					__checkVCOM(gdtfDmxChannel->HasHighlight(hasHighlight));
					this->checkifEqual("gdtfDmxChannelHasHighlight ", hasHighlight, 1);

					// DMX Break
					Sint32 breakId;
					__checkVCOM(gdtfDmxChannel->GetDmxBreak(breakId));
					this->checkifEqual("gdtfDmxChannelGetDmxBreak ", breakId, 7);

					//------------------------------------------------------------------------------    
					// Add the Logical Channels
					size_t countLogicalChannels = 0;
					__checkVCOM(gdtfDmxChannel->GetLogicalChannelCount(countLogicalChannels));
					for (size_t j = 0; j < countLogicalChannels; j++)
					{
						IGdtfDmxLogicalChannelPtr gdtfLogicalChannel;
						__checkVCOM(gdtfDmxChannel->GetLogicalChannelAt(j, &gdtfLogicalChannel));

						IGdtfDmxChannelPtr parentChannel;
						__checkVCOM(gdtfLogicalChannel->GetParentDmxChannel( & parentChannel));
						{
							this->checkifEqual("Test Get Parent Channel", parentChannel->GetName(), gdtfDmxChannel->GetName());
						}

						// Set the name
						MvrString logicalChannelName = gdtfLogicalChannel->GetName();
						this->checkifEqual("gdtfLogicalChannelGetName ", logicalChannelName, "My attributeName");

						// Attribute
						IGdtfAttributePtr gdtfAttribute;
						if (__checkVCOM(gdtfLogicalChannel->GetAttribute(&gdtfAttribute)))
						{
							MvrString logicalChannelName = gdtfAttribute->GetName();
							this->checkifEqual("gdtfAttributeGetName ", logicalChannelName, "My attributeName");
						}

						// DMX Snap
						EGdtfDmxSnap snap;
						__checkVCOM(gdtfLogicalChannel->GetDmxSnap(snap));
						this->checkifEqual("gdtfLogicalChannelGetDmxSnap ", snap, EGdtfDmxSnap::eGdtfDmxMaster_On);

						// DMX Master
						EGdtfDmxMaster master;
						__checkVCOM(gdtfLogicalChannel->GetDmxMaster(master));
						this->checkifEqual("gdtfLogicalChannelGetDmxMaster ", master, EGdtfDmxMaster::eGdtfDmxMaster_Grand);

					    // Move In Black Frames
					    double moveInBlack = 0;
					    __checkVCOM(gdtfLogicalChannel->GetMoveInBlackFrames(moveInBlack));
					    this->checkifEqual("gdtfDmxChannelGetMoveInBlackFrames ", moveInBlack, double(8) );

					    // DMX Change Time Limit
					    double change;
					    __checkVCOM(gdtfLogicalChannel->GetDmxChangeTimeLimit(change));
					    this->checkifEqual("gdtfDmxChannelGetDmxChangeTimeLimit ", change, double(9));

						//------------------------------------------------------------------------------    
						// Add the Features 
						size_t countFeatures = 0;
						__checkVCOM(gdtfLogicalChannel->GetDmxFunctionCount(countFeatures));
						for (size_t j = 0; j < countFeatures; j++)
						{
                            //------------------------------------------------------------------------------    
                            // ChannelFunction
							IGdtfDmxChannelFunctionPtr gdtfFunction;
							if (__checkVCOM(gdtfLogicalChannel->GetDmxFunctionAt(j, &gdtfFunction)))
							{
								IGdtfDmxLogicalChannelPtr parentLogicalChannel;
								__checkVCOM(gdtfFunction->GetParentLogicalChannel( & parentLogicalChannel));
								{
									this->checkifEqual("Test Get Parent Logical Channel", parentLogicalChannel->GetName(), gdtfLogicalChannel->GetName());
								}

								// Set the name
								MvrString featureName = gdtfFunction->GetName();
								this->checkifEqual("gdtfFunctionGetName ", featureName, "My nameDmxFunction");

								// Attribute
								IGdtfAttributePtr gdtfAttribute;
								if (__checkVCOM(gdtfFunction->GetAttribute(&gdtfAttribute)))
								{
									MvrString attributeName = gdtfAttribute->GetName();
									this->checkifEqual("gdtfAttributeGetName ", attributeName, "My attributeName");
								}

								// Wheel
								IGdtfWheelPtr gdtfWheel;
								if (__checkVCOM(gdtfFunction->GetOnWheel(&gdtfWheel)))
								{
									MvrString wheelName = gdtfWheel->GetName();
									this->checkifEqual("gdtfWheelGetName ", wheelName, "My Wheel1");
								}

								// Emitter
								IGdtfPhysicalEmitterPtr gdtfEmitter;
								if (__checkVCOM(gdtfFunction->GetEmitter(&gdtfEmitter)))
								{
									MvrString emitterName = gdtfEmitter->GetName();
									this->checkifEqual("gdtfEmitterGetName ", emitterName, "My emitterName");
								}

								//OriginalAttribute
								MvrString ogAttribute = gdtfFunction->GetOriginalAttribute();
								this->checkifEqual("gdtfFunctionGetOriginalAttribute ", ogAttribute, "My orginalAttribute");

								//Start Address
								GdtfDefines::DmxValue dmxStartAddress;
								__checkVCOM(gdtfFunction->GetStartAddress(dmxStartAddress));
								this->checkifEqual("gdtfFunctionGetStartAddress ", dmxStartAddress, GdtfDefines::DmxValue(0));

								//physical Start
								double physicalStart;
								__checkVCOM(gdtfFunction->GetPhysicalStart(physicalStart));
								this->checkifEqual("gdtfFunctionGetPhysicalStart ", physicalStart, double(2));

								//physical End
								double physicalEnd;
								__checkVCOM(gdtfFunction->GetPhysicalEnd(physicalEnd));
								this->checkifEqual("gdtfFunctionGetPhysicalEnd ", physicalEnd, double(3));

								//real Fade
								double realFade;
								__checkVCOM(gdtfFunction->GetRealFade(realFade));
								this->checkifEqual("gdtfFunctionGetRealFade ", realFade, double(4));

								//real Acceleration
								double realAcc;
								__checkVCOM(gdtfFunction->GetRealAcceleration(realAcc));
								this->checkifEqual("gdtfFunctionGetRealAcceleration ", realAcc, double(5));

                                // Check the Linked Filter
                                IGdtfFilterPtr filter;
                                __checkVCOM(gdtfFunction->GetFilter(&filter) );
                                this->checkifEqual("Filter Name", filter->GetName() ,"My Filter");
								//------------------------------------------------------------------------------    
								// Add the ChannelSets 
								size_t countChannelSets = 0;
								__checkVCOM(gdtfFunction->GetDmxChannelSetCount(countChannelSets));

								std::vector<IGdtfDmxChannelSetPtr> gdtfChannelSets;
								for (size_t j = 0; j < countChannelSets; j++)
								{
									IGdtfDmxChannelSetPtr gdtfChannelSet;
									__checkVCOM(gdtfFunction->GetDmxChannelSetAt(j, &gdtfChannelSet));

									std::string channelSetName = gdtfChannelSet->GetName();
									if (!channelSetName.empty()) { gdtfChannelSets.push_back(gdtfChannelSet); }
								}

								for (size_t j = 0; j < gdtfChannelSets.size(); j++)
								{
									IGdtfDmxChannelSetPtr gdtfChannelSet = gdtfChannelSets[j];

									// Set the name
									MvrString channelSetName = gdtfChannelSet->GetName();
									this->checkifEqual("gdtfChannelSetGetName ", channelSetName, "My nameDmxChannelSet");

									GdtfDefines::DmxValue startAddr;
									__checkVCOM(gdtfChannelSet->GetDmxStartAddress(startAddr));
									this->checkifEqual("gdtfChannelSetGetDmxStartAddress ", startAddr, (GdtfDefines::DmxValue)1);

									GdtfDefines::DmxValue endAddr;
									__checkVCOM(gdtfChannelSet->GetDmxEndAddress(endAddr));
									this->checkifEqual("gdtfChannelSetGetDmxEndAddress ", endAddr, (GdtfDefines::DmxValue)2);

									double physicalStart;
									__checkVCOM(gdtfChannelSet->GetPhysicalStart(physicalStart));
									this->checkifEqual("gdtfChannelSetGetPhysicalStart ", physicalStart, double(10));

									double physicalEnd;
									__checkVCOM(gdtfChannelSet->GetPhysicalEnd(physicalEnd));
									this->checkifEqual("gdtfChannelSetGetPhysicalEnd ", physicalEnd, double(20));

									bool isSet = false;
									__checkVCOM(gdtfChannelSet->GetUsePhysicalFromParent(isSet));
									this->checkifEqual("gdtfChannelSetGetUsePhysicalFromParent ", isSet, 0);

									Sint32 wheelSlotIndex;
									__checkVCOM(gdtfChannelSet->GetWheelSlot(wheelSlotIndex));
									this->checkifEqual("gdtfChannelSetGetWheelSlot ", wheelSlotIndex, 11);
								}
							}
						}
					}
				}


				//------------------------------------------------------------------------------ 
				// Add the Dmx Relations
				size_t countRelations = 0;
				__checkVCOM(gdtfDmxMode->GetDmxRelationCount(countRelations));
				for (size_t i = 0; i < countRelations; i++)
				{
					IGdtfDmxRelationPtr gdtfRelation;
					__checkVCOM(gdtfDmxMode->GetDmxRelationAt(i, &gdtfRelation));

					// Set the name
					MvrString dmxRelationName = gdtfRelation->GetName();
					this->checkifEqual("gdtfRelationGetName ", dmxRelationName, "My Relation");

					// Get Master Channel
					IGdtfDmxChannelPtr	master;
					MvrString	masterStr;
					if (__checkVCOM(gdtfRelation->GetMasterChannel(&master)))
					{
						masterStr = master->GetName();
					}

					// Get Slave ChannelFunction
					IGdtfDmxChannelFunctionPtr slave;
					MvrString                slaveStr;
					if (__checkVCOM(gdtfRelation->GetSlaveChannel(&slave)))
					{
						slaveStr = slave->GetName();
					}
					
					// Relation Type
					EGdtfDmxRelationType rel;
					__checkVCOM(gdtfRelation->GetRelationType(rel));
					this->checkifEqual("gdtfRelationGetRelationType ", rel, EGdtfDmxRelationType::eGdtfDmxRelationType_Multiply);
					
				}

				//------------------------------------------------------------------------------ 
				// Add the Macro
				size_t countMacro = 0;
				__checkVCOM(gdtfDmxMode->GetDmxMacroCount(countMacro));
				for (size_t i = 0; i < countMacro; i++)
				{
					IGdtfMacroPtr gdtfmacro;
					__checkVCOM(gdtfDmxMode->GetDmxMacroAt(i, &gdtfmacro));

					// Set the name
					MvrString dmxMacroName = gdtfmacro->GetName();
					this->checkifEqual("gdtfMacroGetName ", dmxMacroName, "My Macro");

					// TODO Add MacroDMX MacroVisual
				}

			}
		}


		//------------------------------------------------------------------------------    
		// Fill Activation Groups Section
		size_t countActivationsGroups = 0;
		__checkVCOM(gdtfRead->GetActivationGroupCount(countActivationsGroups));
		for (size_t i = 0; i < countActivationsGroups; i++)
		{
			IGdtfActivationGroupPtr gdtfActivationGroups;
			if (__checkVCOM(gdtfRead->GetActivationGroupAt(i, &gdtfActivationGroups)))
			{
				// Set the name
				MvrString activationGroupName = gdtfActivationGroups->GetName();
				this->checkifEqual("gdtfActivationGroupsGetName ", activationGroupName, "My actGroupName");

				//------------------------------------------------------------------------------ 
				// Add the Attributes
				size_t countMainAttributes = 0;
				__checkVCOM(gdtfActivationGroups->GetAttributeCount(countMainAttributes));
				this->checkifEqual("Check Count Attributes", countMainAttributes, size_t(2));

				// Check Main Attribute
				IGdtfAttributePtr	gdtfMainAttribute;
				__checkVCOM(gdtfActivationGroups->GetAttributeAt(0, &gdtfMainAttribute));
				this->checkifEqual("gdtfMainAttribute GetName()", gdtfMainAttribute->GetName(), "My MainAttributeName");

				double lyLinkTest = 0;
				gdtfMainAttribute->BindToObject( & lyLinkTest);


				// Check Slave Attribute
				IGdtfAttributePtr	gdtfSlaveAttribute;
				__checkVCOM(gdtfActivationGroups->GetAttributeAt(1, &gdtfSlaveAttribute));
				this->checkifEqual("gdtfSlaveAttribute GetName() ", gdtfSlaveAttribute->GetPrettyName()	, "My attributePrettyName");

				IGdtfAttributePtr linkedAttribute;
				if(__checkVCOM(gdtfSlaveAttribute->GetMainAttribute(&linkedAttribute)))
				{
					this->checkifEqual("Name Main Attribute", linkedAttribute->GetName() , "My MainAttributeName");

					this->checkifEqualPtr("Check Bind Behavoir", linkedAttribute->GetBoundObject(), (void*)&lyLinkTest );
				}
			}
		} // ActivationsGroups loop


		//------------------------------------------------------------------------------    
		// Fill Feature Groups
		size_t acountFeatureGroups = 0;
		__checkVCOM(gdtfRead->GetFeatureGroupCount(acountFeatureGroups));
		for (size_t i = 0; i < acountFeatureGroups; i++)
		{
			IGdtfFeatureGroupPtr gdtfFeatureGroup;
			if (__checkVCOM(gdtfRead->GetFeatureGroupAt(i, &gdtfFeatureGroup)))
			{
				MvrString featureGroupName	= gdtfFeatureGroup->GetName();
				MvrString prettyName		= gdtfFeatureGroup->GetPrettyName();
				this->checkifEqual("gdtfFeatureGroupGetName "		, featureGroupName	, "My featureGroupName");
				this->checkifEqual("gdtfFeatureGroupGetPrettyName "	, prettyName		, "My featureGroupPrettyName");

				//------------------------------------------------------------------------------ 
				// Add the Features
				size_t countFeatures = 0;
				__checkVCOM(gdtfFeatureGroup->GetFeatureCount(countFeatures));
				for (size_t i = 0; i < countFeatures; i++)
				{
					IGdtfFeaturePtr gdtfFeature;
					__checkVCOM(gdtfFeatureGroup->GetFeatureAt(i, &gdtfFeature));

					// Set the name
					MvrString featureName = gdtfFeature->GetName();
					this->checkifEqual("gdtfFeatureGetName ", featureName, "My featureName");
				}
			}
		} // FeatureGroups loops

		//------------------------------------------------------------------------------    
		// Check Attributes
		size_t countAttributes = 0;
		__checkVCOM(gdtfRead->GetAttributeCount(countAttributes));
		this->checkifEqual("Check Attribute Count ", (size_t) 2, countAttributes);

		for(size_t i = 0; i < countAttributes; i++)
		{
			if (countAttributes == 0)
			{
				IGdtfAttributePtr attribute;
				__checkVCOM(gdtfRead->GetAttributeAt(i, &attribute));

				EGdtfPhysicalUnit unit;
				__checkVCOM(attribute->GetPhysicalUnit(unit));
				this->checkifEqual("Check Physical Unit ", (Sint32)unit, (Sint32)EGdtfPhysicalUnit::Acceleration);
				this->checkifEqual("Check Attribute Name ", "My MainAttributeName", attribute->GetName());
			}

			if (countAttributes == 1)
			{
				IGdtfAttributePtr attribute;
				__checkVCOM(gdtfRead->GetAttributeAt(i, &attribute));

				EGdtfPhysicalUnit unit;
				__checkVCOM(attribute->GetPhysicalUnit(unit));
				this->checkifEqual("Check Physical Unit ", (Sint32)unit, (Sint32)EGdtfPhysicalUnit::Angle);
				this->checkifEqual("Check Attribute Name ", "My attributeName", attribute->GetName());
			}
		}

		//------------------------------------------------------------------------------    
		// Extract Geometry & Models
		size_t countModels = 0;
		__checkVCOM(gdtfRead->GetModelCount(countModels));
		for (size_t i = 0; i < countModels; i++)
		{
			IGdtfModelPtr gdtfModel;
			if (__checkVCOM(gdtfRead->GetModelAt(i, &gdtfModel)))
			{
				MvrString  modelName	= gdtfModel->GetName();
				MvrString geometryFile	= gdtfModel->GetGeometryFileName();
				this->checkifEqual("gdtfModelGetName "				, modelName		, "My modelName");
				this->checkifEqual("gdtfModelGet3DSGeometryFile "	, geometryFile	, "MyModel");

				MvrString fullPath_3ds = gdtfModel->GetGeometryFile_3DS_FullPath();
				this->checkifTrue("Model 3DS exists.", UnitTestUtil::FileExists(fullPath_3ds));

				MvrString fullPath_svg = gdtfModel->GetGeometryFile_SVG_FullPath();
				this->checkifTrue("Model SVG exists", UnitTestUtil::FileExists(fullPath_svg));

				// Height
				double heightVal = 0.0;
				__checkVCOM(gdtfModel->GetHeight(heightVal));
				this->checkifEqual("gdtfModelGetHeight ", heightVal, double(10));

				// Width
				double widthVal = 0.0;
				__checkVCOM(gdtfModel->GetWidth(widthVal));
				this->checkifEqual("gdtfModelGetWidth ", widthVal, double(20));

				// Length
				double lengthVal = 0.0;
				__checkVCOM(gdtfModel->GetLength(lengthVal));
				this->checkifEqual("gdtfModelGetLength ", lengthVal, double(30));

				// PrimitiveType
				EGdtfModel_PrimitiveType primitiveType = EGdtfModel_PrimitiveType::eGdtfModel_PrimitiveType_Undefined;
				__checkVCOM(gdtfModel->GetPrimitiveType(primitiveType));
				this->checkifEqual("gdtfModelGetPrimitiveType ", primitiveType, EGdtfModel_PrimitiveType::eGdtfModel_PrimitiveType_Sphere);
			}
		} // Models loop


		//--------------------------------------------------------------------------------
		// Geometry Section
		size_t countGeo = 0;
		__checkVCOM(gdtfRead->GetGeometryCount(countGeo));
		this->checkifEqual("Geometry Count ", countGeo, size_t(4));

		IGdtfGeometryPtr geo1;
		__checkVCOM(gdtfRead->GetGeometryAt(0, &geo1));

		IGdtfGeometryPtr geo2;
		__checkVCOM(gdtfRead->GetGeometryAt(1, &geo2));

		IGdtfGeometryPtr geo3;
		__checkVCOM(gdtfRead->GetGeometryAt(2, &geo3));

		if(geo1 && geo2)
		{
			IGdtfGeometryPtr refedGeo;
			if(__checkVCOM(geo2->GetGeometryReference(&refedGeo)))
			{
				this->checkifEqual("Geo Link ", geo1->GetName(), refedGeo->GetName());
			}			
		}

		if(geo3)
		{
			IGdtfGeometryPtr refedGeo;
			if(__checkVCOM(geo3->GetGeometryReference(&refedGeo)))
			{
				this->checkifEqual("Geo Link Inner", "My Inner Geo", refedGeo->GetName());
			}

			size_t breakCount = 0;
			__checkVCOM(geo3->GetBreakCount(breakCount));

			this->checkifEqual("Get Break Count", (size_t)1 , breakCount);

			IGdtfBreakPtr gdtfBreak;
			__checkVCOM(geo3->GetBreakAt(0, & gdtfBreak));

			DMXAddress adress = 0;
			__checkVCOM(gdtfBreak->GetDmxAddress(adress));
			this->checkifEqual("Check Adress", (DMXAddress)4,adress);

			Sint32 breakId = 0;
			__checkVCOM(gdtfBreak->GetDmxBreak(breakId));
			this->checkifEqual("Check Adress", (Sint32)3,breakId);
		}

		//--------------------------------------------------------------------------------
		// Read Revision
		size_t countRevs = 0;
		__checkVCOM(gdtfRead->GetRevisionCount(countRevs));
		this->checkifEqual("Revision Count ", countRevs, size_t(1));

		IGdtfRevisionPtr rev;
		__checkVCOM(gdtfRead->GetRevisionAt(0, &rev));

		STime expTimestamp;
		__checkVCOM(rev->GetDate(expTimestamp));

		size_t userId = 0;
		__checkVCOM(rev->GetUserId(userId));

		this->checkifEqual("Check RevText", rev->GetText(), "Revision TestText");
		this->checkifEqual("Check RevDatefYear",	expTimestamp.fYear, 	Uint16(2020));
		this->checkifEqual("Check RevDatefMonth",	expTimestamp.fMonth, 	Uint16(12));
		this->checkifEqual("Check RevDatefDay",		expTimestamp.fDay, 		Uint16(2));
		this->checkifEqual("Check RevDatefHour",	expTimestamp.fHour, 	Uint16(22));
		this->checkifEqual("Check RevDatefMinute",	expTimestamp.fMinute,	Uint16(33));
		this->checkifEqual("Check RevDatefSecond",	expTimestamp.fSecond, 	Uint16(44));
		this->checkifEqual("Check UserId",			userId, 				size_t(254));


		

        //------------------------------------------------------------------------------    
        // Read RDM         
        IGdtfTRDMPtr rdm;
        __checkVCOM (gdtfRead->GetRDM(&rdm));
        
        size_t devModID = 0;
        __checkVCOM (rdm->GetDeviceModelID(devModID));
        this->checkifEqual("Check DeviceModelID", devModID, size_t(1));

        size_t manID = 0;
        __checkVCOM (rdm->GetManufacturerID(manID));
        this->checkifEqual("Check ManufacturerID", manID, size_t(2));
        
        //------------------------------------------------------------------------------    
        // Read SoftwareVersionID
        size_t softIdCount;
        __checkVCOM (rdm->GetSoftwareVersionIDCount(softIdCount));
        this->checkifEqual("SoftwareVersionID count", Sint32(softIdCount), Sint32(1));
                
        IGdtfSoftwareVersionIDPtr softID;
        rdm->GetSoftwareVersionIDAt(0, &softID);

        size_t softIDVal;
        __checkVCOM (softID->GetValue(softIDVal));
        this->checkifEqual("SoftwareVersionID Value", Sint32(softIDVal), Sint32(22));

        //------------------------------------------------------------------------------    
        // Read DMXPersonality
        size_t dmxPersCount;
        __checkVCOM (softID->GetDMXPersonalityCount(dmxPersCount) );
        this->checkifEqual("DMXPersonality count", Sint32(dmxPersCount), Sint32(1));

        IGdtfDMXPersonalityPtr dmxPerso;
        __checkVCOM (softID->GetDMXPersonalityAt(0, &dmxPerso));
        
        size_t dmxPersoVal;
        __checkVCOM (dmxPerso->GetValue(dmxPersoVal));
        this->checkifEqual("DMXPersonality Value", Sint32(dmxPersoVal), Sint32(11));
        
        IGdtfDmxModePtr dmxMode; dmxPerso->GetDmxMode(&dmxMode);
        this->checkifEqual("DMXPersonality.DMXModeName ", dmxMode->GetName(), "My DmxModeName");
}

	PrintParsingErrorList(gdtfRead);
}

std::string GdtfUnittest::GetTestPNG_ThumbNail(bool readLocation)
{
	std::string path;
	if(readLocation)	{ path = fAppDataFolder + kSeparator + "GdtfGroup" + kSeparator; }
	else 				{ path = fTestResourcesFolder + kSeparator; }
    path += "MyThumbnail.png";
    return path;
}

std::string GdtfUnittest::GetTestSVG_ThumbNail(bool readLocation)
{
	std::string path;
	if(readLocation)	{ path = fAppDataFolder + kSeparator + "GdtfGroup" + kSeparator; }
	else 				{ path = fTestResourcesFolder + kSeparator; }
    path += "MyThumbnail.svg";
    return path;
}

std::string GdtfUnittest::GetTestSVG_Model(bool readLocation)
{
	std::string path;
	if(readLocation)	{ path = fAppDataFolder + kSeparator + "GdtfGroup" + kSeparator+ "modelssvg" + kSeparator;; }
	else 				{ path = fTestResourcesFolder + kSeparator; }
    path += "MyModel.svg";
    return path;
}

std::string GdtfUnittest::GetTest3DS_Model(bool readLocation)
{
	std::string path;
	if(readLocation)	{ path = fAppDataFolder + kSeparator + "GdtfGroup" + kSeparator+ "models3ds" + kSeparator;; }
	else 				{ path = fTestResourcesFolder + kSeparator; }
	
    path += "MyModel.3ds";
    return path;
}

std::string GdtfUnittest::GetTestWheel_PNG(bool readLocation)
{
	std::string path;
	if(readLocation)	{ path = fAppDataFolder + kSeparator + "GdtfGroup" + kSeparator + "wheels" + kSeparator; }
	else 				{ path = fTestResourcesFolder + kSeparator; }
    path += "MWheel_Img1.png";
    return path;
}

void GdtfUnittest::CheckAttibute(VectorworksMVR::IGdtfAttributePtr attribute, bool hasColor)
{
	VectorworksMVR::CieColor color;
	if(hasColor)
	{
		__checkVCOM(attribute->GetColor(color));
	}
	else
	{
		__checkVCOM_NotSet(attribute->GetColor(color));
	}
}

void GdtfUnittest::CheckAttachedFiles(VectorworksMVR::IGdtfFixturePtr fixture, size_t at, std::string inFile)
{
	std::string file = fixture->GetImageRessourcesPathAt(at);

	this->checkifEqual("Filename for Attached File", file, inFile);

	
}