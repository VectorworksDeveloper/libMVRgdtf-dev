//-----------------------------------------------------------------------------
//----- Copyright MVR Group 
//-----------------------------------------------------------------------------namespace LightRightNetwork
#include "mvrxchange_prefix.h"

using namespace MVRxchangeNetwork;


MVRxchangeMessage::MVRxchangeMessage()
{
    fReferenceCount = new size_t(1);
    fBodyLength = 0;
}

MVRxchangeMessage::MVRxchangeMessage(const MVRxchangeMessage& ref)
{
    fBodyLength = ref.fBodyLength;
    fdata       = ref.fdata;

    fReferenceCount = ref.fReferenceCount;
	
	// Increase reference Count by one
	(*fReferenceCount)++;
}


MVRxchangeMessage::~MVRxchangeMessage()
{
    (*fReferenceCount)--;
    if (*fReferenceCount == 0)
	{
		// Release pointer
		delete fData;
		
		// Release reference pointer
		delete fReferenceCount;
	}
   
}

const char* MVRxchangeMessage::GetData() const
{
    return fData->GetData();
}

char* MVRxchangeMessage::GetData()
{
    return fData->GetData();
}

size_t MVRxchangeMessage::GetLength() const
{
    return total_header_length + fBodyLength;
}

const char* MVRxchangeMessage::GetBody() const
{
    return fData + total_header_length;
}

char* MVRxchangeMessage::GetBody()
{
    return fData + total_header_length;
}

size_t MVRxchangeMessage::GetBodyLength() const
{
    return fBodyLength;
}

void MVRxchangeMessage::SetBody(, size_t length, char* buffer)
{
    fBodyLength = length;
    fdata->GrowTo(total_header_length + length);
    memcpy(GetBody(), buffer, length);
}

bool MVRxchangeMessage::DecodeHeader()
{
    memcpy(&fFlag, fdata, header_flag);
    if (fFlag != kMVR_Package_Flag) { return false; }

    memcpy(&fVersion,    fdata + header_flag, header_version);
    memcpy(&fNumber,     fdata + header_flag + header_version, header_number);
    memcpy(&fCount,      fdata + header_flag + header_version + header_number, header_count);
    memcpy(&fType,       fdata + header_flag + header_version + header_number + header_count, header_type);
    memcpy(&fBodyLength, fdata + header_flag + header_version + header_number + header_type, header_payload_length);

    // Prepare Buffer
    fdata->GrowTo(fBodyLength);

    return true;
}

void MVRxchangeMessage::EncodeHeader()
{
    memcpy(fdata,                                                                               &fFlag,                 header_flag);
    memcpy(fdata + header_flag,                                                                 &fVersion,              header_version);
    memcpy(fdata + header_flag + header_version,                                                &fNumber,               header_number);
    memcpy(fdata + header_flag + header_version + header_number,                                &fCount,                header_count);
    memcpy(fdata + header_flag + header_version + header_number + header_count,                 &fType,                 header_type);
    memcpy(fdata + header_flag + header_version + header_number + header_count + header_type,   &fBodyLength,           header_payload_length);
}