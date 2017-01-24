#include "Platform.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "WAVReader.h"
#include "BaseCommunication.h"

#include "memory_placements.h"


#define base CRFSReader

CWAVReader::CWAVReader(CReader *Owner,CBaseCommunication *Communicator)
			  :base(Owner,Communicator)
{
}

CWAVReader::~CWAVReader(void)
{
}

void CWAVReader::SetHWString(char *String)
{
   strcpy(String,"WAV_");
}

bool CWAVReader::ATRFilter(bool IsWarm,uint8_t Slot)
{
	  uint8_t ATRS;
		uint32_t Result;
		uint32_t rlen;
		if(m_p_Slot[Slot].m_ATR_Length>=5)
		{
			if(m_p_Slot[Slot].m_ATR[0]==0x4b)
			{
				m_p_Slot[Slot].m_ATR[0]=0x3b;
				m_p_Slot[Slot].m_bIsRF=true;
				return true;
			}
			rlen=sizeof(ATRS);
			if(Escape(MODULE_ID_KERNEL,CCID_ESCAPE_GET_CARDINFO,NULL,0,&Result,&ATRS,&rlen,Slot)==CJ_SUCCESS)
			{
				if(Result==0 && rlen==1)
				{
					if(ATRS==0x4b)
					{
						m_p_Slot[Slot].m_bIsRF=true;
						return true;
					}
				}
			}
		}
		return CEC30Reader::ATRFilter(IsWarm,Slot);
}



void CWAVReader::GetProductString(uint8_t *Product)
{
	memcpy(Product,"CJWAV",5);
}

CJ_RESULT CWAVReader::CtSetBacklight(EBacklight eBacklight,uint32_t *Result)
{
	CJ_RESULT Res;
	switch(eBacklight)
	{
	//case BacklightOff:
	//	Res=_CtSetBacklight(0,Result);
	//	break;
	//case BacklightVeryLow:
	//	Res=_CtSetBacklight(70,Result);
	//	break;
	//case BacklightLow:
	//	Res=_CtSetBacklight(100,Result);
	//	break;
	//case BacklightMedium:
	//	Res=_CtSetBacklight(120,Result);
	//	break;
	//case BacklightHigh:
	//	Res=_CtSetBacklight(160,Result);
	//	break;
	//case BacklightVeryHigh:
	//	Res=_CtSetBacklight(255,Result);
	//	break;
	default:
		Res=CJ_ERR_WRONG_PARAMETER;
	}
	return Res;
}

//CJ_RESULT CWAVReader::CtSelfTest2(const uint8_t *TransportKey,uint8_t KeyNr)
//{
//	uint32_t Res;
//	uint8_t buffer[256];
//	struct _CCID_Message::_Data::_Escape::_Reader::_EC30::_Data::_SetDateTime *DateTime=(struct _CCID_Message::_Data::_Escape::_Reader::_EC30::_Data::_SetDateTime *)buffer;
//   struct tm *t;
//   time_t tim;
//	 CJ_RESULT Result;
//
//   time(&tim);
//   t=localtime(&tim);
//
//	 DateTime->Nr=1;
//   sprintf((char *)DateTime->dtDate.ProductionDate,"%02d.%02d.%04d",t->tm_mday,t->tm_mon+1,t->tm_year+1900);
//   sprintf((char *)DateTime->dtDate.ProductionTime,"%02d:%02d",t->tm_hour,t->tm_min);
//	 memcpy(buffer+sizeof(struct _CCID_Message::_Data::_Escape::_Reader::_EC30::_Data::_SetDateTime),TransportKey,16);
//	 buffer[16+sizeof(struct _CCID_Message::_Data::_Escape::_Reader::_EC30::_Data::_SetDateTime)]=KeyNr;
//
//  Result=Escape(MODULE_ID_KERNEL,CCID_ESCAPE_SELF_TEST,buffer,sizeof(struct _CCID_Message::_Data::_Escape::_Reader::_EC30::_Data::_SetDateTime)+17,&Res,0,0);
//	if(Result!=CJ_SUCCESS && Result!=CJ_ERR_CHECK_RESULT)
//	{
//		m_Owner->DebugLeveled(DEBUG_MASK_COMMUNICATION_ERROR,"Error Selftest");
//		return CJ_ERR_DEVICE_LOST;
//	}
//   return Res;
//}

cj_ModuleInfo helpModule; 

cj_ModuleInfo *CWAVReader::FindModule(uint32_t ModuleID)
{
	if(ModuleID==MODULE_ID_KT_LIGHT)
	{
		memset(&helpModule,0,sizeof(helpModule));
		return &helpModule;
	}
	return CBaseReader::FindModule(ModuleID);
}

cj_ModuleInfo *CWAVReader::FindModuleWithMask(uint32_t ModuleID,uint32_t Mask)
{
	if(ModuleID==MODULE_ID_KT_LIGHT)
	{
		memset(&helpModule,0,sizeof(helpModule));
		return &helpModule;
	}
	return CBaseReader::FindModuleWithMask(ModuleID,Mask);
}

void CWAVReader::CompressModifyStructure(CCID_Message& Message)
{
	if(m_ReaderInfo.Version>=0x19)
	{
		if(Message.Data.Secure.Data.Modify.bNumberMessage==0)
		{
			memmove(&(Message.Data.Secure.Data.Modify.bMsgIndex2),Message.Data.Secure.Data.Modify.bTeoPrologue,Message.dwLength-17);
			Message.dwLength-=2;
		}
		else if(Message.Data.Secure.Data.Modify.bNumberMessage!=3)
		{
			memmove(&(Message.Data.Secure.Data.Modify.bMsgIndex3),Message.Data.Secure.Data.Modify.bTeoPrologue,Message.dwLength-17);
			Message.dwLength-=1;
		}
	}
}
