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
void usb_sendHalfwords(uint16_t *Buf, uint8_t *dest_Buf,uint32_t Len, uint8_t *num, uint8_t endian);  //Ҫ���͵�16bit�������飬Ŀ��8bit���飬 Ҫ���͵�16bit���ݳ��ȣ� Ҫ���͵Ĵ�����һ�㷢��һ�ξ��У�Դ�����С�˸�ʽ��1��ˣ�0С��
void usb_sendBytes(uint8_t* Buf, uint16_t Len);      //����Len��8bit����
void usb_sendWords(uint32_t *Buf, uint8_t *dest_Buf,uint32_t Len, uint8_t *num, uint8_t endian);  //Ҫ���͵�32bit�������飬Ŀ��8bit���飬 Ҫ���͵�32bit���ݳ��ȣ� Ҫ���͵Ĵ�����һ�㷢��һ�ξ��У�Դ�����С�˸�ʽ��1��ˣ�0С��
void usb_sendHalfwords_Direct(uint16_t *Buf,uint32_t Len, uint8_t *num);  //Ҫ���͵�16bit�������飬Ҫ���͵�16bit���ݳ��ȣ� Ҫ���͵Ĵ�����һ�㷢��һ�ξ���

#endif
