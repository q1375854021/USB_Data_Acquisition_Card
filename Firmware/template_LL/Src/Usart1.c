#include "Usart1.h"

uint8_t USART1_Data_Recv[USART1_Data_Recv_Length];      //接收数据缓冲区
uint16_t USART1_CheckWord = 0;                             //用于检验当前数据是否为0x0a 0x0d
uint16_t USART1_Data_Recv_Num = 0;                         //缓冲区的数据大小
uint8_t USART1_STATUS = 0;                                 //串口的状态   0代表正常，1代表接受完毕
int USART1_Received_Newest_Byte = 0;                       //串口到的最新数据  1开灯 2关灯





void USART1_Printf(char *str)        //发送字符串
{
	int temp_i = 0;         //用于取字符串的每一个字符
	while(*(str+temp_i) != '\0')
	{
		while(LL_USART_IsActiveFlag_TC(USART_Port)==0);      //0表示数据还没有发完，要等待
		LL_USART_TransmitData8(USART_Port,*(str+temp_i));    //发送
		temp_i++;
	}
}





// 发送一个字节
void USART1_SendByte(uint8_t data)
{
	while(LL_USART_IsActiveFlag_TC(USART_Port)==0);  //0表示数据还没有发完，要等待
	LL_USART_TransmitData8(USART_Port,data);         //发送数据
}

// 发送多个字节，但是这里没有判别数组是否越界，使用时要注意
void USART1_SendBytes(uint8_t *data, int Send_Byte_Num)   
{
	int temp_i = 0;       //用于取数组的每一个内容
	while(temp_i < Send_Byte_Num)
	{
		USART1_SendByte(*(data+temp_i));
		temp_i++;
	}
}




void USART1_Send_Nbit_Data(void *data, int Nbit)  //int    long int     float 均为四位  double 8位
{
	uint8_t *temp_pointer = (uint8_t *)data;      //把float指针转为uint8_t指针，便于每8字节读取一个数据，否则则是32位  因为float就是32位的
	for(int i=0;i<Nbit;i++)   //float占用四个字节
	{
		USART1_SendByte(*(temp_pointer+Nbit-1-i));   //从高字节开始往低字节发，也就是说先发的是高位
	}  //完毕
}





uint8_t USART1_Read_Newest_Byte(void)    //获取串口读取到的最新的数据
{
	return USART1_Data_Recv[USART1_Data_Recv_Num-1];
}



void USART1_Recv_DataArray_Clear(void)   //清空串口缓冲区数据
{
	for(int i=0;i<USART1_Data_Recv_Num;i++)
	{
		USART1_Data_Recv[i]=0;
	}
	USART1_Data_Recv_Num=0;
}

