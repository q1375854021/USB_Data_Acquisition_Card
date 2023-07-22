#include "Usb.h"

extern uint8_t UserTxBufferHS[APP_TX_DATA_SIZE];


/**
  * @brief          usb虚拟串口,printf 函数
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
	i=strlen((const char*)UserTxBufferHS);     //此次发送数据的长度
  CDC_Transmit_HS(UserTxBufferHS,i);              //发送数据
}

/**
	* @brief          usb虚拟串口，通过虚拟串口发送接收到的数据
										需要在CDC_Receive_FS函数中调用
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
	CDC_Transmit_HS(UserTxBufferHS,sizeof(UserTxBufferHS));              //发送数据
}

void usb_sendHalfwords(uint16_t *Buf, uint8_t *dest_Buf,uint32_t Len, uint8_t *num, uint8_t endian)  //要发送的16bit数据数组，目标8bit数组， 要发送的16bit数据长度， 要发送的次数，一般发送一次就行，源数组大小端格式：1大端，0小端
{
	//最后发送出去的数据永远是高八位在前，第八位在后
	if(Len>1024) return;         //不能大于1024个数据  这主要是由于USB传输数组大小为2048
	if(endian == 1)   //大端格式
	{
		for(int i=0;i<Len;i++)
		{
			*(dest_Buf+2*i) = *(Buf+i)>>8;           //低地址放高字节
			*(dest_Buf+2*i+1) = *(Buf+i);            //高地址放低字节
		}
	}
	else //小端格式
	{
		for(int i=0;i<Len;i++)
		{
			*(dest_Buf+2*i) = *(Buf+i);                  //低地址放低字节
			*(dest_Buf+2*i+1) = *(Buf+i)>>8;            //高地址放高字节
		}
	}
	*num = *num-1;
	CDC_Transmit_HS(dest_Buf,2*Len);        //发送数据
}

void usb_sendBytes(uint8_t* Buf, uint16_t Len)      //发送Len个8bit数据
{
	CDC_Transmit_HS(Buf,Len);
}


void usb_sendWords(uint32_t *Buf, uint8_t *dest_Buf,uint32_t Len, uint8_t *num, uint8_t endian) //要发送的32bit数据数组，目标8bit数组， 要发送的32bit数据长度， 要发送的次数，一般发送一次就行，源数组大小端格式：1大端，0小端
{
	//最后发送出去的数据永远是高位在前，低位在后
	if(Len>512) return;         //不能大于512个数据  这主要是由于USB传输数组大小为2048
	if(endian == 1)   //大端格式
	{
		for(int i=0;i<Len;i++)
		{
			*(dest_Buf+4*i) = *(Buf+i)>>24;           //低地址放高字节
			*(dest_Buf+4*i+1) = *(Buf+i)>>16;            //高地址放低字节
			*(dest_Buf+4*i+2) = *(Buf+i)>>8;           //低地址放高字节
			*(dest_Buf+4*i+1) = *(Buf+i);            //高地址放低字节
		}
	}
	else //小端格式
	{
		for(int i=0;i<Len;i++)
		{
			*(dest_Buf+4*i) = *(Buf+i);                  //低地址放低字节
			*(dest_Buf+4*i+1) = *(Buf+i)>>8;            //高地址放高字节
			*(dest_Buf+4*i+2) = *(Buf+i)>>16;                  //低地址放低字节
			*(dest_Buf+4*i+1) = *(Buf+i)>>24;            //高地址放高字节
		}
	}
	*num = (*num) -1;
	CDC_Transmit_HS(dest_Buf,4*Len);        //发送数据
}

void usb_sendHalfwords_Direct(uint16_t *Buf,uint32_t Len, uint8_t *num)  //要发送的16bit数据数组，要发送的16bit数据长度， 要发送的次数，一般发送一次就行
{
	//最后发送出去的数据永远是高八位在前，第八位在后
	if(Len>1024) return;         //不能大于1024个数据  这主要是由于USB传输数组大小为2048
	*num = *num-1;
	CDC_Transmit_HS((uint8_t *)Buf,2*Len);        //发送数据
}

