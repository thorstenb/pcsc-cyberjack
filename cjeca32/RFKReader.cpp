#include "Platform.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "RFKReader.h"
#include "BaseCommunication.h"

#include "memory_placements.h"


#define base CRFSReader

CRFKReader::CRFKReader(CReader *Owner,CBaseCommunication *Communicator)
			  :base(Owner,Communicator)
{}

CRFKReader::~CRFKReader(void)
{
}

void CRFKReader::SetHWString(char *String)
{
   strcpy(String,"RFK_");
}

void CRFKReader::GetProductString(uint8_t *Product)
{
	memcpy(Product,"CJRFK",5);
}

CJ_RESULT CRFKReader::CtSetBacklight(EBacklight eBacklight,uint32_t *Result)
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

CJ_RESULT CRFKReader::CtSelfTest2(const uint8_t *TransportKey,uint8_t KeyNr)
{
	uint32_t Res;
	uint8_t buffer[256];
	struct _CCID_Message::_Data::_Escape::_Reader::_EC30::_Data::_SetDateTime *DateTime=(struct _CCID_Message::_Data::_Escape::_Reader::_EC30::_Data::_SetDateTime *)buffer;
   struct tm *t;
   time_t tim;
	 CJ_RESULT Result;

   time(&tim);
   t=localtime(&tim);

	 DateTime->Nr=1;
   sprintf((char *)DateTime->dtDate.ProductionDate,"%02d.%02d.%04d",t->tm_mday,t->tm_mon+1,t->tm_year+1900);
   sprintf((char *)DateTime->dtDate.ProductionTime,"%02d:%02d",t->tm_hour,t->tm_min);
	 memcpy(buffer+sizeof(struct _CCID_Message::_Data::_Escape::_Reader::_EC30::_Data::_SetDateTime),TransportKey,16);
	 buffer[16+sizeof(struct _CCID_Message::_Data::_Escape::_Reader::_EC30::_Data::_SetDateTime)]=KeyNr;

  Result=Escape(MODULE_ID_KERNEL,CCID_ESCAPE_SELF_TEST,buffer,sizeof(struct _CCID_Message::_Data::_Escape::_Reader::_EC30::_Data::_SetDateTime)+17,&Res,0,0);
	if(Result!=CJ_SUCCESS && Result!=CJ_ERR_CHECK_RESULT)
	{
		//m_Owner->DebugLeveled(DEBUG_MASK_COMMUNICATION_ERROR,"Error Selftest");
		return CJ_ERR_DEVICE_LOST;
	}
   return Res;
}

