#include "Platform.h"
#include <string.h>
#include <stdio.h>
#include "SISReader.h"
#include "BaseCommunication.h"

#define base CEC30Reader

CSISReader::CSISReader(CReader *Owner,CBaseCommunication *Communicator)
			  :base(Owner,Communicator)
{
}

CSISReader::~CSISReader(void)
{
}


uint16_t CSISReader::HostToReaderShort(uint16_t Value)
{
   return InversByteOrderShort(htons(Value));
}

uint32_t CSISReader::HostToReaderLong(uint32_t Value)
{
   return InversByteOrderLong(htonl(Value));
}

void CSISReader::SetHWString(char *String)
{
   strcpy(String,"SIS_");
}

void CSISReader::GetProductString(uint8_t *Product)
{
	memcpy(Product,"CJSIS",5);
}

CJ_RESULT CSISReader::CtSetContrast(EContrast eContrast, uint32_t *Result)
{
	CJ_RESULT Res;
	switch (eContrast)
	{
	case ContrastVeryLow:
		Res = _CtSetContrast(0, Result);
		break;
	case ContrastLow:
		Res = _CtSetContrast(70, Result);
		break;
	case ContrastMedium:
		Res = _CtSetContrast(120, Result);
		break;
	case ContrastHigh:
		Res = _CtSetContrast(160, Result);
		break;
	case ContrastVeryHigh:
		Res = _CtSetContrast(255, Result);
		break;
	default:
		Res = CJ_ERR_WRONG_PARAMETER;
	}
	return Res;
}


CJ_RESULT CSISReader::CtSetBacklight(EBacklight eBacklight, uint32_t *Result)
{
	CJ_RESULT Res;
	switch (eBacklight)
	{
	case BacklightOff:
		Res = _CtSetBacklight(0, Result);
		break;
	case BacklightVeryLow:
		Res = _CtSetBacklight(70, Result);
		break;
	case BacklightLow:
		Res = _CtSetBacklight(100, Result);
		break;
	case BacklightMedium:
		Res = _CtSetBacklight(120, Result);
		break;
	case BacklightHigh:
		Res = _CtSetBacklight(160, Result);
		break;
	case BacklightVeryHigh:
		Res = _CtSetBacklight(255, Result);
		break;
	default:
		Res = CJ_ERR_WRONG_PARAMETER;
	}
	return Res;
}


