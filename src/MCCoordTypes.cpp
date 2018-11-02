//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//	
//	Declares most of the standard geometric data types used
//	in MiniCAD code. This includes all WorldCoord related types.
//
#include "Prefix/StdAfx.h"
#include "MCCoordTypes.h"

const extern double kNearlyEqualEpsilonForWorldCoords = 1e-13;
const extern WorldCoord kMaxLegalWorldCoord = 1.0E100;
const extern WorldCoord kMaxOutOfRangeWorldCoord = DBL_MAX;