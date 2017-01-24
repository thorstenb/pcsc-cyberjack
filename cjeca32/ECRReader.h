#ifndef ECRREADER_H
#define ECRREADER_H

#include "ECPReader.h"

class CECRReader :
	virtual public CECPReader
{
public:
	CECRReader(CReader *Owner,CBaseCommunication *Communicator);
	virtual ~CECRReader(void);
	
	virtual void SetHWString(char *String);
	virtual void GetProductString(uint8_t *Product);

protected:
	virtual RSCT_IFD_RESULT _IfdPower(uint32_t Mode, uint8_t *ATR, uint32_t *ATR_Length, uint32_t Timeout,uint8_t Slot=0);
	virtual RSCT_IFD_RESULT IfdSetProtocol(uint32_t *Protocol,uint8_t Slot=0);
	virtual RSCT_IFD_RESULT _IfdTransmit(const uint8_t *cmd, uint16_t cmd_len,uint8_t *response,uint16_t *response_len,uint8_t Slot=0);	
   virtual RSCT_IFD_RESULT IfdVendor(uint32_t IoCtrlCode,uint8_t *Input,uint32_t InputLength,uint8_t *Output,uint32_t *OutputLength);
	virtual CJ_RESULT BuildReaderInfo();
	virtual uint32_t GetReadersInputBufferSize();
};

#endif

