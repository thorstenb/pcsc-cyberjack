#ifndef CJBINGO_H
#define CJBINGO_H

typedef enum 
{
	RNDG_SUCCESS,
	RNDG_TIMEOUT,
	RNDG_ABORT,
	RNDG_COMMUNICATION_ERROR,
	RNDG_EXT_ERROR,
	RNDG_PROTOCOL_ERROR,
	RNDG_READER_NOT_FOUND,
	RNDG_READER_BUSY,
	RNDG_READER_NOT_CONNECTED
}RNDG_RESULT;

/*Initialisation of the RND-Generator API and connecting the Device*/
RNDG_RESULT RNDGeneratorInit(uint16_t port); 

/*Disconnecting the Device and closing the API */
RNDG_RESULT RNDGeneratorClose(void);

/*Getting extended error information, if a function returns with RNDG_EXT_ERROR*/
uint32_t RNDGetLastError(void);



/*Checking the authentication of the random generator
In the first release the signature will be a cryptogram calculated by the device as 3DES_ENC(RND_IFD). The synchrones 3DES - key has to be stored in a secure environment. In later releases the signature can be calculated with RSA2048 by the security - module (the signature card).*/
RNDG_RESULT RNDGeneratorInternalAutheticate(uint64_t RND_IFD, uint8_t *Signuture);

/*Generation of the random numbers.
In future releases the numbers can be secured by a cryptogram or a signature and additionally encrypted*/
RNDG_RESULT RNDGeneratorGenerateRND(int count,uint64_t *RNDs);

/*Showing the last generated numbers on the display of the device*/
RNDG_RESULT RNDGeneratorShowLastRNDs(void);



#endif
