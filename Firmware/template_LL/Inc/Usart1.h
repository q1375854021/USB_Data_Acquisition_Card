#ifndef __USART1_H
#define __USART1_H

#include "main.h"
#include "usart.h"
#include "String.h"

#define USART1_Data_Recv_Length  200       //串口缓冲区大小

#define USART_Port USART1

extern uint8_t USART1_Data_Recv[USART1_Data_Recv_Length];      //接收数据缓冲区
extern uint16_t USART1_CheckWord;                             //用于检验当前数据是否为0x0a 0x0d
extern uint16_t USART1_Data_Recv_Num;                         //缓冲区的数据大小
extern uint8_t USART1_STATUS;                                 //串口的状态   0代表正常，1代表接受完毕
extern int USART1_Received_Newest_Byte ;                       //串口到的最新数据  1开灯 2关灯



void USART1_Printf(char *str);                //发送字符串
void USART1_SendByte(uint8_t data);           //发送一个字符
void USART1_Send_Nbit_Data(void *data,int Nbit);  //用于发送位宽超过两位的数据  int    long int     float 均为四位   double 8位   说实话并不是很方便，因为不好判断数据的起始和终止，能知道起始和终止还是很好的，不知道的话尽量用字符串
void USART1_SendBytes(uint8_t *data, int Send_Byte_Num);          //发送多个字符
uint8_t USART1_Read_Newest_Byte(void);                            //读取最新的接收到的串口数据
void USART1_Recv_DataArray_Clear(void);                           //清空串口数据，等待新一轮接收



#endif
