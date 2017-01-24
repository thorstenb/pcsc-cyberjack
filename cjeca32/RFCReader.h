#ifndef RFCREADER_H
#define RFCREADER_H

#include "RFSReader.h"

class CRFCReader :
	public CRFSReader
{
public:
	CRFCReader(CReader *Owner,CBaseCommunication *Communicator);
	virtual ~CRFCReader(void);
	virtual void SetHWString(char *String);
	virtual void GetProductString(uint8_t *Product);
	virtual CJ_RESULT CtSetBacklight(EBacklight eBacklight,uint32_t *Result);	
private:

};

#endif