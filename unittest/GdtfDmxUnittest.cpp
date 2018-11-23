//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Unittest.h"
#include "GdtfDmxUnittest.h"
#include <iostream>

#include "Include/VectorworksMVR.h"
using namespace VectorworksMVR;
using namespace VectorworksMVR::GdtfDefines;


#define __checkVCOM(x) this->checkVCOM(x, #x)

GdtfDmxUnittest::GdtfDmxUnittest(const std::string& currentDir)
{
    fPath = currentDir;
    fPath += std::string("/testDmx.gdtf");

    std::cout << "Export File to" << fPath << std::endl; 
}

GdtfDmxUnittest::~GdtfDmxUnittest()
{  
}

bool GdtfDmxUnittest::ExecuteTest()
{
	std::cout << "=                                     GdtfUnittest DMX Unit Test                           =" << std::endl;
    WriteFile();
    ReadFile();

    return true;
}

void GdtfDmxUnittest::WriteFile()
{
	//------------------------------------------------------------------------------------------------
	// Create Pointer to GDTF Interface
	IGdtfFixturePtr gdtfWrite (IID_IGdtfFixture);

    MvrUUID uuid (225204211, 177198167, 1575790, 96627);
    if(__checkVCOM(gdtfWrite->OpenForWrite(fPath.c_str(),"My FixtureName","My Manufacturer", uuid)))
    {
		//----------------------------------------------------------------
		// Create Attribute
		IGdtfAttributePtr attribute;
		__checkVCOM(gdtfWrite->CreateAttribute("Attribute","Pretty", &attribute));


		//----------------------------------------------------------------
		// Create Model
		IGdtfModelPtr model;
		__checkVCOM(gdtfWrite->CreateModel("Model", &model));

		IGdtfGeometryPtr geometry;
		__checkVCOM(gdtfWrite->CreateGeometry(EGdtfObjectType::eGdtfGeometry, "Geometry", model, STransformMatrix(), &geometry));

		IGdtfDmxModePtr mode;
		__checkVCOM(gdtfWrite->CreateDmxMode("Mode", &mode));
		__checkVCOM(mode->SetGeometry(geometry));

		//----------------------------------------------------------------
		// Write 8 bit Channel
		IGdtfDmxChannelPtr bit8channel;
		__checkVCOM(mode->CreateDmxChannel("8bit Channel", &bit8channel));
		__checkVCOM(bit8channel->SetGeometry(geometry));
		bit8channel->SetCoarse(1);

		// First Logical Channel
		IGdtfDmxLogicalChannelPtr bit8LogicalChannel1;
		bit8channel->CreateLogicalChannel("Log1", &bit8LogicalChannel1);
		bit8LogicalChannel1->SetAttribute(attribute);

		IGdtfDmxChannelFunctionPtr bit8Function1;
		bit8LogicalChannel1->CreateDmxFunction("Function1", &bit8Function1);
		bit8Function1->SetStartAddress(0);

		IGdtfDmxChannelSetPtr bit8ChannelSet1;
		bit8Function1->CreateDmxChannelSet("My Name1", 15, 60, &bit8ChannelSet1);

		IGdtfDmxChannelSetPtr bit8ChannelSet2;
		bit8Function1->CreateDmxChannelSet("My Name2", 61, 90, &bit8ChannelSet2);

		IGdtfDmxChannelSetPtr bit8ChannelSet3;
		bit8Function1->CreateDmxChannelSet("My Name3", 91, 92, &bit8ChannelSet3);

		// Second Channel Function
		IGdtfDmxChannelFunctionPtr bit8Function2;
		bit8LogicalChannel1->CreateDmxFunction("Function2", &bit8Function2);
		bit8Function2->SetStartAddress(100);

		IGdtfDmxChannelSetPtr bit8ChannelSet4;
		bit8Function2->CreateDmxChannelSet("My Name4", 100, 120, &bit8ChannelSet4);

		IGdtfDmxChannelSetPtr bit8ChannelSet5;
		bit8Function2->CreateDmxChannelSet("My Name5", 121, 130, &bit8ChannelSet5);

		IGdtfDmxChannelSetPtr bit8ChannelSet6;
		bit8Function2->CreateDmxChannelSet("My Name6", 160, 165, &bit8ChannelSet6);

		// Second Logical Channel
		IGdtfDmxLogicalChannelPtr bit8LogicalChannel2;
		bit8channel->CreateLogicalChannel("Log2", &bit8LogicalChannel2);
		bit8LogicalChannel2->SetAttribute(attribute);

		IGdtfDmxChannelFunctionPtr bit8Function3;
		bit8LogicalChannel2->CreateDmxFunction("Function3", &bit8Function3);
		bit8Function3->SetStartAddress(170);

		IGdtfDmxChannelSetPtr bit8ChannelSet7;
		bit8Function3->CreateDmxChannelSet("My Name7", 170, 170, &bit8ChannelSet7);

		IGdtfDmxChannelSetPtr bit8ChannelSet8;
		bit8Function3->CreateDmxChannelSet("My Name8", 180, 180, &bit8ChannelSet8);

		IGdtfDmxChannelSetPtr bit8ChannelSet9;
		bit8Function3->CreateDmxChannelSet("My Name9", 181, 198, &bit8ChannelSet9);

		// Second Channel Function
		IGdtfDmxChannelFunctionPtr bit8Function4;
		bit8LogicalChannel2->CreateDmxFunction("Function4", &bit8Function4);
		bit8Function4->SetStartAddress(200);

		IGdtfDmxChannelSetPtr bit8ChannelSet10;
		bit8Function4->CreateDmxChannelSet("My Name10", 210, 210, &bit8ChannelSet10);

		IGdtfDmxChannelSetPtr bit8ChannelSet11;
		bit8Function4->CreateDmxChannelSet("My Name11", 220, 225, &bit8ChannelSet11);

		IGdtfDmxChannelSetPtr bit8ChannelSet12;
		bit8Function4->CreateDmxChannelSet("My Name12", 230, 255, &bit8ChannelSet12);

		//----------------------------------------------------------------
		// Write 16 bit Channel
		IGdtfDmxChannelPtr bit16channel;
		__checkVCOM(mode->CreateDmxChannel("8bit Channel", &bit16channel));
		__checkVCOM(bit16channel->SetGeometry(geometry));
		bit16channel->SetCoarse(1);
		bit16channel->SetFine(2);

		IGdtfDmxLogicalChannelPtr bit16LogicalChannel;
		bit16channel->CreateLogicalChannel("Log1", &bit16LogicalChannel);
		bit16LogicalChannel->SetAttribute(attribute);

		IGdtfDmxChannelFunctionPtr bit16Function;
		bit16LogicalChannel->CreateDmxFunction("Function", &bit16Function);

		IGdtfDmxChannelSetPtr bit16ChannelSet1;
		bit16Function->CreateDmxChannelSet("My Name1", 15, 60, &bit16ChannelSet1);

		IGdtfDmxChannelSetPtr bit16ChannelSet;
		bit16Function->CreateDmxChannelSet("My Name2", 61, 90, &bit16ChannelSet);

		IGdtfDmxChannelSetPtr bit16ChannelSet3;
		bit16Function->CreateDmxChannelSet("My Name3", 128, 4501, &bit16ChannelSet3);


        __checkVCOM(gdtfWrite->Close());
    }
}

void GdtfDmxUnittest::ReadFile()
{
	//------------------------------------------------------------------------------------------------
	// Create Pointer to GDTF Interface
    IGdtfFixturePtr gdtfRead (IID_IGdtfFixture);
    if(__checkVCOM(gdtfRead->ReadFromFile(fPath.c_str())))
    {
		//------------------------------------------------------------------------------ 
		// Read the Attributes
		size_t countAttributes = 0;
		__checkVCOM(gdtfRead->GetAttributeCount(countAttributes));
		this->checkifEqual("Check Count Attributes ", countAttributes, size_t(1));

		// Check Attribute
		IGdtfAttributePtr	gdtfAttribute;
		__checkVCOM(gdtfRead->GetAttributeAt(0, &gdtfAttribute));
		this->checkifEqual("gdtfAttribute GetName() ", gdtfAttribute->GetName(), "Attribute");
		this->checkifEqual("gdtfAttribute GetName() ", gdtfAttribute->GetPrettyName(), "Pretty");


		//------------------------------------------------------------------------------    
		// Extract Geometry & Models
		size_t countModels = 0;
		__checkVCOM(gdtfRead->GetModelCount(countModels));
		for (size_t i = 0; i < countModels; i++)
		{
			IGdtfModelPtr gdtfModel;
			if (__checkVCOM(gdtfRead->GetModelAt(i, &gdtfModel)))
			{
				MvrString  modelName = gdtfModel->GetName();
				MvrString geometryFile = gdtfModel->Get3DSGeometryFile();
				this->checkifEqual("gdtfModelGetName ", modelName, "Model");

				// Height
				double heightVal = 0.0;
				__checkVCOM(gdtfModel->GetHeight(heightVal));
				this->checkifEqual("gdtfModelGetHeight ", heightVal, double(0));

				// Width
				double widthVal = 0.0;
				__checkVCOM(gdtfModel->GetWidth(widthVal));
				this->checkifEqual("gdtfModelGetWidth ", widthVal, double(0));

				// Length
				double lengthVal = 0.0;
				__checkVCOM(gdtfModel->GetLength(lengthVal));
				this->checkifEqual("gdtfModelGetLength ", lengthVal, double(0));

				// PrimitiveType
				EGdtfModel_PrimitiveType primitiveType = EGdtfModel_PrimitiveType::eGdtfModel_PrimitiveType_Undefined;
				__checkVCOM(gdtfModel->GetPrimitiveType(primitiveType));
				this->checkifEqual("gdtfModelGetPrimitiveType ", primitiveType, EGdtfModel_PrimitiveType::eGdtfModel_PrimitiveType_Undefined);
			}
		} // Models loop


		//--------------------------------------------------------------------------------
		// Geometry Section
		size_t countGeo = 0;
		__checkVCOM(gdtfRead->GetGeometryCount(countGeo));
		this->checkifEqual("Geometry Count ", countGeo, size_t(1));

		IGdtfGeometryPtr gdtfGeometry;
		__checkVCOM(gdtfRead->GetGeometryAt(0, &gdtfGeometry));
		this->checkifEqual("GetGeometryAtGetName() ", gdtfGeometry->GetName(), "Geometry");
		

		//------------------------------------------------------------------
		// Get DMX Mode
		size_t countDmxModes;
		__checkVCOM(gdtfRead->GetDmxModeCount(countDmxModes));
		this->checkifEqual("Check Count DMX Modes", countDmxModes, size_t(1));

		IGdtfDmxModePtr mode;
		__checkVCOM(gdtfRead->GetDmxModeAt(0, &mode));

		size_t countChannels = 0;
		__checkVCOM(mode->GetDmxChannelCount(countChannels));
		this->checkifEqual("Check Count DMX Channels", countChannels, size_t(2));
		

		//----------------------------------------------------------------
		// Read 8 bit Channel
		IGdtfDmxChannelPtr bit8channel;
		__checkVCOM(mode->GetDmxChannelAt(0, &bit8channel));
		Check8bitChannel(bit8channel);

		//----------------------------------------------------------------
		// Read 16 bit Channel
		IGdtfDmxChannelPtr bit16channel;
		__checkVCOM(mode->GetDmxChannelAt(1, &bit16channel));

		IGdtfDmxLogicalChannelPtr bit16LogicalChannel;
		__checkVCOM(bit16channel->GetLogicalChannelAt(0, &bit16LogicalChannel));

		IGdtfDmxChannelFunctionPtr bit16Function;
		__checkVCOM(bit16LogicalChannel->GetDmxFunctionAt(0, &bit16Function));

		// Check DMX Channel Sets
		size_t countChannelSets = 0;
		__checkVCOM(bit16Function->GetDmxChannelSetCount(countChannelSets));
		this->checkifEqual("Check Count DMX Channels", countChannelSets, size_t(6));

		IGdtfDmxChannelSetPtr bit16ChannelSet1;
		__checkVCOM(bit16Function->GetDmxChannelSetAt(0, &bit16ChannelSet1)); 
		this->CheckChannelSet(bit16ChannelSet1, "",0,14);

		IGdtfDmxChannelSetPtr bit16ChannelSet2;
		__checkVCOM(bit16Function->GetDmxChannelSetAt(1, &bit16ChannelSet2));
		this->CheckChannelSet(bit16ChannelSet2, "My Name1",15,60);

		IGdtfDmxChannelSetPtr bit16ChannelSet3;
		__checkVCOM(bit16Function->GetDmxChannelSetAt(2, &bit16ChannelSet3));
		this->CheckChannelSet(bit16ChannelSet3, "My Name2",61,90);

		IGdtfDmxChannelSetPtr bit16ChannelSet4;
		__checkVCOM(bit16Function->GetDmxChannelSetAt(3, &bit16ChannelSet4));
		this->CheckChannelSet(bit16ChannelSet4, "",91,127);

		IGdtfDmxChannelSetPtr bit16ChannelSet5;
		__checkVCOM(bit16Function->GetDmxChannelSetAt(4, &bit16ChannelSet5));
		this->CheckChannelSet(bit16ChannelSet5, "My Name3",128,4501);

		IGdtfDmxChannelSetPtr bit16ChannelSet6;
		__checkVCOM(bit16Function->GetDmxChannelSetAt(5, &bit16ChannelSet6));
		this->CheckChannelSet(bit16ChannelSet6, "",4502,65535);

	}

}

void GdtfDmxUnittest::CheckChannelSet(IGdtfDmxChannelSetPtr& channelSet, std::string name, DmxValue start, DmxValue end)
{
	this->checkifEqual("Check Name ", name, channelSet->GetName());

	DmxValue thisStart = 0;
	__checkVCOM(channelSet->GetDmxStartAddress(thisStart));
	this->checkifEqual("Check Start ", start, thisStart);

	DmxValue thisEnd = 0;
	__checkVCOM(channelSet->GetDmxEndAddress(thisEnd));
	this->checkifEqual("Check End ",  end, thisEnd);
}

void GdtfDmxUnittest::CheckFunction(VectorworksMVR::IGdtfDmxChannelFunctionPtr& function, std::string name, VectorworksMVR::GdtfDefines::DmxValue start, VectorworksMVR::GdtfDefines::DmxValue end)
{
	this->checkifEqual("Check Name ", name, function->GetName());

	DmxValue thisStart = 0;
	__checkVCOM(function->GetStartAddress(thisStart));
	this->checkifEqual("Check Start ", start, thisStart);

	DmxValue thisEnd = 0;
	__checkVCOM(function->GetEndAddress(thisEnd));
	this->checkifEqual("Check End ",  end, thisEnd);
}

void GdtfDmxUnittest::Check8bitChannel(VectorworksMVR::IGdtfDmxChannelPtr& dmxChannel)
{
	// ---------------------------------------------------------------------------
	// Get Logical Channels
	size_t count = 0;
	__checkVCOM(dmxChannel->GetLogicalChannelCount(count));
	this->checkifEqual("Count Logical Channels", count, size_t(2));

	IGdtfDmxLogicalChannelPtr bit8LogicalChannel1;
	__checkVCOM(dmxChannel->GetLogicalChannelAt(0, &bit8LogicalChannel1));

	IGdtfDmxLogicalChannelPtr bit8LogicalChannel2;
	__checkVCOM(dmxChannel->GetLogicalChannelAt(1, &bit8LogicalChannel2));

	// ---------------------------------------------------------------------------
	// Get Functions
	__checkVCOM(bit8LogicalChannel1->GetDmxFunctionCount(count));
	this->checkifEqual("Count Function Count", count, size_t(2));

	__checkVCOM(bit8LogicalChannel2->GetDmxFunctionCount(count));
	this->checkifEqual("Count Function Count", count, size_t(2));

	IGdtfDmxChannelFunctionPtr bit8Function1;
	__checkVCOM(bit8LogicalChannel1->GetDmxFunctionAt(0, &bit8Function1));
	CheckFunction(bit8Function1, "Function1", 0, 99);

	IGdtfDmxChannelFunctionPtr bit8Function2;
	__checkVCOM(bit8LogicalChannel1->GetDmxFunctionAt(1, &bit8Function2));
	CheckFunction(bit8Function2, "Function2", 100, 169);

	IGdtfDmxChannelFunctionPtr bit8Function3;
	__checkVCOM(bit8LogicalChannel2->GetDmxFunctionAt(0, &bit8Function3));
	CheckFunction(bit8Function3, "Function3", 170, 199);

	IGdtfDmxChannelFunctionPtr bit8Function4;
	__checkVCOM(bit8LogicalChannel2->GetDmxFunctionAt(1, &bit8Function4));
	CheckFunction(bit8Function4, "Function4", 200, 255);

	// ---------------------------------------------------------------------------
	// Check Channel Set Count bit8Function1
	__checkVCOM(bit8Function1->GetDmxChannelSetCount(count));
	this->checkifEqual("bit8Function1 Count Channel Set", count, size_t(5));

	IGdtfDmxChannelSetPtr bit8ChannelSet1;
	__checkVCOM(bit8Function1->GetDmxChannelSetAt(0, &bit8ChannelSet1));
	this->CheckChannelSet(bit8ChannelSet1, "",0,14);

	IGdtfDmxChannelSetPtr bit8ChannelSet2;
	__checkVCOM(bit8Function1->GetDmxChannelSetAt(1, &bit8ChannelSet2));
	this->CheckChannelSet(bit8ChannelSet2, "My Name1",15,60);

	IGdtfDmxChannelSetPtr bit8ChannelSet3;
	__checkVCOM(bit8Function1->GetDmxChannelSetAt(2, &bit8ChannelSet3));
	this->CheckChannelSet(bit8ChannelSet3, "My Name2",61,90);

	IGdtfDmxChannelSetPtr bit8ChannelSet4;
	__checkVCOM(bit8Function1->GetDmxChannelSetAt(3, &bit8ChannelSet4));
	this->CheckChannelSet(bit8ChannelSet4, "My Name3",91,92);

	IGdtfDmxChannelSetPtr bit8ChannelSet5;
	__checkVCOM(bit8Function1->GetDmxChannelSetAt(4, &bit8ChannelSet5));
	this->CheckChannelSet(bit8ChannelSet5, "",93,99);

	// ---------------------------------------------------------------------------
	// Check Channel Set Count bit8Function2
	__checkVCOM(bit8Function2->GetDmxChannelSetCount(count));
	this->checkifEqual("bit8Function2 Count Channel Set", count, size_t(5));

	IGdtfDmxChannelSetPtr bit8ChannelSet6;
	__checkVCOM(bit8Function2->GetDmxChannelSetAt(0, &bit8ChannelSet1));
	this->CheckChannelSet(bit8ChannelSet1, "My Name4",100,120);

	IGdtfDmxChannelSetPtr bit8ChannelSet7;
	__checkVCOM(bit8Function2->GetDmxChannelSetAt(1, &bit8ChannelSet2));
	this->CheckChannelSet(bit8ChannelSet2, "My Name5",121,130);

	IGdtfDmxChannelSetPtr bit8ChannelSet8;
	__checkVCOM(bit8Function2->GetDmxChannelSetAt(2, &bit8ChannelSet3));
	this->CheckChannelSet(bit8ChannelSet3, "",131,159);

	IGdtfDmxChannelSetPtr bit8ChannelSet9;
	__checkVCOM(bit8Function2->GetDmxChannelSetAt(3, &bit8ChannelSet4));
	this->CheckChannelSet(bit8ChannelSet4, "My Name6",160,165);

	IGdtfDmxChannelSetPtr bit8ChannelSet10;
	__checkVCOM(bit8Function2->GetDmxChannelSetAt(4, &bit8ChannelSet5));
	this->CheckChannelSet(bit8ChannelSet5, "",166,169);
	// ---------------------------------------------------------------------------
	// Check Channel Set Count bit8Function3
	__checkVCOM(bit8Function3->GetDmxChannelSetCount(count));
	this->checkifEqual("bit8Function3 Count Channel Set", count, size_t(5));

	IGdtfDmxChannelSetPtr bit8ChannelSet11;
	__checkVCOM(bit8Function3->GetDmxChannelSetAt(0, &bit8ChannelSet11));
	this->CheckChannelSet(bit8ChannelSet11, "My Name7",170,170);

	IGdtfDmxChannelSetPtr bit8ChannelSet12;
	__checkVCOM(bit8Function3->GetDmxChannelSetAt(1, &bit8ChannelSet12));
	this->CheckChannelSet(bit8ChannelSet12, "",171,179);

	IGdtfDmxChannelSetPtr bit8ChannelSet13;
	__checkVCOM(bit8Function3->GetDmxChannelSetAt(2, &bit8ChannelSet13));
	this->CheckChannelSet(bit8ChannelSet13, "My Name8",180,180);

	IGdtfDmxChannelSetPtr bit8ChannelSet14;
	__checkVCOM(bit8Function3->GetDmxChannelSetAt(3, &bit8ChannelSet14));
	this->CheckChannelSet(bit8ChannelSet14, "My Name9",181,198);

	IGdtfDmxChannelSetPtr bit8ChannelSet15;
	__checkVCOM(bit8Function3->GetDmxChannelSetAt(4, &bit8ChannelSet15));
	this->CheckChannelSet(bit8ChannelSet15, "",199,199);

	// ---------------------------------------------------------------------------
	// Check Channel Set Count bit8Function4
	__checkVCOM(bit8Function4->GetDmxChannelSetCount(count));
	this->checkifEqual("bit8Function4 Count Channel Set", count, size_t(6));

	IGdtfDmxChannelSetPtr bit8ChannelSet16;
	__checkVCOM(bit8Function4->GetDmxChannelSetAt(0, &bit8ChannelSet16));
	this->CheckChannelSet(bit8ChannelSet16, "",200,209);

	IGdtfDmxChannelSetPtr bit8ChannelSet17;
	__checkVCOM(bit8Function4->GetDmxChannelSetAt(1, &bit8ChannelSet17));
	this->CheckChannelSet(bit8ChannelSet17, "My Name10",210,210);

	IGdtfDmxChannelSetPtr bit8ChannelSet18;
	__checkVCOM(bit8Function4->GetDmxChannelSetAt(2, &bit8ChannelSet18));
	this->CheckChannelSet(bit8ChannelSet18, "",211,219);

	IGdtfDmxChannelSetPtr bit8ChannelSet19;
	__checkVCOM(bit8Function4->GetDmxChannelSetAt(3, &bit8ChannelSet19));
	this->CheckChannelSet(bit8ChannelSet19, "My Name11",220,225);

	IGdtfDmxChannelSetPtr bit8ChannelSet20;
	__checkVCOM(bit8Function4->GetDmxChannelSetAt(4, &bit8ChannelSet20));
	this->CheckChannelSet(bit8ChannelSet20, "",226,229);

	IGdtfDmxChannelSetPtr bit8ChannelSet21;
	__checkVCOM(bit8Function4->GetDmxChannelSetAt(5, &bit8ChannelSet21));
	this->CheckChannelSet(bit8ChannelSet21, "My Name12",230,255);
}