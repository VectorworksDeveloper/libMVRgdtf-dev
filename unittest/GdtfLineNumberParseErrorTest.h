//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once
#include "Unittest.h"
#include "GdtfUnittestHandler.h"


class GdtfLineNumberParseErrorTest : public GdtfUnitTest
{
public:
	GdtfLineNumberParseErrorTest(const std::string& currentDir);
	virtual ~GdtfLineNumberParseErrorTest();
protected:
	std::string virtual GetUnitTestName() override;

private:
	std::string fErrorGdtf_Path;

	void virtual WriteFile(VectorworksMVR::IGdtfFixturePtr& fixtureDuringRead) override;
	void virtual ReadFile(VectorworksMVR::IGdtfFixturePtr& fixtureDuringWrite) override;

};