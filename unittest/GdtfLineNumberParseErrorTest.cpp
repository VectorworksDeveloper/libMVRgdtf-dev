//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Unittest.h"
#include "GdtfLineNumberParseErrorTest.h"
#include <iostream>
#include "Utility.h"
#include "Include/VectorworksMVR.h"
using namespace VectorworksMVR;
using namespace VectorworksMVR::GdtfDefines;

#define __checkVCOM(x) checkVCOM(x, #x)
#define __checkVCOM_Failed(x) this->checkVCOM_NotSet(x, #x)

GdtfLineNumberParseErrorTest::GdtfLineNumberParseErrorTest(const std::string& currentDir) : GdtfUnitTest(currentDir)
{
	fErrorGdtf_Path = UnitTestUtil::GetTestResourceFolder() + kSeparator + "WrongDmxValue.gdtf";
}

GdtfLineNumberParseErrorTest::~GdtfLineNumberParseErrorTest()
{
}


std::string GdtfLineNumberParseErrorTest::GetUnitTestName()
{
	return  std::string("GdtfLineNumberParseErrorTest");
}

void GdtfLineNumberParseErrorTest::WriteFile(VectorworksMVR::IGdtfFixturePtr& fixture)
{
}

void GdtfLineNumberParseErrorTest::ReadFile(VectorworksMVR::IGdtfFixturePtr& fixture)
{
	
	//------------------------------------------------------------------------------    
	// Read Existing File with damaged structure
	IGdtfFixturePtr gdtfRead(IID_IGdtfFixture);
	__checkVCOM(gdtfRead->ReadFromFile(fErrorGdtf_Path.c_str()));

	size_t countErrors = 0;
	__checkVCOM(gdtfRead->GetParsingErrorCount(countErrors));
	checkifEqual("Count Errors", countErrors, size_t(1));

	PrintParsingErrorList(gdtfRead);
}
