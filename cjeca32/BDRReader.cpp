#include "Platform.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "BDRReader.h"
#include "BaseCommunication.h"

#include "memory_placements.h"


#define base CWAVReader

CBDRReader::CBDRReader(CReader *Owner,CBaseCommunication *Communicator)
			  :base(Owner,Communicator)
{
}

CBDRReader::~CBDRReader(void)
{ 
}

void CBDRReader::SetHWString(char *String)
{
   strcpy(String,"BDR_");
}

void CBDRReader::GetProductString(uint8_t *Product)
{
	memcpy(Product,"CJBDR",5);
}

