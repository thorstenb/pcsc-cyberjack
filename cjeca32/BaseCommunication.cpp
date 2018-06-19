#include "Platform.h"
#include "BaseCommunication.h"
#include <string.h>
#include "Debug.h"

#include "ECAReader.h"
#include "ECBReader.h"
#include "ECRReader.h"
#include "ECPReader.h"
#include "SECReader.h"
#include "SYOReader.h"
#include "ECFReader.h"
#include "ECFReader.h"
#include "EFBReader.h"
#include "PPAReader.h"
#include "RFKReader.h"
#include "RFSReader.h"
#include "CPTReader.h"
#include "CGOReader.h"
#include "WAVReader.h"
#include "RFCReader.h"
#include "RFSoliReader.h"
#include "TLSReader.h"
#include "BDRReader.h"
#include "SHUReader.h"
#include "SISReader.h"
#include "RFUReader.h"






CBaseCommunication::CBaseCommunication(const char *cDeviceName,CReader *Owner)
{
	m_cDeviceName=strdup(cDeviceName);
	m_Owner=Owner;
	m_Reader=NULL;
	m_InterruptPipeState=UnInit;
        m_pid=0;
}


CBaseCommunication::~CBaseCommunication(void)
{
	free(m_cDeviceName);
}

void CBaseCommunication::Close()
{}



int CBaseCommunication::Write(void *Message,uint32_t len)
{
	if(IsConnected())
   {
      Debug.Out(m_cDeviceName,DEBUG_MASK_COMMUNICATION_OUT,"CCID OUT:",Message,len);
	}
      
	return ((!IsConnected())?CJ_ERR_DEVICE_LOST:CJ_SUCCESS);
}

int CBaseCommunication::Read(void *Response,uint32_t *len)
{
   if(IsConnected())
   {
      Debug.Out(m_cDeviceName,DEBUG_MASK_COMMUNICATION_IN,"CCID IN:",Response,*len);
	}
      
	return ((!IsConnected())?CJ_ERR_DEVICE_LOST:CJ_SUCCESS);
}

void CBaseCommunication::FreeIFDHandlerDeviceName(char *DeviceName)
{
	if(DeviceName!=NULL)
	   delete DeviceName;
}



CBaseReader *CBaseCommunication::_buildUsbReaderObject(uint16_t pid, const char *readerName) {
  int len;
  char *ptr;

  len=strlen(readerName);
  ptr=strdup(readerName);

  Debug.varLog(m_cDeviceName, DEBUG_MASK_COMMUNICATION_INFO, "Reader Productstring: [%s]", ptr);

  switch(pid) {
#ifndef _WINDOWS
  case 0x300:
    if (len>=18 && memcmp(ptr, "cyberJack pinpad(a)", 19)==0) {
      ptr[18]='\0';
      m_Reader = new CPPAReader(m_Owner, this);
      Debug.varLog(m_cDeviceName, DEBUG_MASK_COMMUNICATION_INFO,
                   "Recognized device %04x [%s]", pid, ptr);
    }
    else {
      Debug.varLog(m_cDeviceName, DEBUG_MASK_COMMUNICATION_ERROR,
                   "Device [%s] ist not a known cyberJack 0x300, assuming pinpad(a)", ptr);
      m_Reader = new CPPAReader(m_Owner, this);
    }

    m_pid=pid;
    m_productString=ptr;
    free(ptr);
    return m_Reader;
#endif
  case 0x400:
    if (len>=18 && memcmp(ptr, "cyberJack e-com(a)", 18)==0) {
      ptr[18]='\0';
      m_Reader = new CECAReader(m_Owner, this);
      Debug.varLog(m_cDeviceName, DEBUG_MASK_COMMUNICATION_INFO,
             "Recognized device %04x [%s]", pid, ptr);
    }
    else if(len>=24 && memcmp(ptr, "cyberJack e-com plus DUO", 24)==0){
      ptr[24]='\0';
      m_Reader = new CECBReader(m_Owner, this);
      Debug.varLog(m_cDeviceName, DEBUG_MASK_COMMUNICATION_INFO,
             "Recognized device %04x [%s]", pid, ptr);
    }
    else if(len>=24 && memcmp(ptr, "cyberJack e-com plus BIO", 24)==0){
      ptr[24]='\0';
      m_Reader = new CECBReader(m_Owner, this);
      Debug.varLog(m_cDeviceName, DEBUG_MASK_COMMUNICATION_INFO,
             "Recognized device %04x [%s]", pid, ptr);
    }
    else if(len>=25 && memcmp(ptr, "cyberJack e-com plus RFID", 25)==0){
      ptr[25]='\0';
      m_Reader = new CECRReader(m_Owner, this);
      Debug.varLog(m_cDeviceName, DEBUG_MASK_COMMUNICATION_INFO,
             "Recognized device %04x [%s]", pid, ptr);
    }
    else if(len>=20 && memcmp(ptr, "cyberJack e-com plus", 20)==0) {
      ptr[20]='\0';
      m_Reader = new CECPReader(m_Owner, this);
      Debug.varLog(m_cDeviceName, DEBUG_MASK_COMMUNICATION_INFO,
             "Recognized device %04x [%s]", pid, ptr);
    }
    else if(len>=17 && memcmp(ptr, "cyberJack Secoder", 17)==0){
      ptr[17]='\0';
      m_Reader = new CSECReader(m_Owner, this);
      Debug.varLog(m_cDeviceName, DEBUG_MASK_COMMUNICATION_INFO,
             "Recognized device %04x [%s]", pid, ptr);
    }
    else {
      Debug.varLog(m_cDeviceName, DEBUG_MASK_COMMUNICATION_ERROR,
             "Device [%s] ist not a known cyberJack 0x400, assuming e-com(a)", ptr);
      m_Reader = new CECAReader(m_Owner, this);
    }

    m_pid=pid;
    m_productString=ptr;
    free(ptr);
    return m_Reader;
  
  case 0x401:
    if(len>=18 && memcmp(ptr, "cyberJack e-com(f)", 18)==0) {
      ptr[18]='\0';
      m_Reader = new CECFReader(m_Owner, this);
      Debug.varLog(m_cDeviceName, DEBUG_MASK_COMMUNICATION_INFO,
             "Recognized device %04x [%s]", pid, ptr);
    }
    else if (len>=19 && memcmp(ptr, "cyberJack e-com BIO", 19)==0){
      ptr[19]='\0';
      m_Reader = new CEFBReader(m_Owner, this);
      Debug.varLog(m_cDeviceName, DEBUG_MASK_COMMUNICATION_INFO,
             "Recognized device %04x [%s]", pid, ptr);
    }
    else {
      Debug.varLog(m_cDeviceName, DEBUG_MASK_COMMUNICATION_ERROR,
             "Device [%s] ist not a known cyberJack 0x401, assuming e-com(f)", ptr);
      m_Reader=new CECFReader(m_Owner, this);
    }

    m_pid=pid;
    m_productString=ptr;
    free(ptr);
    return m_Reader;

  case 0x0500:
    if (len>=27 && memcmp(ptr, "cyberJack RFID standard HUN", 27)==0) {
      ptr[27]='\0';
      m_Reader = new CSHUReader(m_Owner, this);
      Debug.varLog(m_cDeviceName, DEBUG_MASK_COMMUNICATION_INFO,
             "Recognized device %04x [%s]", pid, ptr);
    } else if (len>=23 && memcmp(ptr, "cyberJack RFID standard", 23)==0) {
      ptr[23]='\0';
      m_Reader = new CRFSReader(m_Owner, this);
      Debug.varLog(m_cDeviceName, DEBUG_MASK_COMMUNICATION_INFO,
             "Recognized device %04x [%s]", pid, ptr);
    } else {
      Debug.varLog(m_cDeviceName, DEBUG_MASK_COMMUNICATION_ERROR,
             "Device [%s] ist not a known cyberJack 0x500, assuming RFID standard", ptr);
      m_Reader = new CRFSReader(m_Owner, this);
    }
    m_pid=pid;
    m_productString=ptr;
    free(ptr);
    return m_Reader;

  case 0x0501:
    if (len>=22 && memcmp(ptr, "cyberJack RFID komfort", 22)==0) {
      ptr[22]='\0';
      m_Reader = new CRFKReader(m_Owner, this);
      Debug.varLog(m_cDeviceName, DEBUG_MASK_COMMUNICATION_INFO,
             "Recognized device %04x [%s]", pid, ptr);
    }
    else {
      Debug.varLog(m_cDeviceName, DEBUG_MASK_COMMUNICATION_ERROR,
             "Device [%s] ist not a known cyberJack 0x501, assuming RFID standard", ptr);
      m_Reader = new CRFSReader(m_Owner, this);
    }
    m_pid=pid;
    m_productString=ptr;
    free(ptr);
    return m_Reader;

  case 0x0502:
    if (len>=17 && memcmp(ptr, "cyberJack compact", 17)==0) {
      ptr[17]='\0';
      m_Reader = new CCPTReader(m_Owner, this);
      Debug.varLog(m_cDeviceName, DEBUG_MASK_COMMUNICATION_INFO,
             "Recognized device %04x [%s]", pid, ptr);
    }
    else {
      Debug.varLog(m_cDeviceName, DEBUG_MASK_COMMUNICATION_ERROR,
             "Device [%s] ist not a known cyberJack 0x502, assuming cyberJack compact", ptr);
      m_Reader = new CCPTReader(m_Owner, this);
    }
    m_pid=pid;
    m_productString=ptr;
    free(ptr);
    return m_Reader;

  case 0x0503:
    if (len>=24 && memcmp(ptr, "cyberJack RFID universal", 24)==0) {
      ptr[24]='\0';
      m_Reader = new CRFUReader(m_Owner, this);
      Debug.varLog(m_cDeviceName, DEBUG_MASK_COMMUNICATION_INFO,
             "Recognized device %04x [%s]", pid, ptr);
    }
    else {
      Debug.varLog(m_cDeviceName, DEBUG_MASK_COMMUNICATION_ERROR,
             "Device [%s] ist not a known cyberJack 0x503, assuming cyberJack RFID universal", ptr);
      m_Reader = new CRFUReader(m_Owner, this);
    }
    m_pid=pid;
    m_productString=ptr;
    free(ptr);
    return m_Reader;

  case 0x0504:
    if (len>=12 && memcmp(ptr, "cyberJack go / go plus", 22)==0) {
      ptr[22]='\0';
      m_Reader = new CCGOReader(m_Owner, this);
      Debug.varLog(m_cDeviceName, DEBUG_MASK_COMMUNICATION_INFO,
             "Recognized device %04x [%s]", pid, ptr);
    }
    else {
      Debug.varLog(m_cDeviceName, DEBUG_MASK_COMMUNICATION_ERROR,
             "Device [%s] ist not a known cyberJack 0x504, assuming cyberjack go / go plus", ptr);
      m_Reader = new CCGOReader(m_Owner, this);
    }
    m_pid=pid;
    m_productString=ptr;
    free(ptr);
    return m_Reader;

  case 0x0580:
    if (len>=12 && memcmp(ptr, "cyberJack one", 13)==0) {
      ptr[13]='\0';
      m_Reader = new CCGOReader(m_Owner, this);
      Debug.varLog(m_cDeviceName, DEBUG_MASK_COMMUNICATION_INFO,
             "Recognized device %04x [%s]", pid, ptr);
    }
    else {
      Debug.varLog(m_cDeviceName, DEBUG_MASK_COMMUNICATION_ERROR,
             "Device [%s] ist not a known cyberJack 0x580, assuming cyberjack one", ptr);
      m_Reader = new CCGOReader(m_Owner, this);
    }
    m_pid=pid;
    m_productString=ptr;
    free(ptr);
    return m_Reader;

  case 0x0505:
    if (len>=13 && memcmp(ptr, "cyberJack wav", 13)==0) {
      ptr[13]='\0';
      m_Reader = new CWAVReader(m_Owner, this);
      Debug.varLog(m_cDeviceName, DEBUG_MASK_COMMUNICATION_INFO,
             "Recognized device %04x [%s]", pid, ptr);
    }
    else {
      Debug.varLog(m_cDeviceName, DEBUG_MASK_COMMUNICATION_ERROR,
             "Device [%s] ist not a known cyberJack 0x505, assuming cyberjack wav", ptr);
      m_Reader = new CWAVReader(m_Owner, this);
    }
    m_pid=pid;
    m_productString=ptr;
    free(ptr);
    return m_Reader;

  case 0x0506:
    if (len>=17 && memcmp(ptr, "cyberJack RFID cv", 17)==0) {
      ptr[17]='\0';
      m_Reader = new CRFCReader(m_Owner, this);
      Debug.varLog(m_cDeviceName, DEBUG_MASK_COMMUNICATION_INFO,
             "Recognized device %04x [%s]", pid, ptr);
    }
    else {
      Debug.varLog(m_cDeviceName, DEBUG_MASK_COMMUNICATION_ERROR,
             "Device [%s] ist not a known cyberJack 0x506, assuming cyberjack RFID cv", ptr);
      m_Reader = new CRFCReader(m_Owner, this);
    }
    m_pid=pid;
    m_productString=ptr;
    free(ptr);
    return m_Reader;

  case 0x0507:
    if (len>=26 && memcmp(ptr, "cyberJack RFID SoliSYSTEMS", 26)==0) {
      ptr[26]='\0';
      m_Reader = new CRFSoliReader(m_Owner, this);
      Debug.varLog(m_cDeviceName, DEBUG_MASK_COMMUNICATION_INFO,
             "Recognized device %04x [%s]", pid, ptr);
    }
    else {
      Debug.varLog(m_cDeviceName, DEBUG_MASK_COMMUNICATION_ERROR,
             "Device [%s] ist not a known cyberJack 0x507, assuming cyberjack RFID SoliSYSTEMS", ptr);
      m_Reader = new CRFSoliReader(m_Owner, this);
    }
    m_pid=pid;
    m_productString=ptr;
    free(ptr);
    return m_Reader;

  case 0x0412:
    if (len>=21 && memcmp(ptr, "cyberJack secoder TLS", 21)==0) {
      ptr[21]='\0';
      m_Reader = new CTLSReader(m_Owner, this);
      Debug.varLog(m_cDeviceName, DEBUG_MASK_COMMUNICATION_INFO,
             "Recognized device %04x [%s]", pid, ptr);
    }
    else {
      Debug.varLog(m_cDeviceName, DEBUG_MASK_COMMUNICATION_ERROR,
             "Device [%s] ist not a known cyberJack 0x412, assuming cyberjack secoder TLS", ptr);
      m_Reader = new CTLSReader(m_Owner, this);
    }
    m_pid=pid;
    m_productString=ptr;
    free(ptr);
    return m_Reader;

  case 0x0485:
    m_Reader = new CSYOReader(m_Owner, this);
    Debug.varLog(m_cDeviceName, DEBUG_MASK_COMMUNICATION_INFO,
           "Recognized device %04x [%s]", pid, ptr);
    m_pid=pid;
    m_productString=ptr;
    free(ptr);
    return m_Reader;

  case 0x0525:
    m_Reader = new CBDRReader(m_Owner, this);
    Debug.varLog(m_cDeviceName, DEBUG_MASK_COMMUNICATION_INFO,
           "Recognized device %04x [%s]", pid, ptr);
    m_pid=pid;
    m_productString=ptr;
    free(ptr);
    return m_Reader;

  case 0x0527:
    m_Reader = new CSISReader(m_Owner, this);
    Debug.varLog(m_cDeviceName, DEBUG_MASK_COMMUNICATION_INFO,
           "Recognized device %04x [%s]", pid, ptr);
    m_pid=pid;
    m_productString=ptr;
    free(ptr);
    return m_Reader;

    /* add more readers here */

  default:
    Debug.varLog(m_cDeviceName, DEBUG_MASK_COMMUNICATION_ERROR,
                  "Device %04x [%s] ist not a known cyberJack\n", pid, ptr);
    free(ptr);
    return NULL;
  }
}



