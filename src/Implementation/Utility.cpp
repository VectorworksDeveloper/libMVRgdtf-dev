//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "Utility.h"

/*static*/ void Utility::ConvertMatrix(const VectorworksMVR::STransformMatrix & smatrix, VWTransformMatrix & vwmatrix)
/* 
Converts a STransformMatrix to a VWTransformMatrix.
*/
{
    vwmatrix.fMatrix.mat[0][0] = smatrix.ux; vwmatrix.fMatrix.mat[0][1] = smatrix.uy; vwmatrix.fMatrix.mat[0][2] = smatrix.uz;
    vwmatrix.fMatrix.mat[1][0] = smatrix.vx; vwmatrix.fMatrix.mat[1][1] = smatrix.vy; vwmatrix.fMatrix.mat[1][2] = smatrix.vz;
    vwmatrix.fMatrix.mat[2][0] = smatrix.wx; vwmatrix.fMatrix.mat[2][1] = smatrix.wy; vwmatrix.fMatrix.mat[2][2] = smatrix.wz;
    vwmatrix.fMatrix.mat[3][0] = smatrix.ox; vwmatrix.fMatrix.mat[3][1] = smatrix.oy; vwmatrix.fMatrix.mat[3][2] = smatrix.oz;
}

/*static*/ void Utility::ConvertMatrix(const VWTransformMatrix & vwmatrix, VectorworksMVR::STransformMatrix & smatrix)
/*
Converts a VWTransformMatrix to a STransformMatrix.
*/
{
    smatrix.ux = vwmatrix.fMatrix.mat[0][0]; smatrix.uy = vwmatrix.fMatrix.mat[0][1]; smatrix.uz = vwmatrix.fMatrix.mat[0][2];
    smatrix.vx = vwmatrix.fMatrix.mat[1][0]; smatrix.vy = vwmatrix.fMatrix.mat[1][1]; smatrix.vz = vwmatrix.fMatrix.mat[1][2];
    smatrix.wx = vwmatrix.fMatrix.mat[2][0]; smatrix.wy = vwmatrix.fMatrix.mat[2][1]; smatrix.wz = vwmatrix.fMatrix.mat[2][2];
    smatrix.ox = vwmatrix.fMatrix.mat[3][0]; smatrix.oy = vwmatrix.fMatrix.mat[3][1]; smatrix.oz = vwmatrix.fMatrix.mat[3][2];
}
