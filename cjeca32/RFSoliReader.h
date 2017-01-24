#ifndef RFSOLIREADER_H
#define RFSOLIREADER_H

#include "RFSReader.h"

class CRFSoliReader :
	public CRFSReader
{
public:
	CRFSoliReader(CReader *Owner,CBaseCommunication *Communicator);
	virtual ~CRFSoliReader(void);
  virtual RSCT_IFD_RESULT IfdVendor(uint32_t IoCtrlCode,uint8_t *Input,uint32_t InputLength,uint8_t *Output,uint32_t *OutputLength);
	virtual CJ_RESULT BuildReaderInfo();
	
	virtual void SetHWString(char *String);
	virtual void GetProductString(uint8_t *Product);
	virtual CJ_RESULT CtSetBacklight(EBacklight eBacklight,uint32_t *Result);	
  virtual cj_ModuleInfo *FindModule(uint32_t ModuleID);
	virtual int cjccid_SecureMV(uint8_t Timeout,
                    uint8_t PinPosition,uint8_t PinType,
                    uint8_t PinLengthSize,uint8_t PinLength,
                    uint8_t PinLengthPosition,
                    uint8_t Min, uint8_t Max,
                    uint8_t bConfirmPIN,
                    uint8_t Condition,uint8_t *Prologue,
                    uint8_t OffsetOld,uint8_t OffsetNew,
                    uint8_t *out,int out_len,uint8_t *in,int *in_len,int TextCount,uint8_t *Text[3],uint8_t Textlen[3],uint8_t bMessageIndex[3],uint8_t bNumberMessage,uint8_t *pDiversifier,uint8_t Slot=0);

protected:
		virtual bool HasDiversifier();


};

#endif

