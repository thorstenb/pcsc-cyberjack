#ifndef BDRREADER_H
#define BDRREADER_H

#include "WAVReader.h"

class CBDRReader :
	public CWAVReader
{
public:
	CBDRReader(CReader *Owner,CBaseCommunication *Communicator);
	virtual ~CBDRReader(void);
	
	virtual void SetHWString(char *String);
	virtual void GetProductString(uint8_t *Product);
};

#endif