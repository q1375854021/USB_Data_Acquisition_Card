#include "Usb.h"

extern uint8_t UserTxBufferHS[APP_TX_DATA_SIZE];


/**
  * @brief          usb���⴮��,printf ����
  * @param[in]     	char* fmt,...
  * @retval         none
  */
void usb_printf(char* fmt,...)  
{  
	uint16_t i;
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char*)UserTxBufferHS,fmt,ap);
	va_end(ap);
	i=strlen((const char*)UserTxBufferHS);     //�˴η������ݵĳ���
  CDC_Transmit_HS(UserTxBufferHS,i);              //��������
}

/**
	* @brief          usb���⴮�ڣ�ͨ�����⴮�ڷ��ͽ��յ�������
										��Ҫ��CDC_Receive_FS�����е���
  * @param[in]     	uint8_t* Buf 
										uint32_t Len
  * @retval         USBD_OK
  */
uint16_t VCP_DataRx (uint8_t* Buf, uint32_t Len)
{
	CDC_Transmit_HS(Buf,Len); 
	return USBD_OK;
}

void usb_sendBytes_Transpeed(uint32_t i)
{
	memset(UserTxBufferHS,i,sizeof(UserTxBufferHS));
	CDC_Transmit_HS(UserTxBufferHS,sizeof(UserTxBufferHS));              //��������
}

void usb_sendHalfwords(uint16_t *Buf, uint8_t *dest_Buf,uint32_t Len, uint8_t *num, uint8_t endian)  //Ҫ���͵�16bit�������飬Ŀ��8bit���飬 Ҫ���͵�16bit���ݳ��ȣ� Ҫ���͵Ĵ�����һ�㷢��һ�ξ��У�Դ�����С�˸�ʽ��1��ˣ�0С��
{
	//����ͳ�ȥ��������Զ�Ǹ߰�λ��ǰ���ڰ�λ�ں�
	if(Len>1024) return;         //���ܴ���1024������  ����Ҫ������USB���������СΪ2048
	if(endian == 1)   //��˸�ʽ
	{
		for(int i=0;i<Len;i++)
		{
			*(dest_Buf+2*i) = *(Buf+i)>>8;           //�͵�ַ�Ÿ��ֽ�
			*(dest_Buf+2*i+1) = *(Buf+i);            //�ߵ�ַ�ŵ��ֽ�
		}
	}
	else //С�˸�ʽ
	{
		for(int i=0;i<Len;i++)
		{
			*(dest_Buf+2*i) = *(Buf+i);                  //�͵�ַ�ŵ��ֽ�
			*(dest_Buf+2*i+1) = *(Buf+i)>>8;            //�ߵ�ַ�Ÿ��ֽ�
		}
	}
	*num = *num-1;
	CDC_Transmit_HS(dest_Buf,2*Len);        //��������
}

void usb_sendBytes(uint8_t* Buf, uint16_t Len)      //����Len��8bit����
{
	CDC_Transmit_HS(Buf,Len);
}


void usb_sendWords(uint32_t *Buf, uint8_t *dest_Buf,uint32_t Len, uint8_t *num, uint8_t endian) //Ҫ���͵�32bit�������飬Ŀ��8bit���飬 Ҫ���͵�32bit���ݳ��ȣ� Ҫ���͵Ĵ�����һ�㷢��һ�ξ��У�Դ�����С�˸�ʽ��1��ˣ�0С��
{
	//����ͳ�ȥ��������Զ�Ǹ�λ��ǰ����λ�ں�
	if(Len>512) return;         //���ܴ���512������  ����Ҫ������USB���������СΪ2048
	if(endian == 1)   //��˸�ʽ
	{
		for(int i=0;i<Len;i++)
		{
			*(dest_Buf+4*i) = *(Buf+i)>>24;           //�͵�ַ�Ÿ��ֽ�
			*(dest_Buf+4*i+1) = *(Buf+i)>>16;            //�ߵ�ַ�ŵ��ֽ�
			*(dest_Buf+4*i+2) = *(Buf+i)>>8;           //�͵�ַ�Ÿ��ֽ�
			*(dest_Buf+4*i+1) = *(Buf+i);            //�ߵ�ַ�ŵ��ֽ�
		}
	}
	else //С�˸�ʽ
	{
		for(int i=0;i<Len;i++)
		{
			*(dest_Buf+4*i) = *(Buf+i);                  //�͵�ַ�ŵ��ֽ�
			*(dest_Buf+4*i+1) = *(Buf+i)>>8;            //�ߵ�ַ�Ÿ��ֽ�
			*(dest_Buf+4*i+2) = *(Buf+i)>>16;                  //�͵�ַ�ŵ��ֽ�
			*(dest_Buf+4*i+1) = *(Buf+i)>>24;            //�ߵ�ַ�Ÿ��ֽ�
		}
	}
	*num = (*num) -1;
	CDC_Transmit_HS(dest_Buf,4*Len);        //��������
}

void usb_sendHalfwords_Direct(uint16_t *Buf,uint32_t Len, uint8_t *num)  //Ҫ���͵�16bit�������飬Ҫ���͵�16bit���ݳ��ȣ� Ҫ���͵Ĵ�����һ�㷢��һ�ξ���
{
	//����ͳ�ȥ��������Զ�Ǹ߰�λ��ǰ���ڰ�λ�ں�
	if(Len>1024) return;         //���ܴ���1024������  ����Ҫ������USB���������СΪ2048
	*num = *num-1;
	CDC_Transmit_HS((uint8_t *)Buf,2*Len);        //��������
}

