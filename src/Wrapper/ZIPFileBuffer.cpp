#include "Prefix/StdAfx.h"

#include "ZIPFileBuffer.h"

#ifdef _LINUX
#include <unistd.h>
#include <stdio.h>
#endif

using namespace VectorworksMVR::Filing;

ZIPFileBuffer::ZIPFileBuffer()
{
	fpZIPFileBuffer		= NULL;
	fZIPFileBufferSize	= 0;
}

ZIPFileBuffer::~ZIPFileBuffer()
{
	if (fpZIPFileBuffer)
		delete[] fpZIPFileBuffer;
	fpZIPFileBuffer = NULL;
}

VCOMError ZIPFileBuffer::Open(VectorworksMVR::Filing::IFileIdentifier* pFileID, bool openForRead)
{
	fOpenForRead   = openForRead;
	fpOpenedFileID = pFileID;
	if (fOpenForRead)
	{
		// prepare file
		IRawOSFilePtr file(IID_RawOSFile);

		// open file
		file->Open(pFileID, true, false, false, false);

		// get filesize
		file->GetFileSize(fZIPFileBufferSize);

		// load in buffer
		fpZIPFileBuffer = new Uint8[fZIPFileBufferSize];
		file->Read(0, fZIPFileBufferSize, fpZIPFileBuffer);

		// close file
		file->Close();
	}

	return kVCOMError_NoError ;
}

VCOMError ZIPFileBuffer::Close()
{
	if (!fOpenForRead && fpZIPFileBuffer)
	{
		// prepare file
		IRawOSFilePtr file(IID_RawOSFile);

		// open file
		file->Open(fpOpenedFileID, true, true, true, true);

		file->Write(0, fZIPFileBufferSize, fpZIPFileBuffer);

		// close file
		file->Close();
	}

	return kVCOMError_NoError;
}

VCOMError ZIPFileBuffer::GetFileSize(Uint64& outValue)
{
	outValue = fZIPFileBufferSize;
	return kVCOMError_NoError;
}

VCOMError ZIPFileBuffer::Read(Uint64 position, Uint64& inoutSize, void* pOutBuffer)
{
	memcpy(pOutBuffer, fpZIPFileBuffer + position, inoutSize);
	return kVCOMError_NoError;
}

VCOMError ZIPFileBuffer::Write(Uint64 position, Uint64 size, const void* pBuffer)
{
	Uint8* tempBuffer = new Uint8[fZIPFileBufferSize + size];

	memcpy(tempBuffer, fpZIPFileBuffer, fZIPFileBufferSize);

	memcpy(tempBuffer + sizeof(Uint8) * fZIPFileBufferSize, pBuffer, size);

	fZIPFileBufferSize += size;

	delete[] fpZIPFileBuffer;

	fpZIPFileBuffer = new Uint8[fZIPFileBufferSize];
	memcpy(fpZIPFileBuffer, tempBuffer, fZIPFileBufferSize);

	if (tempBuffer)
		delete[] tempBuffer;

	return kVCOMError_NoError;
}

