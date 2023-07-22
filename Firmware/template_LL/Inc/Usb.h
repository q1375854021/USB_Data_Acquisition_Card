#ifndef __USB_H
#define	__USB_H

#include "main.h"
#include "usbd_cdc_if.h"
#include "string.h"	
#include "stdarg.h"		 
#include "stdio.h"	

void usb_printf(char* fmt,...);
uint16_t VCP_DataRx (uint8_t* Buf, uint32_t Len);
void usb_sendBytes_Transpeed(uint32_t i);
void usb_sendHalfwords(uint16_t *Buf, uint8_t *dest_Buf,uint32_t Len, uint8_t *num, uint8_t endian);  //要发送的16bit数据数组，目标8bit数组， 要发送的16bit数据长度， 要发送的次数，一般发送一次就行，源数组大小端格式：1大端，0小端
void usb_sendBytes(uint8_t* Buf, uint16_t Len);      //发送Len个8bit数据
void usb_sendWords(uint32_t *Buf, uint8_t *dest_Buf,uint32_t Len, uint8_t *num, uint8_t endian);  //要发送的32bit数据数组，目标8bit数组， 要发送的32bit数据长度， 要发送的次数，一般发送一次就行，源数组大小端格式：1大端，0小端
void usb_sendHalfwords_Direct(uint16_t *Buf,uint32_t Len, uint8_t *num);  //要发送的16bit数据数组，要发送的16bit数据长度， 要发送的次数，一般发送一次就行

#endif
