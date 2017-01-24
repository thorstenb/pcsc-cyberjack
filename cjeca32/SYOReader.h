#ifndef SYOREADER_H
#define SYOREADER_H

#include "EC30Reader.h"

class CSYOReader :
	public CEC30Reader
{
public:
	CSYOReader(CReader *Owner,CBaseCommunication *Communicator);
	virtual ~CSYOReader(void);
	virtual CJ_RESULT CtSetContrast(EContrast eContrast,uint32_t *Result);
	virtual RSCT_IFD_RESULT _IfdTransmit(const uint8_t *cmd, uint16_t cmd_len,uint8_t *response,uint16_t *response_len,uint8_t Slot=0);	


protected:
	virtual uint16_t HostToReaderShort(uint16_t Value);
	virtual uint32_t HostToReaderLong(uint32_t Value);
	virtual void SetHWString(char *String);
	virtual void GetProductString(uint8_t *Product);

};

#endif

