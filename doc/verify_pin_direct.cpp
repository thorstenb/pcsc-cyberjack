// Compilieren mit folgender Kommandozeile:
//
//		 g++ -I/usr/include/PCSC verify_pin_direct.cpp -lpcsclite -o verify_pin_direct
// g++ -framework PCSC -I/Users/sct/reinser-sct/5final.SP03/pcsc-cyberjack-3.99.5final.SP03/include/macosx/PCSC  verify_pin_direct.cpp -o verify_pin_direct

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>

#define CALLCONVENTION
#include <PCSC/wintypes.h>
#include <reader.h>

#include <PCSC/pcsclite.h>
#include <PCSC/winscard.h>

int main(int argc, char** argv)
{
	SCARDHANDLE hCard;
	DWORD cardProtocol;
	SCARDCONTEXT hContext;
	long res;
	char *mszReaders;
	DWORD dwReaders = 1000;
	char *mszGroups;
	int numReaders=0;
	int maxNumReaders=10;
	char readerName[maxNumReaders][255];

	res = SCardEstablishContext(SCARD_SCOPE_SYSTEM, NULL, NULL, &hContext);

	if (res != SCARD_S_SUCCESS) {
		printf("Fehler bei sCardEstablishContext: %p\n", (void*)res);
		return -1;
	}

	printf("Testing SCardListReaders\t: ");
	mszGroups = NULL;
	mszReaders = (char *)calloc(dwReaders, sizeof(char));
	res = SCardListReaders(hContext, mszGroups, mszReaders, &dwReaders);
	if (res != SCARD_S_SUCCESS) {
		printf("Fehler bei SCardListReaders: %p\n", (void*)res);
		return -1;
	}
	/*
	 * Have to understand the multi-string here
	 */
	for (int i = 0; i + 1 < dwReaders; i++) {
		printf("Reader %s\n", &mszReaders[i]);
		sprintf(&readerName[numReaders][0],"%s",&mszReaders[i]);
		while (mszReaders[++i] != 0) ;
		numReaders++;
	}


	for (int loopnr = 0; loopnr < numReaders; ++loopnr) {
		int i = 0;
		sleep(1); // es ist egal, ob hier sleep steht, oder nicht, insofern kein Timing-Problem
		//SCARD_SHARE_EXCLUSIVE,

		//"REINER SCT cyberJack pp_a (5475474673) 00 00",
		//"REINER SCT cyberJack ecom_a (1521134321) 00 00",
		if (strstr(&readerName[loopnr][0],"REINER") == NULL ) {
			continue;
		} else {
			printf("found first Reiner");
		}

		printf("using %s\n", &readerName[loopnr][0]);
		res = SCardConnect(hContext,
				   &readerName[loopnr][0],
				   SCARD_SHARE_SHARED,
				   SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1,
				   &hCard,
				   &cardProtocol);

				char buffer[1024] = { 0x02 };
				DWORD cbRecvLength = sizeof(buffer);
		if (res != SCARD_S_SUCCESS) {
			printf("sCardConnect %03d: Fehler %p ****\n", loopnr, (void*)res);
		} else {
			SCARD_IO_REQUEST pioRecvPci;
			SCARD_IO_REQUEST pioSendPci;
			unsigned char bSendBuffer[MAX_BUFFER_SIZE];
			unsigned char bRecvBuffer[MAX_BUFFER_SIZE];
			DWORD send_length, length;
			switch (cardProtocol) {
			case SCARD_PROTOCOL_T0:
				pioSendPci = *SCARD_PCI_T0;
				break;
			case SCARD_PROTOCOL_T1:
				pioSendPci = *SCARD_PCI_T1;
				break;
			case SCARD_PROTOCOL_RAW:
				pioSendPci = *SCARD_PCI_RAW;
				break;
			default:
				printf("Unknown protocol\n");
				return -1;
			}

			/* APDU select file */
			printf("Select file:");
			send_length = 7;
			memcpy(bSendBuffer, "\x00\xA4\x00\x00\x02\x3F\x00", send_length);
			for (i = 0; i < send_length; i++)
				printf(" %02X", bSendBuffer[i]);
			printf("\n");
			length = sizeof(bRecvBuffer);

			printf("Testing SCardTransmit\t\t: ");
			res = SCardTransmit(hCard, &pioSendPci, bSendBuffer, send_length,
					    &pioRecvPci, bRecvBuffer, &length);
			printf("res=%ld\n", res);
			for (i = 0; i < length; i++)
				printf(" %02X", bRecvBuffer[i]);

			sleep(1);

			{
				char buffer[1024] = { 0x02 };
				DWORD cbRecvLength = sizeof(buffer);
				DWORD fr_fmpd = 0;

				printf("\ntesting SCardControl CM_IOCTL_GET_FEATURE_REQUEST\n");
				send_length = 0;
				PCSC_TLV_STRUCTURE *pcsc_tlv = (PCSC_TLV_STRUCTURE *)buffer;
				res = SCardControl(hCard, CM_IOCTL_GET_FEATURE_REQUEST, bSendBuffer, send_length, buffer, sizeof(buffer), &cbRecvLength);
//exit(0);
#if KP_DEBUG
				if (cbRecvLength && (SCARD_S_SUCCESS == res)) {
					for (i = 0; i < cbRecvLength; i++)
						printf("0x%02x ", buffer[i]);
					printf(" ");
				}else  {
					printf("Fehler bei SCardControl: %p\n", (void*)res);
					return 1;
				}
				printf("\n");
#endif
				for (int len = 0; len < cbRecvLength; len++) {
					switch (pcsc_tlv->tag) {
					//case FEATURE_MODIFY_PIN_DIRECT:
						//printf("FEATURE_MODIFY_PIN_DIRECT found\n");
						//printf("pcsc_tlv->value = %08x\n", ntohl(pcsc_tlv->value));
						//fr_fmpd = ntohl(pcsc_tlv->value);
						//break;
					case FEATURE_VERIFY_PIN_DIRECT:
						printf("FEATURE_VERIFY_PIN_DIRECT found\n");
						printf("pcsc_tlv->value = %08x\n", ntohl(pcsc_tlv->value));
						fr_fmpd = ntohl(pcsc_tlv->value);
						break;
					//default:
						//printf("unknown FEATURE found\n");
						//printf("pcsc_tlv->value = %08x\n", ntohl(pcsc_tlv->value));
					}
					pcsc_tlv++;
					len += sizeof(PCSC_TLV_STRUCTURE);
				}


				if (fr_fmpd) {
					printf("\ntesting SCardControl FEATURE_VERIFY_PIN_DIRECT\n");
					send_length = 32;
memcpy(bSendBuffer,"\x00\x00\x89\x47\x04\x08\x04\x02\x00\x00\x00\x00\x00\x00\x00\x0D\x00\x00\x00\x00\x20\x00\x80\x08\x20\xFF\xFF\xFF\xFF\xFF\xFF\xFF", send_length);
					//send_length = 28;
					//memcpy(bSendBuffer, "\x00\x00\x82\x08\x00\x00\x00\x08\x04\x03\x02\x03\x04\x07\x00\x01\x02\x00\x00\x00\x04\x00\x00\x00\x00\x24\x00\x03", send_length);
					for (i = 0; i < send_length; i++)
						printf(" %02X", bSendBuffer[i]);
					printf("\n");
					length = sizeof(bRecvBuffer);

					res = SCardControl(hCard, fr_fmpd, bSendBuffer, send_length, buffer, sizeof(buffer), &cbRecvLength);
					if (cbRecvLength && (SCARD_S_SUCCESS == res)) {
						for (i = 0; i < cbRecvLength; i++)
							//printf("%c", buffer[i]);
							printf("0x%x", buffer[i]);
						printf(" ");
					}else  {
						printf("Fehler bei SCardControl: %p\n", (void*)res);
						return 1;
					}
				}
			}

			SCardDisconnect(hCard, SCARD_RESET_CARD); // ohne diesen disconnect gehen alle Folgeaufrufe schief
		}
	}

	return 0;
}
