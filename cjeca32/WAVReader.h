#ifndef WAVEREADER_H
#define WAVEREADER_H

#include "RFSReader.h"

class CWAVReader :
	public CRFSReader
{
public:
	CWAVReader(CReader *Owner,CBaseCommunication *Communicator);
	virtual ~CWAVReader(void);
	
	virtual void SetHWString(char *String);
	virtual void GetProductString(uint8_t *Product);
	virtual CJ_RESULT CtSetBacklight(EBacklight eBacklight,uint32_t *Result);	
//	virtual CJ_RESULT CtSelfTest2(const uint8_t *TransportKey,uint8_t KeyNr);
protected:
  virtual cj_ModuleInfo *FindModule(uint32_t ModuleID);
	virtual cj_ModuleInfo *FindModuleWithMask(uint32_t ModuleID,uint32_t Mask);
	virtual bool ATRFilter(bool IsWarm,uint8_t Slot=0);
	virtual void CompressModifyStructure(CCID_Message& Message);

};

#endif
