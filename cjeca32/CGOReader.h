#ifndef CGOREADER_H
#define CGOREADER_H

#include "EC30Reader.h"

class CCGOReader :
	public CEC30Reader
{
public:
	CCGOReader(CReader *Owner,CBaseCommunication *Communicator);
	virtual ~CCGOReader(void);
	virtual CJ_RESULT CtSetContrast(EContrast eContrast,uint32_t *Result);


protected:
	virtual uint16_t HostToReaderShort(uint16_t Value);
	virtual uint32_t HostToReaderLong(uint32_t Value);
	virtual void SetHWString(char *String);
	virtual void GetProductString(uint8_t *Product);
	virtual bool HastModulestoreInfo();
	virtual CJ_RESULT CtSetBacklight(EBacklight eBacklight,uint32_t *Result);	
	virtual CJ_RESULT CtSetSilentMode(bool boolMode,bool *pboolMode,uint32_t *Result);
	virtual CJ_RESULT CtGetSilentMode(bool *pboolMode,uint32_t *Result);
	virtual CJ_RESULT SpecialLess3_0_41();
	virtual bool PinDirectSupported();



};

#endif

