//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#ifndef FOLDER_SPECIFIER_ENUM
#define FOLDER_SPECIFIER_ENUM

enum EFolderSpecifier {
	kRootFolderSpecifier	= 0,
	kApplicationFolder		= 1,
	kExternalsFolder		= 2,
	kExternalDataFolder		= 3,
	kWorkspacesFolder		= 4,
	kOverlaysFolder			= kWorkspacesFolder,
	kParametricsFolder		= 5,
	kDebugtoolsFolder		= 6,
	kTemplatesFolder		= 7,
	kStandardsFolder		= 8,
	kHelpFolder				= 9,
	kDictionariesFolder		= 10,
	kObjectLibrariesFolder  = 11,
	kAppDataFolder			= 12,
	kLibrariesFolder		= 13,
	kDefaultsFolder			= 14,
	kSettingsFolder			= 15,
	kObjectsImperialFolder	= 16,
	kObjectsMetricFolder	= 17,
	kPDFResourcesFolder		= 18,
	kCommonFolder			= 19,
	kCommonDataFolder		= 20,
	kCommonIncludesFolder   = 21,
	kCommonInterfacesFolder = 22,
	kFavoritesFolder		= 23,
	kIconsFolder			= 24,
	
	k_RESERVED_INTERNAL_OLDTemp = 68,		// not for use by SDK developers
	k_RESERVED_INTERNAL_OLDStan = 69,		// not for use by SDK developers
	k_RESERVED_INTERNAL_OLDEvntLyt = 139, // not for use by SDK developers

	kDefaultTexturesFolder			= 100,
	kDefaultCabinetHandlesFolder	= 101,
	kDefaultDoorHardwareFolder		= 102,
	kDefaultGradientsFolder			= 103,
	kDefaultHardscapeHatchesFolder	= 104,
	kDefaultHatchesFolder			= 105,
	kDefaultImageFillsFolder		= 106,
	kDefaultPlantsFolder			= 107,
	kDefaultToiletsFolder			= 108,
	kDefaultRWBackgroundsFolder		= 109,
	kDefaultSeatingLayoutFolder		= 110,
	kDefaultTileSymbolsFolder		= 111,
	kDefaultHumanFigTexturesFolder	= 112,
	kDefaultWallSlabRoofStylesFolder	= 113,
	kDefaultStairsFolder			= 114,
	kDefaultTitleBlocksFolder		= 115,
	kDefaultSectionMarkersFolder	= 116,
	kDefaultRepetitiveUnitFolder	= 117,
	kDefaultDoorCustomLeavesFolder	= 118,
	kDefaultLightingGobosFolder		= 119,
	kDefaultReportsFolder			= 120,
	kDefaultLightingSymbolsFolder	= 121,
	kDefaultPlants2DSymbolsFolder	= 122,
	kDefaultPlants3DSymbolsFolder	= 123,
	kDefaultPlantsHatchesFolder		= 124,
	kDefaultRepetitiveFlooringFolder = 125,
	kDefaultRepetitiveFramingFolder = 126,
	kDefaultRepetitiveMasonryFolder	= 127,
	kDefaultRepetitiveMiscFolder	= 128,
	kDefaultRepetitiveRoofingFolder = 129,
	kDefaultRepetitiveSidingFolder	= 130,
	kDefaultWallSlabRoofHatchesFolder	= 131,
	kDefaultWallSlabRoofTexturesFolder	= 132,
	kDefaultWindowCustomShuttersFolder = 133,
	kDefaultSketchStylesFolder		= 134,
	kDefaultPlantListFolder			= 135,
	kDefaultPlantDatabaseFolder		= 136,
	kDefaultColorPalettesFolder		= 137,
	kDefaultFramingMemberProfileFolder = 138,
	kDefaultSpacesOccupantOrgFolder = 140,
	kDefaultSpacesNameListsFolder	= 141,
	kDefaultStructuralShapesFolder	= 142,
	kDefaultLandmarkSchedules		= 143,
	kDefaultVideoScreenFolder		= 144,
	kDefaultVSCasingsCRT43			= 145,
	kDefaultVSCasingsCRT169			= 146,
	kDefaultVSCasingsFlat43			= 147,
	kDefaultVSCasingsFlat169		= 148,
	kDefaultVSCasingsCRTCurved43	= 149,
	kDefaultVSScreenImages			= 150,
	kDefaultVSProjectorModels		= 151,
	kDefaultVSStandModels			= 152,
	kDefaultDashStylesFolder		= 153,
	kDefaultEventPlanningFolder		= 154,
	kDefaultEPRoom					= 155,
	kDefaultEPStage					= 156,
	kDefaultEPLectern				= 157,
	kDefaultEPScreen				= 158,
	kDefaultEPSeating				= 159,
	kDefaultEPStep					= 160,
	kDefaultCustomStair				= 161,
	kDefaultCustomStairStringers	= 162,
	kDefaultTilesFolder				= 163,
	kDefaultTextStylesFolder    	= 164,
	kDefaultFocusPointGraphics		= 165,
	kRenderworksFolder				= 166,
	kDefaultExistingTreeFolder		= 167,
	kDefaultHeliodonFolder			= 168,
	kDefaultHeliodonSymbolsFolder	= 169,
	kDefaultHeliodonCitiesFolder	= 170,
	kDefaultRenderStylesFolder		= 171,
	kDefaultStorySupportFolder		= 172,
	kDefaultDetailMarkersFolder		= 173,
	kDefaultLineTypesFolder			= 174,
	kDefaultAudioToolsFolder		= 175,
	kDefaultATBumpersFolder			= 176,
	kDefaultATSpeakersFolder		= 177,
	kExtrasFolder					= 178,
	kSamplesFolder					= 179,
	kDefaultParkingSpaceFolder		= 180,
	kDefaultSpotlightSchedules		= 181,
    kDefaultWorkspacesFolder        = 182,
	kDefaultNotesFolder				= 183,
	kDefaultWallSlabRoofStylesImperialFolder	= 184,
	kDefaultWallSlabRoofStylesMetricFolder		= 185,
	kDefaultWallSlabRoofStylesUKMetricFolder	= 186,
	kDefaultEnergyAnalysisFolder			= 187,
	kHoistToolsFolder				        = 188,
	kAccessorySymbolsFolder					= 189,
	kEntertainmentLightingFolder			= 190,
	kDefaultMarionetteFolder				= 191,
	kDefaultMarionetteAttributesFolder		= 192,
	kDefaultMarionetteMathFolder			= 193,
	kDefaultMarionetteObjectsFolder			= 194,
	kDefaultMarionetteObjectsNurbsFolder	= 195,
	kDefaultMarionetteTexturesFolder		= 196,
	kDefaultRecordFormatsFolder				= 197,
	kDefaultIrrigationFolder				= 198,
	kDefaultTagLabelFolder					= 199,
	kDefaultSpotlightStageFolder			= 200,
	kSpotlightTrussFolder					= 201,
	kDefaultInteriorElevationMarkersFolder	= 202,
	kDefaultSoftGoodsTexturesFolder			= 203,
	kDefaultRailingFenceFolder				= 204,
	kDefaultRailingFenceProfilePostFolder	= 205,
	kDefaultRailingFenceProfileTopRailFolder = 206,
	kDefaultRailingFenceRailingFenceFolder	= 207,
	kDefaultRailingFenceRFFenceFolder		= 208,
	kDefaultRailingFenceRFRailingFolder		= 209,
	kDefaultRailingFenceSymbolPostFolder	= 210,
	kDefaultSlabDrainSymbolsFolder			= 211,
	kDefaultBIMobjectFolder					= 212,
	
	kDefaultCableToolsFolder				= 214,
	kDefaultCableToolsBreakOutLabelsFolder	= 215,
	kDefaultCableToolsMultiHeadSymbolsFolder = 216,

	kObjectStylesFolder						= 217,
	kObjectStylesBathShowerFolder			= 218,
	kObjectStylesCabinetBaseFolder			= 219,
	kObjectStylesCabinetUtilityFolder		= 220,
	kObjectStylesCabinetWallFolder			= 221,
	kObjectStylesCampanileFolder			= 222,
	kObjectStylesColumnFolder				= 223,
	kObjectStylesCommDeviceFolder			= 224,
	kObjectStylesCompartmentSinkFolder		= 225,
	kObjectStylesCustomCabinetFolder		= 226,
	kObjectStylesDeskFolder					= 227,
	kObjectStylesDoorFolder					= 228,
	kObjectStylesEscalatorFolder			= 229,
	kObjectStylesFireplaceFolder			= 230,
	kObjectStylesGrabBarFolder				= 231,
	kObjectStylesHardscapeFolder			= 232,
	kObjectStylesHVACDamperFolder			= 233,
	kObjectStylesHVACDiffuserFolder			= 234,
	kObjectStylesHVACElbowDuctFolder		= 235,
	kObjectStylesHVACFlexDuctFolder			= 236,
	kObjectStylesHVACOutletFolder			= 237,
	kObjectStylesHVACSplitterFolder			= 238,
	kObjectStylesHVACStraightDuctFolder		= 239,
	kObjectStylesHVACTransitionFolder		= 240,
	kObjectStylesHVACVerticalDuctFolder		= 241,
	kObjectStylesHVACVerticalElbowFolder	= 242,
	kObjectStylesIncandescentFixtureFolder	= 243,
	kObjectStylesLandscapeAreaFolder		= 244,
	//lighting accessory and instrument have IDs in default, even though folder was moved to object styles
	kObjectStylesPilasterFolder				= 247,
	//plants constant is in defaults even though folder is object styles
	kObjectStylesRampFolder					= 248,
	kObjectStylesReceptacleFolder			= 249,
	kObjectStylesShelvingUnitFolder			= 250,
	kObjectStylesSimpleElevatorFolder		= 251,
	kObjectStylesSpeakerFolder				= 252,
	kObjectStylesStageDeckFolder			= 253,
	kObjectStylesSwitchFolder				= 254,
	kObjectStylesTablesAndChairsFolder		= 255,
	kObjectStylesToiletStallFolder			= 256,
	//walls, roof, slab styles constant is in defaults even though folder is object styles
	kObjectStylesWindowFolder				= 257,
	kObjectStylesWorkstationCounterFolder	= 258,
	kObjectStylesWorkstationOverheadFolder	= 259,
	kObjectStylesWorkstationPanelFolder		= 260,
	kObjectStylesWorkstationPedestalFolder	= 261,
	
	//leaving a numbering gap to allow for more object styles entries; not really necessary, 
	//but it's nice to have same directories together.
	kObjectsArchitectureFolder				= 266,
	kObjectsBuildingEquipFolder				= 267,
	kObjectsBuildingFurnishingsFolder		= 268,
	kObjectsBuildingServicesFolder			= 269,
	kObjectsEntertainmentAudioFolder		= 270,
	kObjectsEntertainmentControlFolder		= 271,
	kObjectsEntertainmentStage_EventFolder	= 272,
	kObjectsEntertainmentTrussFolder		= 273,
	kObjectsLandscapePlantsFolder			= 274,
	kObjectsLandscapeSiteFolder				= 275,
	kObjectsMiscellaneous_EntourageFolder	= 276,
	
	kDefaultIrrigationCatalogsFolder			= 277,

	kDefaultIrrigationContentControllersFolder	= 278,
	kDefaultIrrigationContentOutletsFolder		= 279,
	kDefaultIrrigationContentOutletsDripFolder	= 280,
	kDefaultIrrigationContentPipesFolder		= 281,
	kDefaultIrrigationContentPOCsFolder			= 282,
	kDefaultIrrigationContentSysCompsFolder		= 283,
	kDefaultIrrigationContentValvesFolder		= 284,

	kDefaultIrrigationSymbolsControllersFolder	= 285,
	kDefaultIrrigationSymbolsOutletsFolder		= 286,
	kDefaultIrrigationSymbolsPOCsFolder			= 287,
	kDefaultIrrigationSymbolsSysCompsFolder		= 288,
	kDefaultIrrigationSymbolsValvesFolder		= 289,

	kDefaultCableToolsMarkerSymbolsFolder		= 290,

    kObjectsLandscapeSiteStipplesFolder         = 291,

	kDefaultFoliageFolder						= 292,
	kDefaultSpacePlanningFolder					= 293,
	kDefaultNorthArrowsFolder					= 294,

	kObjectStylesTitleBlockBorderFolder			= 300,

	kSpotlightFolder							= 302,
	kSpotlightDataFolder						= 303,
	kSpotlightDataBraceworksFolder				= 304,
	kSpotlightDataBrackworksCrossSectionFolder  = 305,

	kObjectsEntertainmentEventFolder			= 306,
    
    kDefaultHyperlinkFolder                     = 307,
	kObjectsEntLightingGobos					= 308,
	kObjectsLandscapeFurnishings				= 309,
};

#endif
