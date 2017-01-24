#include "Platform.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "RFSoliReader.h"
#include "BaseCommunication.h"

#include "memory_placements.h"


#define base CRFSReader

CRFSoliReader::CRFSoliReader(CReader *Owner,CBaseCommunication *Communicator)
			  :base(Owner,Communicator)
{
	m_maxSlot=2;
}

CRFSoliReader::~CRFSoliReader(void)
{
}

void CRFSoliReader::SetHWString(char *String)
{
   strcpy(String,"SOL_");
}

void CRFSoliReader::GetProductString(uint8_t *Product)
{
	memcpy(Product,"CJSOL",5);
}

CJ_RESULT CRFSoliReader::CtSetBacklight(EBacklight eBacklight,uint32_t *Result)
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

RSCT_IFD_RESULT CRFSoliReader::IfdVendor(uint32_t IoCtrlCode,uint8_t *Input,uint32_t InputLength,uint8_t *Output,uint32_t *OutputLength)
{
	switch(IoCtrlCode)
	{
	case CJPCSC_VEN_IOCTRL_EXECUTE_PACE:
		return CECPReader::IfdVendor(IoCtrlCode,Input,InputLength,Output,OutputLength);
	default:
	   return base::IfdVendor(IoCtrlCode,Input,InputLength,Output,OutputLength);
	}
}

CJ_RESULT CRFSoliReader::BuildReaderInfo()
{
	CJ_RESULT Res;
	uint8_t disablesync=0;
	uint32_t Result;

	Res = CECPReader::BuildReaderInfo();

	

	m_ReaderInfo.HardwareMask |=	RSCT_READER_HARDWARE_MASK_RFID
		                          | RSCT_READER_HARDWARE_MASK_ICC2 ;

	return Res;
}

cj_ModuleInfo *CRFSoliReader::FindModule(uint32_t ModuleID)
{
	if(ModuleID==MODULE_ID_MKT_COMP)
		return FindModule(MODULE_ID_KERNEL);
	else
		return CBaseReader::FindModule(ModuleID);
}

int CRFSoliReader::cjccid_SecureMV(uint8_t Timeout,
                    uint8_t PinPosition,uint8_t PinType,
                    uint8_t PinLengthSize,uint8_t PinLength,
                    uint8_t PinLengthPosition,
                    uint8_t Min, uint8_t Max,
                    uint8_t bConfirmPIN,
                    uint8_t Condition,uint8_t *Prologue,
                    uint8_t OffsetOld,uint8_t OffsetNew,
                    uint8_t *out,int out_len,uint8_t *in,int *in_len,int TextCount,uint8_t *Text[3],uint8_t Textlen[3],uint8_t bMessageIndex[3],uint8_t bNumberMessage,uint8_t *pDiversifier,uint8_t Slot)
{
	if(Max>15)
		Max=15;
	if(pDiversifier==NULL)
	{
		return CEC30Reader::cjccid_SecureMV(Timeout,PinPosition,PinType,PinLengthSize,PinLength,
											  PinLengthPosition,Min,Max,bConfirmPIN,Condition,Prologue,OffsetOld,OffsetNew,
											  out,out_len,in,in_len,TextCount,Text,Textlen,bMessageIndex,bNumberMessage,pDiversifier,Slot);
	}
	else
	{
		uint32_t Result;
		uint8_t RespData[1000];
		uint8_t buffer[1000];
		uint32_t RespDataLen=sizeof(RespData);
		uint8_t *ptr;
		struct _CCID_Message::_Data::_Secure *Secure;
		uint8_t Error;
		uint32_t ErrorLength=sizeof(Error);
		int i;
   	int Res;
		uint32_t len=0;

		for(i=0,ptr=buffer;i<TextCount;i++)
		{
			*ptr++=Textlen[i];
			memcpy(ptr,Text[i],Textlen[i]);
			ptr+=Textlen[i];
			len+=Textlen[i];
		}
		for(;i<3;i++)
		{
			*ptr++=0;
		}

		*ptr++=4;
		memcpy(ptr,pDiversifier,4);
		ptr+=4;

		

		Secure=(struct _CCID_Message::_Data::_Secure *)ptr;
	

		Secure->bPINOperation=1;
		Secure->bTimeOut=Timeout;
		Secure->bmFormatString=(uint8_t)(0x80 | (PinPosition<<3) | PinType);
		Secure->bmPINBlockString=(uint8_t)((PinLengthSize<<4) | PinLength);
		Secure->bmPINLengthFormat=PinLengthPosition;
		Secure->Data.Modify.bInsertionOffsetOld=OffsetOld;
		Secure->Data.Modify.bInsertionOffsetNew=OffsetNew;
		Secure->Data.Modify.wPINMaxExtraDigit=HostToReaderShort((((uint16_t)Min)<<8)+Max);
		Secure->Data.Modify.bConfirmPIN= bConfirmPIN;
		Secure->Data.Modify.bEntryValidationCondition=Condition;
		Secure->Data.Modify.bNumberMessage=bNumberMessage;
		Secure->Data.Modify.wLangId=HostToReaderShort(0x0409);
		Secure->Data.Modify.bMsgIndex1=bMessageIndex[0];
		Secure->Data.Modify.bMsgIndex2=bMessageIndex[1];
		Secure->Data.Modify.bMsgIndex3=bMessageIndex[2];
		memcpy(Secure->Data.Modify.bTeoPrologue,Prologue,3);
		memcpy(Secure->Data.Modify.abData,out,out_len);
#ifdef _INSERT_KEY_EVENTS
		{
			uint8_t buffer[2];
			buffer[0]=RDR_TO_PC_KEYEVENT;
			buffer[1]=0xa0;
			DoInterruptCallback(buffer,2);
		}
#endif
		Res=CtApplicationData(MODULE_ID_MKT_COMP,2,buffer,20+out_len+len+8,&Result,RespData,&RespDataLen,&Error,&ErrorLength,Slot);

	#ifdef _INSERT_KEY_EVENTS
		if(Res==CJ_SUCCESS)
		{
			if(m_p_Slot[Slot].m_ReaderState==SCARD_SPECIFIC)
			{
				uint8_t buffer[2];
				buffer[0]=RDR_TO_PC_KEYEVENT;
			   if(ErrorLength==1 && Error==PIN_CANCELED)
					buffer[1]=0x01;
				else 
					buffer[1]=0x02;
				DoInterruptCallback(buffer,2);
			}
		}
		{
			uint8_t buffer[2];
			buffer[0]=RDR_TO_PC_KEYEVENT;
			buffer[1]=0xa1;
			DoInterruptCallback(buffer,2);
		}
	#endif
		if(Res!=0)
			return Res;
		return ExecuteApplSecureResult(Error,ErrorLength,in,in_len,RespData,RespDataLen,5,Slot);
	}
}

bool CRFSoliReader::HasDiversifier()
{
	return true;
}

