#include "Platform.h"
#include <string.h>
#include <stdio.h>
#include "CGOReader.h"
#include "BaseCommunication.h"

#define base CEC30Reader

CCGOReader::CCGOReader(CReader *Owner,CBaseCommunication *Communicator)
			  :base(Owner,Communicator)
{
}

CCGOReader::~CCGOReader(void)
{
}

uint16_t CCGOReader::HostToReaderShort(uint16_t Value)
{
   return InversByteOrderShort(htons(Value));
}

uint32_t CCGOReader::HostToReaderLong(uint32_t Value)
{
   return InversByteOrderLong(htonl(Value));
}



void CCGOReader::SetHWString(char *String)
{
   strcpy(String,"CGO_");
}

void CCGOReader::GetProductString(uint8_t *Product)
{
	memcpy(Product,"CJ-GO",5);
}


CJ_RESULT CCGOReader::CtSetContrast(EContrast eContrast,uint32_t *Result)
{
	CJ_RESULT Res;
	switch(eContrast)
	{
	case ContrastVeryLow:
		Res=_CtSetContrast(0,Result);
		break;
	case ContrastLow:
		Res=_CtSetContrast(70,Result);
		break;
	case ContrastMedium:
		Res=_CtSetContrast(120,Result);
		break;
	case ContrastHigh:
		Res=_CtSetContrast(160,Result);
		break;
	case ContrastVeryHigh:
		Res=_CtSetContrast(255,Result);
		break;
	default:
		Res=CJ_ERR_WRONG_PARAMETER;
	}
	return Res;
}


CJ_RESULT CCGOReader::CtSetBacklight(EBacklight eBacklight,uint32_t *Result)
{
	CJ_RESULT Res;
	switch(eBacklight)
	{
	case BacklightOff:
		Res=_CtSetBacklight(0,Result);
		break;
	case BacklightVeryLow:
		Res=_CtSetBacklight(70,Result);
		break;
	case BacklightLow:
		Res=_CtSetBacklight(100,Result);
		break;
	case BacklightMedium:
		Res=_CtSetBacklight(120,Result);
		break;
	case BacklightHigh:
		Res=_CtSetBacklight(160,Result);
		break;
	case BacklightVeryHigh:
		Res=_CtSetBacklight(255,Result);
		break;
	default:
		Res=CJ_ERR_WRONG_PARAMETER;
	}
	return Res;
}

bool CCGOReader::HastModulestoreInfo()
{
	return true;
}

CJ_RESULT CCGOReader::CtSetSilentMode(bool boolMode,bool *pboolMode,uint32_t *Result)
{
	if(pboolMode)
		*pboolMode=boolMode;
  if(Result)
		*Result=0;
	return CJ_SUCCESS;
}

CJ_RESULT CCGOReader::CtGetSilentMode(bool *pboolMode,uint32_t *Result)
{
	if(pboolMode)
		*pboolMode=0;
  if(Result)
		*Result=0;
	return CJ_SUCCESS;
}

CJ_RESULT CCGOReader::SpecialLess3_0_41()
{
	return CJ_SUCCESS;
}

bool CCGOReader::PinDirectSupported()
{
	return true;
}
