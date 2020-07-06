import sys
import os.path
import urllib
import zipfile

print("Building Xerces-c-lib")

XERCES_VERSION = "3.2.2"
XERCES_ZIP_FILE = "shared/xerces-c-" + XERCES_VERSION + ".zip"
XERCES_DIR_PATH = "shared/xerces-c-" + XERCES_VERSION



# check for other system lib file (.lib [for windows])
if not os.path.isfile("shared/lib/libxerces-c.a"):
    print ("===============================================================")
    print ("= M A K E   X e r c e s - C                                   =")
    print ("===============================================================")
    if not os.path.isfile(XERCES_ZIP_FILE):
        print("Downloading xerces")
        urllib.urlretrieve("http://archive.apache.org/dist/xerces/c/3/sources/xerces-c-" + XERCES_VERSION + ".zip", XERCES_ZIP_FILE)
    if not os.path.isdir("shared/xerces"):
        with zipfile.ZipFile(XERCES_ZIP_FILE, 'r') as zip_ref:
            zip_ref.extractall("shared")
            os.rename(XERCES_DIR_PATH, "shared/xerces")

    os.chdir("shared/xerces")

    extraCmakeOptions = "";
    if sys.platform == "win32":
        if not os.path.isdir("build"):
            os.mkdir("build")
        os.chdir("build")

        extraCmakeOptions += "-Dxmlch-type=wchar_t"
        os.system("cmake -DBUILD_SHARED_LIBS:BOOL=OFF -DCMAKE_INSTALL_PREFIX:PATH=libs "+ extraCmakeOptions +" ..")
        os.system("cmake --build . --target install")
    #we need some more cases for linux and should check all configure-options
    if sys.platform == "darwin":
        os.system("./configure --enable-transcoder-gnuiconv --enable-transcoder-macosunicodeconverter")
        os.system("make")
        os.system("make install")

    