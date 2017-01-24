#ifndef RFUREADER_H
#define RFUREADER_H

#include "RFSReader.h"

class CRFUReader :
	public CRFSReader
{
public:
	CRFUReader(CReader *Owner,CBaseCommunication *Communicator);
	virtual ~CRFUReader(void);
  virtual RSCT_IFD_RESULT IfdVendor(uint32_t IoCtrlCode,uint8_t *Input,uint32_t InputLength,uint8_t *Output,uint32_t *OutputLength);
	virtual CJ_RESULT BuildReaderInfo();
	
	virtual void SetHWString(char *String);
	virtual void GetProductString(uint8_t *Product);
	virtual CJ_RESULT CtSetBacklight(EBacklight eBacklight,uint32_t *Result);	
  virtual cj_ModuleInfo *FindModule(uint32_t ModuleID);

};

#endif

