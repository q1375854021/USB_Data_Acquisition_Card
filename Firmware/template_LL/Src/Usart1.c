#include "Usart1.h"

uint8_t USART1_Data_Recv[USART1_Data_Recv_Length];      //�������ݻ�����
uint16_t USART1_CheckWord = 0;                             //���ڼ��鵱ǰ�����Ƿ�Ϊ0x0a 0x0d
uint16_t USART1_Data_Recv_Num = 0;                         //�����������ݴ�С
uint8_t USART1_STATUS = 0;                                 //���ڵ�״̬   0����������1����������
int USART1_Received_Newest_Byte = 0;                       //���ڵ�����������  1���� 2�ص�





void USART_Printf(char *str)        //�����ַ���
{
	int temp_i = 0;         //����ȡ�ַ�����ÿһ���ַ�
	while(*(str+temp_i) != '\0')
	{
		while(LL_USART_IsActiveFlag_TC(USART_Port)==0);      //0��ʾ���ݻ�û�з��꣬Ҫ�ȴ�
		LL_USART_TransmitData8(USART_Port,*(str+temp_i));    //����
		temp_i++;
	}
}





// ����һ���ֽ�
void USART_SendByte(uint8_t data)
{
	while(LL_USART_IsActiveFlag_TC(USART_Port)==0);  //0��ʾ���ݻ�û�з��꣬Ҫ�ȴ�
	LL_USART_TransmitData8(USART_Port,data);         //��������
}

// ���Ͷ���ֽڣ���������û���б������Ƿ�Խ�磬ʹ��ʱҪע��
void USART_SendBytes(uint8_t *data, int Send_Byte_Num)   
{
	int temp_i = 0;       //����ȡ�����ÿһ������
	while(temp_i < Send_Byte_Num)
	{
		USART_SendByte(*(data+temp_i));
		temp_i++;
	}
}




void USART_Send_Nbit_Data(void *data, int Nbit)  //int    long int     float ��Ϊ��λ  double 8λ
{
	uint8_t *temp_pointer = (uint8_t *)data;      //��floatָ��תΪuint8_tָ�룬����ÿ8�ֽڶ�ȡһ�����ݣ���������32λ  ��Ϊfloat����32λ��
	for(int i=0;i<Nbit;i++)   //floatռ���ĸ��ֽ�
	{
		USART_SendByte(*(temp_pointer+Nbit-1-i));   //�Ӹ��ֽڿ�ʼ�����ֽڷ���Ҳ����˵�ȷ����Ǹ�λ
	}  //���
}





uint8_t USART_Read_Newest_Byte(void)    //��ȡ���ڶ�ȡ�������µ�����
{
	return USART1_Data_Recv[USART1_Data_Recv_Num-1];
}



void USART_Recv_DataArray_Clear(void)   //��մ��ڻ���������
{
	for(int i=0;i<USART1_Data_Recv_Num;i++)
	{
		USART1_Data_Recv[i]=0;
	}
	USART1_Data_Recv_Num=0;
}

