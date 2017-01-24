#include "Platform.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "RFUReader.h"
#include "BaseCommunication.h"

#include "memory_placements.h"


#define base CRFSReader

CRFUReader::CRFUReader(CReader *Owner,CBaseCommunication *Communicator)
			  :base(Owner,Communicator)
{
	m_maxSlot=2;
}

CRFUReader::~CRFUReader(void)
{
}

void CRFUReader::SetHWString(char *String)
{
   strcpy(String,"RFU_");
}

void CRFUReader::GetProductString(uint8_t *Product)
{
	memcpy(Product,"CJRFU",5);
}

CJ_RESULT CRFUReader::CtSetBacklight(EBacklight eBacklight,uint32_t *Result)
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

RSCT_IFD_RESULT CRFUReader::IfdVendor(uint32_t IoCtrlCode,uint8_t *Input,uint32_t InputLength,uint8_t *Output,uint32_t *OutputLength)
{
	switch(IoCtrlCode)
	{
	case CJPCSC_VEN_IOCTRL_EXECUTE_PACE:
		return CECPReader::IfdVendor(IoCtrlCode,Input,InputLength,Output,OutputLength);
	default:
	   return base::IfdVendor(IoCtrlCode,Input,InputLength,Output,OutputLength);
	}
}

CJ_RESULT CRFUReader::BuildReaderInfo()
{
	CJ_RESULT Res;
	uint8_t disablesync=0;
	uint32_t Result;

	Res = CECPReader::BuildReaderInfo();

	

	m_ReaderInfo.HardwareMask |=	RSCT_READER_HARDWARE_MASK_RFID
		                          | RSCT_READER_HARDWARE_MASK_ICC2 ;

	return Res;
}

cj_ModuleInfo *CRFUReader::FindModule(uint32_t ModuleID)
{
	if(ModuleID==MODULE_ID_MKT_COMP)
		return FindModule(MODULE_ID_KERNEL);
	else
		return CBaseReader::FindModule(ModuleID);
}

