//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
#include "Prefix/StdAfx.h"
#include "RGBColor.h"

using namespace VWFC::Tools;

CRGBColor::CRGBColor()
{
	this->red		= 0;
	this->green		= 0;
	this->blue		= 0;
}

CRGBColor::CRGBColor(Uint8 r, Uint8 g, Uint8 b)
{
	this->red		= (r << 8) | r;
	this->green		= (g << 8) | g;
	this->blue		= (b << 8) | b;
}

CRGBColor::CRGBColor(const CRGBColor& clr)
{
	this->red		= clr.red;
	this->green		= clr.green;
	this->blue		= clr.blue;
}

// create gradient color from 'leftColor' to 'rightColor' using percentage
// 0% = leftColor; 100% = rightColor
CRGBColor::CRGBColor(const CRGBColor& leftColor, const CRGBColor& rightColor, double dPercent)
{

	Uint8	r	= (Uint8) ( (double)( rightColor.GetRed() - leftColor.GetRed() ) * (dPercent/100) + leftColor.GetRed() );
	Uint8	g	= (Uint8) ( (double)( rightColor.GetGreen() - leftColor.GetGreen() ) * (dPercent/100) + leftColor.GetGreen() );
	Uint8	b	= (Uint8) ( (double)( rightColor.GetBlue() - leftColor.GetBlue() ) * (dPercent/100) + leftColor.GetBlue() );

	this->SetColor( r, g, b );
}

CRGBColor::~CRGBColor()
{
}

CRGBColor& CRGBColor::operator=(const CRGBColor& clr)
{
	this->red		= clr.red;
	this->green		= clr.green;
	this->blue		= clr.blue;
	return *this;
}

bool CRGBColor::operator==(const CRGBColor& clr) const
{
	return
		this->red == clr.red &&
		this->green == clr.green &&
		this->blue == clr.blue ;
}

bool CRGBColor::operator!=(const CRGBColor& clr) const
{
	return ! ( this->operator == ( clr ) );
}

Uint8 CRGBColor::GetRed() const
{
	return (this->red >> 7 >> 1) & 0xFF;
}

void CRGBColor::SetRed(Uint8 red)
{
	this->red		= (red << 8) | red;
}

Uint8 CRGBColor::GetGreen() const
{
	return (this->green >> 7 >> 1) & 0xFF;
}

void CRGBColor::SetGreen(Uint8 green)
{
	this->green		= (green << 8) | green;
}

Uint8 CRGBColor::GetBlue() const
{
	return (this->blue >> 7 >> 1) & 0xFF;
}

void CRGBColor::SetBlue(Uint8 blue)
{
	this->blue		= (blue << 8) | blue;
}

void CRGBColor::GetColor(Uint8& r, Uint8& g, Uint8& b) const
{
	r = this->red >> 7 >> 1;
	g = this->green >> 7 >> 1;
	b = this->blue >> 7 >> 1;
}

void CRGBColor::SetColor(Uint8 r, Uint8 g, Uint8 b)
{
	this->red		= (r << 8) | r;
	this->green		= (g << 8) | g;
	this->blue		= (b << 8) | b;
}
