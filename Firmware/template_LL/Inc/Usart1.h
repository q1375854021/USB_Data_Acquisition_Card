#ifndef __USART1_H
#define __USART1_H

#include "main.h"
#include "usart.h"
#include "String.h"

#define USART1_Data_Recv_Length  200       //���ڻ�������С

#define USART_Port USART1

extern uint8_t USART1_Data_Recv[USART1_Data_Recv_Length];      //�������ݻ�����
extern uint16_t USART1_CheckWord;                             //���ڼ��鵱ǰ�����Ƿ�Ϊ0x0a 0x0d
extern uint16_t USART1_Data_Recv_Num;                         //�����������ݴ�С
extern uint8_t USART1_STATUS;                                 //���ڵ�״̬   0����������1����������
extern int USART1_Received_Newest_Byte ;                       //���ڵ�����������  1���� 2�ص�



void USART1_Printf(char *str);                //�����ַ���
void USART1_SendByte(uint8_t data);           //����һ���ַ�
void USART1_Send_Nbit_Data(void *data,int Nbit);  //���ڷ���λ������λ������  int    long int     float ��Ϊ��λ   double 8λ   ˵ʵ�������Ǻܷ��㣬��Ϊ�����ж����ݵ���ʼ����ֹ����֪����ʼ����ֹ���Ǻܺõģ���֪���Ļ��������ַ���
void USART1_SendBytes(uint8_t *data, int Send_Byte_Num);          //���Ͷ���ַ�
uint8_t USART1_Read_Newest_Byte(void);                            //��ȡ���µĽ��յ��Ĵ�������
void USART1_Recv_DataArray_Clear(void);                           //��մ������ݣ��ȴ���һ�ֽ���



#endif
