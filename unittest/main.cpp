﻿//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include <iostream>
#include "Include/VectorworksMVR.h"
#include "Unittest.h"
#include "MvrUnittest.h"
#include "GdtfUnittest.h"
#include "GdtfDmxUnittest.h"
#include "GdtfXmlError.h"
#include "GdtfFunctionModeMaster.h"
#include "Utility.h"


using namespace VectorworksMVR;					

int main(int argc, char* argv[])
{
	// Get Current dir    
	std::string gdtfBase; UnitTestUtil::GetFolderAppDataPath(gdtfBase);

	GdtfUnittest gdtfTest(gdtfBase);
	bool gdtfFailed = gdtfTest.RunTest();

	GdtfDmxUnittest gdtfDmxTest(gdtfBase);
	bool gdtfDmxFailed = gdtfDmxTest.RunTest();

	MvrUnittest mvrTest(gdtfBase);
	bool mvrFailed = mvrTest.RunTest();

	GdtfXmlErrorTest errorTest(gdtfBase);
	bool errorFailed = errorTest.RunTest();

	GdtfFunctionModeMasterTest modeMasterTest(gdtfBase);
	bool modeMasterFailed = modeMasterTest.RunTest();
    
    bool errorOcurred = (mvrFailed || gdtfFailed || gdtfDmxFailed || errorFailed || modeMasterFailed);

    if (! errorOcurred) 
    {
        UnitTestUtil::print_Ascii_DEER();
    }
    else 
    {
        UnitTestUtil::print_Ascii_BUG();        
    }

    return errorOcurred;
}


