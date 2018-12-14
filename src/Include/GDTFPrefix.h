//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------

#ifndef __GDTFPREFIX
#define __GDTFPREFIX

namespace VectorworksMVR
{
	namespace GdtfDefines
	{
        // This is used for DMX Channel defining. So values from 1...512 will be stored
		typedef Uint16		DMXAddress; 
		
        // This is used for a DMX Value defining. GDTF currently supports of to 32bit values, so the maximum value will be 2^32 - 1
        // We always store this in a 64bit values, to make this more simple. 
        typedef Uint64		DmxValue;    
		
		enum EGdtfObjectType
		{
			eGdtfActivationGroup		= 0,
			eGdtfFeatureGroup			= 1,
			eGdtfFeature				= 2,
			eGdtfSubAttribute			= 3,
			eGdtfAttribute				= 4,
			eGdtfWheelSlot				= 5,
			eGdtfPrismFacet				= 6,
			eGdtfWheel					= 7,
			eGdtfModel					= 8,
			eGdtfGeometry				= 9,
			eGdtfGeometryAxis			= 10,
			eGdtfGeometryBeamFilter		= 11,
			eGdtfGeometryColorFilter	= 12,
			eGdtfGeometryGoboFilter		= 13,
			eGdtfGeometryShaperFilter	= 14,
			eGdtfGeometryLamp			= 15,
			eGdtfBreak					= 16,
			eGdtfGeometryReference		= 17,
			eGdtfDmxChannelSet			= 18,
			eGdtfDmxChannelFuntion		= 19,
			eGdtfDmxLogicalChannel		= 20,
			eGdtfDmxChannel				= 21,
			eGdtfDmxRelation			= 22,
			eGdtfDmxMode				= 23,
			eGdtfRevision				= 24,
			eGdtfUserPreset				= 25,
			eGdtfMacro					= 26,
			eGdtfMeasurementPoint		= 27,
			eGdtfPhysicalEmitter		= 28,
			eGdtfPhysicalDescription	= 29,
			eGdtfFixture				= 30,
            eGdtfDMXProfile             = 31,
            eGdtfCRIGroup               = 32,
            eGdtfCRI					= 33,
            eProtocols                  = 34,
            eGdtfFTRDM                  = 35,
            eGdtfRDMParameter           = 36,
            eGdtfRDMNotifications       = 37,
            eGdtfRDMNotification        = 38,
            eGdtfRDMParameterNotification               = 39,
            eGdtfRDMValueBool                           = 40,
            eGdtfRDMValue_UNSIGNED_BYTE                 = 42,
            eGdtfRDMValue_SIGNED_BYTE                   = 43,
            eGdtfRDMValue_UNSIGNED_WORD                 = 44,
            eGdtfRDMValue_SIGNED_WORD                   = 45,
            eGdtfRDMValue_UNSIGNED_DWORD                = 46,
            eGdtfRDMValue_SIGNED_DWORD                  = 47,
            eGdtfRDMValue_ASCII                         = 48,
            eGdtfRDMValue_DMX_PERSONALITY_DESCRIPTION   = 49,            
            eRDMValue_SENSOR_DEFINITION                 = 50,
            eGdtfRDMValue_SLOT_INFO                     = 51,
            eRDMValue_STATUS_ID_DESCRIPTION             = 52,
            eGdtfRDMValue_REAL_TIME_CLOCK               = 53,
            eGdtfRDMSensorNotification                  = 54,
            eGdtfValueSensor                            = 55,
            eGdtfArtNet                                 = 56,
            eGdtf_sACN                                  = 57,
            eGdtfKiNET                                  = 58,
            eGdtfPosiStageNet                           = 59,
            eGdtfOpenSoundControl                       = 60,
            eGdtfCITP                                   = 61,   
            eGdtfMacroDMX               = 62,
            eGdtfMacroDMXStep           = 63,
            eGdtfMacroDMXValue          = 64,
            eGdtfMacroVisual            = 65,  
            eGdtfMacroVisualStep        = 66,
            eGdtfMacroVisualValue       = 67,

		};

        enum class EGdtfParsingError
        {
            eWrongAttribute = 0,
        };
		
		enum class EGdtfPhysicalUnit
		{
			None			= 0,	// Default
			Percent			= 1,
			Length			= 2,	// Meter
			Mass			= 3,	// kg
			Time			= 4,	// s
			Temperatur		= 5,	// K
			LuminousItensity= 6,	//cd
			Angle			= 7,	//degree
			Force			= 8,	// Newton
			Frequeny		= 9,	// 1/s
			Current			= 10,	// A
			Voltage			= 12,	// V
			Power			= 13,	// W
			Energy			= 14,	// J
			Area			= 15,	//m^2
			Volume			= 16,	// m^3
			Speed			= 17,	// m/s
			Acceleration	= 18,	//m/s^2
			AngularSpeed	= 19,	// degree/s
			AngularAccc		= 20,	//degree/s^2
			WaveLength		= 21,	//nm
			ColorComponent	= 22
		};
		
		enum class EGdtfSpecial
		{
			None		= 0,			//Default
			Dimmer		= 1,
			Pan			= 2,
			Tilt		= 3,
			X			= 4,
			Y			= 5,
			Z			= 6,
			RGB			= 7,
			Hue			= 8,
			Saturation	= 9,
			Brightness	= 10,
			ColorWheel	= 11,
			Focus		= 12,
			Zoom		= 13,
			Dummy		= 14,
		};
		
		enum EGdtfModel_PrimitiveType
		{
			eGdtfModel_PrimitiveType_Undefined		= 0,
			eGdtfModel_PrimitiveType_Cube			= 1,
			eGdtfModel_PrimitiveType_Cylinder		= 2,
			eGdtfModel_PrimitiveType_Sphere			= 3,
			eGdtfModel_PrimitiveType_Base			= 4,
			eGdtfModel_PrimitiveType_Yoke			= 5,
			eGdtfModel_PrimitiveType_Head			= 6,
			eGdtfModel_PrimitiveType_Scanner		= 7,
			eGdtfModel_PrimitiveType_Conventional	= 8,
            eGdtfModel_PrimitiveType_Pigtail        = 9,
		};
		
		enum EGdtfLampType
		{
			eGdtfLampType_Dischange = 0,
			eGdtfLampType_Tungsten = 1,
			eGdtfLampType_Halogen = 2,
			eGdtfLampType_LED = 3,
		};
		
		enum EGdtfBeamType
		{
			eGdtfBeamType_Wash	= 0, // Default
			eGdtfBeamType_Spot  = 1,
			eGdtfBeamType_None  = 2,
		};
		
		enum EGdtfDmxFrequency
		{
			eGdtfDmxFrequency_30	= 0,
			eGdtfDmxFrequency_15	= 1,
			eGdtfDmxFrequency_60	= 2,
			eGdtfDmxFrequency_Slow1 = 3,
			eGdtfDmxFrequency_Slow2 = 4,
			eGdtfDmxFrequency_Slow3 = 5,
		};
		
		enum EGdtfDmxMaster
		{
			eGdtfDmxMaster_None		= 0,
			eGdtfDmxMaster_Grand	= 1,
			eGdtfDmxMaster_Group	= 2,
			
		};
		
		enum EGdtfDmxSnap
		{
			eGdtfDmxMaster_Yes  = 0,
			eGdtfDmxMaster_No   = 1,
			eGdtfDmxMaster_On   = 2,
			eGdtfDmxMaster_Off  = 3,
		};
		
		enum EGDTFEncoderInvert
		{
			eGDTFEncoderInvert_No   = 0, //Default
			eGDTFEncoderInvert_Yes  = 1,
			
		};
		
		enum EGDTFDmxInvert
		{
			eGDTFDmxInvert_No       = 0, //Default
			eGDTFDmxInvert_Yes      = 1,
			
		};
		
		enum EGdtfDmxRelationType // Default is missing
		{
			eGdtfDmxRelationType_Multiply   = 1,
			eGdtfDmxRelationType_Override   = 2,
		};

		enum  EGdtfChannelBitResolution
		{
			// Do not change the values!
			eGdtfChannelBitResolution_8 =  1, 
			eGdtfChannelBitResolution_16 = 2,
			eGdtfChannelBitResolution_24 = 3,
            eGdtfChannelBitResolution_32 = 4,
		};

        enum EGdtf_RDMParam_Type
        {
            RDM = 1,
            FixtureType,
            Fixture,
        };

        enum EGdtf_RDMParam_DataType
        {
            DS_NOT_DEFINED = 1,
            DS_BIT_FIELD, 
            DS_ASCII, 
            DS_UNSIGNED_BYTE, 
            DS_SIGNED_BYTE, 
            DS_UNSIGNED_WORD, 
            DS_SIGNED_WORD,
            DS_UNSIGNED_DWORD, 
            DS_SIGNED_DWORD, 
            DS_MS,          
        };

        enum EGdtf_RDMParam_Command
        {            
            None = 1, 
            CC_GET,
            CC_SET,
            CC_GET_SET,            
        };

        enum EGdtf_RDMParam_SensorUnit
        {
            UNITS_NONE = 1,
            UNITS_CENTIGRADE, 
            UNITS_VOLTS_DC,
            UNITS_VOLTS_AC_PEAK,
            UNITS_VOLTS_AC_RMS,
            UNITS_AMPERE_DC,
            UNITS_AMPERE_AC_PEAK,
            UNITS_AMPERE_AC_RMS,
            UNITS_HERTZ, 
            UNITS_OHM,
            UNITS_WATT,
            UNITS_KILOGRAM,
            UNITS_METERS,
            UNITS_METERS_SQUARED,
            UNITS_METERS_CUBED,
            UNITS_KILOGRAMMES_PER_METER_CUBED,
            UNITS_METERS_PER_SECOND,
            UNITS_METERS_PER_SECOND_SQUARED,
            UNITS_NEWTON,
            UNITS_JOULE,
            UNITS_PASCAL,
            UNITS_SECOND,
            UNITS_DEGREE,
            UNITS_STERADIAN,
            UNITS_CANDELA,
            UNITS_LUMEN,
            UNITS_LUX,
            UNITS_IRE,
            UNITS_BYTE,
            UNITS_MS,            
        };

        enum class EGdtf_RDMParam_SensorUnitPrefix
        {            
            PREFIX_NONE = 1,
            PREFIX_DECI,
            PREFIX_CENTI,
            PREFIX_MILLI,
            PREFIX_MICRO,
            PREFIX_NANO,
            PREFIX_PICO,
            PREFIX_FEMPTO,
            PREFIX_ATTO,
            PREFIX_ZEPTO,
            PREFIX_YOCTO,
            PREFIX_DECA,
            PREFIX_HECTO,
            PREFIX_KILO,
            PREFIX_MEGA,
            PREFIX_GIGA,
            PREFIX_TERRA,
            PREFIX_PETA,
            PREFIX_EXA,
            PREFIX_ZETTA,
            PREFIX_YOTTA,
        };

        enum class EGdtf_RDMValue_ThresholdOperator 
        {
            Is = 0,
            IsNot,
            Greater,
            Less,
        };

        enum class EGdtf_RDMValueBool_Value
        {
            eYes = 0,
            eNo,
        };

        enum EGdtf_RDMValue_SENSOR_DEFINITION_TYPE
        {
            SEND_TEMPERATURE = 0,
            SEND_VOLTAGE,
            SEND_CURRENT,
            SEND_FREQUENCY,
            SEND_RESISTANCE,
            SEND_POWER,
            SEND_MASS,
            SEND_LENGTH,
            SEND_AREA,
            SEND_VOLUME,
            SEND_DENSITY,
            SEND_VELOCITY,
            SEND_ACCELERATION,
            SEND_FORCE,
            SEND_ENERGY,
            SEND_PRESSURE,
            SEND_TIME,
            SEND_ANGLE,
            SEND_POSITION_X,
            SEND_POSITION_Y,
            SEND_POSITION_Z,
            SEND_ANGULAR_VELOCITY,
            SEND_LUMINOUS_INTENSITY,
            SEND_LUMINOUS_FLUX,
            SEND_ILLUMINANCE,
            SEND_CHROMINANCE_RED,
            SEND_CHROMINANCE_GREEN,
            SEND_CHROMINANCE_BLUE,
            SEND_CONTACTS,
            SEND_MEMORY,
            SEND_ITEMS,
            SEND_HUMIDITY,
            SEND_COUNTER_16BIT,
            SEND_OTHER,
            SEND_MS,
        };

        enum class EGdtf_RDMValue_LowesHighestDetectionSupported
        {
            eYES = 0,
            eNO,
        };

        enum class EGdtf_RDMValue_RecordValueSupported
        {
            eYES = 0,
            eNO,
        };
        
        enum class EGdtf_RDMValue_SLOT_INFO_Type 
        {
            ST_PRIMARY,
            ST_SEC_FINE,
            ST_SEC_TIMING,
            ST_SEC_SPEED,
            ST_SEC_CONTROL,
            ST_SEC_INDEX,
            ST_SEC_ROTATION,
            ST_SEC_INDEX_ROTATE,
            ST_SEC_UNDEFINED,
        };

        enum class EGdtf_RDMValue_SLOT_INFO_SlotLabelID 
        {
            SD_INTENSITY,
            SD_INTENSITY_MASTER,
            SD_PAN,
            SD_TILT,
            SD_COLOR_WHEEL,
            SD_COLOR_SUB_CYAN,
            SD_COLOR_SUB_YELLOW,
            SD_COLOR_SUB_MAGENTA,
            SD_COLOR_ADD_RED,
            SD_COLOR_ADD_GREEN,
            SD_COLOR_ADD_BLUE,
            SD_COLOR_CORRECTION,
            SD_COLOR_SCROLL,
            SD_COLOR_SEMAPHORE,
            SD_COLOR_ADD_AMBER,
            SD_COLOR_ADD_WHITE,
            SD_COLOR_ADD_WARM_WHITE,
            SD_COLOR_ADD_COOL_WHITE,
            SD_COLOR_SUB_UV,
            SD_COLOR_HUE,
            SD_COLOR_SATURATION,
            SD_STATIC_GOBO_WHEEL,
            SD_ROTO_GOBO_WHEEL,
            SD_PRISM_WHEEL,
            SD_EFFECTS_WHEEL,
            SD_BEAM_SIZE_IRIS,
            SD_EDGE,
            SD_FROST,
            SD_STROBE,
            SD_ZOOM,
            SD_FRAMING_SHUTTER,
            SD_SHUTTER_ROTATE,
            SD_DOUSER,
            SD_BARN_DOOR,
            SD_LAMP_CONTROL,
            SD_FIXTURE_CONTROL,
            SD_FIXTURE_SPEED,
            SD_MACRO,
            SD_POWER_CONTROL,
            SD_FAN_CONTROL,
            SD_HEATER_CONTROL,
            SD_FOUNTAIN_CONTROL,
            SD_UNDEFINED,    
        };
            
        enum class EGdtfColorSample 
        {            
            CES_01, // Default
            CES_02,
            CES_03,
            CES_04,
            CES_05,
            CES_06,
            CES_07,
            CES_08,
            CES_09,
            CES_10,
            CES_11,
            CES_12,
            CES_13,
            CES_14,
            CES_15,
            CES_16,
            CES_17,
            CES_18,
            CES_19,
            CES_20,
            CES_21,
            CES_22,
            CES_23,
            CES_24,
            CES_25,
            CES_26,
            CES_27,
            CES_28,
            CES_29,
            CES_30,
            CES_31,
            CES_32,
            CES_33,
            CES_34,
            CES_35,
            CES_36,
            CES_37,
            CES_38,
            CES_39,
            CES_40,
            CES_41,
            CES_42,
            CES_43,
            CES_44,
            CES_45,
            CES_46,
            CES_47,
            CES_48,
            CES_49,
            CES_50,
            CES_51,
            CES_52,
            CES_53,
            CES_54,
            CES_55,
            CES_56,
            CES_57,
            CES_58,
            CES_59,
            CES_60,
            CES_61,
            CES_62,
            CES_63,
            CES_64,
            CES_65,
            CES_66,
            CES_67,
            CES_68,
            CES_69,
            CES_70,
            CES_71,
            CES_72,
            CES_73,
            CES_74,
            CES_75,
            CES_76,
            CES_77,
            CES_78,
            CES_79,
            CES_80,
            CES_81,
            CES_82,
            CES_83,
            CES_84,
            CES_85,
            CES_86,
            CES_87,
            CES_88,
            CES_89,
            CES_90,
            CES_91,
            CES_92,
            CES_93,
            CES_94,
            CES_95,
            CES_96,
            CES_97,
            CES_98,
            CES_99,
        };
	}
}

#endif // !1
