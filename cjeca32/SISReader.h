#ifndef SISREADER_H
#define SISREADER_H

#include "EC30Reader.h"

class CSISReader :
	public CEC30Reader
{
public:
	CSISReader(CReader *Owner,CBaseCommunication *Communicator);
	virtual ~CSISReader(void);
	virtual CJ_RESULT CtSetContrast(EContrast eContrast,uint32_t *Result);
	virtual CJ_RESULT CtSetBacklight(EBacklight eBacklight, uint32_t *Result);


protected:
	virtual uint16_t HostToReaderShort(uint16_t Value);
	virtual uint32_t HostToReaderLong(uint32_t Value);
	virtual void SetHWString(char *String);
	virtual void GetProductString(uint8_t *Product);

};

#endif

