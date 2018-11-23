//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Unittest.h"
#include <iostream>

using namespace VectorworksMVR;

Unittest::Unittest()
{
    fFailed = false;
};

Unittest::~Unittest()
{
};

bool Unittest::RunTest()
{
    std::cout << "============================================================================================" << std::endl;
    this->ExecuteTest();

   for(size_t i = 0; i < fFailedTests.size(); i++)
   {
       std::cout << fFailedTests[i].fMessage << std::endl;
   }
   
if(fFailed)
{
	std::cout << "                                           FAILED                                          =" << std::endl;
}
else
{
	std::cout << "=                                         SUCCEEDED                                        =" << std::endl;
}
	std::cout << "============================================================================================" << std::endl;
    return fFailed;
}

void Unittest::checkifEqual(const std::string& check, const Uint32 val1, const Uint32 val2)
{
	if (val1 == val2) return;

	// Else Log the error
	fFailed = true;

	UnittestFailObject test;
	test.fMessage += check;
	test.fMessage += "Aspected: ";
	test.fMessage += std::to_string(val1);
	test.fMessage += " Result: ";
	test.fMessage += std::to_string(val2);

	fFailedTests.push_back(test);
};

void Unittest::checkifEqual(const std::string& check, const Sint32 val1, const Sint32 val2)
{
	if (val1 == val2) return;

	// Else Log the error
	fFailed = true;

	UnittestFailObject test;
	test.fMessage += check;
	test.fMessage += "Aspected: ";
	test.fMessage += std::to_string(val1);
	test.fMessage += " Result: ";
	test.fMessage += std::to_string(val2);

	fFailedTests.push_back(test);
};

void Unittest::checkifEqual(const std::string& check, const double val1, const double val2)
{
	if (val1 == val2) return;

	// Else Log the error
	fFailed = true;

	UnittestFailObject test;
	test.fMessage += check;
	test.fMessage += "Aspected: ";
	test.fMessage += std::to_string(val1);
	test.fMessage += " Result: ";
	test.fMessage += std::to_string(val2);

	fFailedTests.push_back(test);
};

void Unittest::checkifEqual(const std::string& check, const size_t val1, const size_t val2)
{
	if (val1 == val2) return;

	// Else Log the error
	fFailed = true;

	UnittestFailObject test;
	test.fMessage += check;
	test.fMessage += " FAILED";

	fFailedTests.push_back(test);
};

/*
void Unittest::checkifEqual(const std::string& check, const VectorworksMVR::GdtfDefines::DmxValue val1, const VectorworksMVR::GdtfDefines::DmxValue val2)
{
	if (val1 == val2) return;

	// Else Log the error
	fFailed = true;

	UnittestFailObject test;
	test.fMessage += check;
	test.fMessage += "Aspected: ";
	test.fMessage += std::to_string(val1);
	test.fMessage += " Result: ";
	test.fMessage += std::to_string(val2);

	fFailedTests.push_back(test);
};

void Unittest::checkifEqual(const std::string& check, const VectorworksMVR::GdtfDefines::DMXAddress val1, const VectorworksMVR::GdtfDefines::DMXAddress val2)
{
	if (val1 == val2) return;

	// Else Log the error
	fFailed = true;

	UnittestFailObject test;
	test.fMessage += check;
	test.fMessage += "Aspected: ";
	test.fMessage += std::to_string(val1);
	test.fMessage += " Result: ";
	test.fMessage += std::to_string(val2);

	fFailedTests.push_back(test);
};
*/

void Unittest::checkifEqual(const std::string& check, const VectorworksMVR::GdtfDefines::EGdtfModel_PrimitiveType val1, const VectorworksMVR::GdtfDefines::EGdtfModel_PrimitiveType val2)
{
	if (val1 == val2) return;

	// Else Log the error
	fFailed = true;

	UnittestFailObject test;
	test.fMessage += check;
	test.fMessage += "Aspected: ";
	test.fMessage += std::to_string(val1);
	test.fMessage += " Result: ";
	test.fMessage += std::to_string(val2);

	fFailedTests.push_back(test);
};

void Unittest::checkifEqual(const std::string& check, const std::string& aspected, const std::string& result)
{
	if (aspected == result) return;

	// Else Log the error
	fFailed = true;

	UnittestFailObject test;
	test.fMessage += check;
	test.fMessage += "Aspected: ";
	test.fMessage += aspected;
	test.fMessage += " Result: ";
	test.fMessage += result;

	fFailedTests.push_back(test);

};


bool Unittest::checkVCOM(VectorworksMVR::VCOMError error, const std::string& check)
{
    if(kVCOMError_NoError == error) return true;

    // Else Log the error
    fFailed = true;

    UnittestFailObject test;
    test.fMessage += "VCOM Failed: ";
    test.fMessage += check;
    test.fMessage += " Result: ";
    test.fMessage += error;

    fFailedTests.push_back(test);

    return false;
};

void Unittest::checkifEqual(const std::string& check, void* val1, void* val2)
{
	if (val1 == val2) return;

	// Else Log the error
	fFailed = true;

	UnittestFailObject test;
	test.fMessage += check;
	test.fMessage += "Aspected: ";
	test.fMessage += (Uint64)val1;
	test.fMessage += " Result: ";
	test.fMessage += (Uint64)val1;

	fFailedTests.push_back(test);
};