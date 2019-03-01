//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Utility.h"

#include <iostream>
#include <fstream>

#if defined(_WINDOWS)
# include <Shlobj.h>
# include <Shlwapi.h>
#elif GS_LIN
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#elif GS_MAC
#include <stdio.h> 
#endif


std::string UnitTestUtil::GetTestResourceFolder()
{
    return std::string(GITPATH) + kSeparator + "unittest" + kSeparator + "files";
}

bool UnitTestUtil::GetFolderAppDataLocal(std::string& outPath)
{
	//--------------------------------------------------------
	// Implementation for Windows
#ifdef _WINDOWS
    
    // Leave this empty for now
	// Beware, brain-compiled code ahead!
	wchar_t buffer[MAX_PATH];
	HWND hWnd = NULL;
	
	BOOL result = SHGetSpecialFolderPath(hWnd, buffer, CSIDL_LOCAL_APPDATA, false );
	
	if(!result) return false;
    std::wstring ws(buffer);
	outPath = std::string(ws.begin(), ws.end());
    
#elif _LINUX
	// LINUX_IMPLEMENTATION - done
	struct passwd *pw = getpwuid(getuid());

	const char *homedir = pw->pw_dir;
	outPath = std::string(homedir);
#elif GS_MAC
	//Implementation for OSX
	const char *homeDir = getenv("HOME");
	outPath = std::string(homeDir);
#endif	    

	return true;
}

bool UnitTestUtil::FileExists(std::string fullPath)
{
    std::ifstream f(fullPath.c_str());
    return f.good();
}
