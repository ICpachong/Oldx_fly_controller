#include "iic2.h"



 void Delay_us_IMU1(u8 num)
{ 
	__nop();__nop();__nop();
	__nop();__nop();__nop();
	__nop();__nop();__nop();
	
	if(!IMU1_Fast)
	{
		u8 i = 15;
		while(i--);
	}
} 
/**************************ʵ�ֺ���********************************************
*����ԭ��:		void IIC_Init(void)
*��������:		��ʼ��I2C��Ӧ�Ľӿ����š�
*******************************************************************************/
void IIC_IMU1_Init(void)
{			
 GPIO_InitTypeDef  GPIO_InitStructure;
  #if USE_VER_5
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��GPIOBʱ��

  //GPIOB8,B9��ʼ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��
	IIC_IMU1_SCL4=1;
	IIC_IMU1_SDA4=1;
	#else
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOBʱ��

  //GPIOB8,B9��ʼ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��
	IIC_IMU1_SCL=1;
	IIC_IMU1_SDA=1;
	#endif
}

/**************************ʵ�ֺ���********************************************
*����ԭ��:		void IIC_Start(void)
*��������:		����IIC��ʼ�ź�
*******************************************************************************/
void IIC_IMU1_Start(void)
{
	#if USE_VER_5
		SDA_IMU1_OUT4();     //sda�����
	IIC_IMU1_SDA4=1;	  	  
	IIC_IMU1_SCL4=1;
	Delay_us_IMU1(4);
 	IIC_IMU1_SDA4=0;//START:when CLK is high,DATA change form high to low 
	Delay_us_IMU1(4);
	IIC_IMU1_SCL4=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
	#else
	SDA_IMU1_OUT();     //sda�����
	IIC_IMU1_SDA=1;	  	  
	IIC_IMU1_SCL=1;
	Delay_us_IMU1(4);
 	IIC_IMU1_SDA=0;//START:when CLK is high,DATA change form high to low 
	Delay_us_IMU1(4);
	IIC_IMU1_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
	#endif
}

/**************************ʵ�ֺ���********************************************
*����ԭ��:		void IIC_Stop(void)
*��������:	    //����IICֹͣ�ź�
*******************************************************************************/	  
void IIC_IMU1_Stop(void)
{
		#if USE_VER_5
	SDA_IMU1_OUT4();//sda�����
	IIC_IMU1_SCL4=0;
	IIC_IMU1_SDA4=0;//STOP:when CLK is high DATA change form low to high
 	Delay_us_IMU1(4);
	IIC_IMU1_SCL4=1; 
	IIC_IMU1_SDA4=1;//����I2C���߽����ź�
	Delay_us_IMU1(4);				
	#else
	SDA_IMU1_OUT();//sda�����
	IIC_IMU1_SCL=0;
	IIC_IMU1_SDA=0;//STOP:when CLK is high DATA change form low to high
 	Delay_us_IMU1(4);
	IIC_IMU1_SCL=1; 
	IIC_IMU1_SDA=1;//����I2C���߽����ź�
	Delay_us_IMU1(4);				
#endif	
}

/**************************ʵ�ֺ���********************************************
*����ԭ��:		u8 IIC_Wait_Ack(void)
*��������:	    �ȴ�Ӧ���źŵ��� 
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
*******************************************************************************/
u8 IIC_IMU1_Wait_Ack(void)
{
	u8 ucErrTime=0;
		#if USE_VER_5
	SDA_IMU1_IN4();      //SDA����Ϊ����  
	IIC_IMU1_SDA4=1;Delay_us_IMU1(1);	   
	IIC_IMU1_SCL4=1;Delay_us_IMU1(1);	 
	while(READ_IMU1_SDA4)
	{
		ucErrTime++;
		if(ucErrTime>50)
		{
			IIC_IMU1_Stop();
			return 1;
		}
	  Delay_us_IMU1(1);
	}
	IIC_IMU1_SCL4=0;//ʱ�����0 	
	#else
	SDA_IMU1_IN();      //SDA����Ϊ����  
	IIC_IMU1_SDA=1;Delay_us_IMU1(1);	   
	IIC_IMU1_SCL=1;Delay_us_IMU1(1);	 
	while(READ_IMU1_SDA)
	{
		ucErrTime++;
		if(ucErrTime>50)
		{
			IIC_IMU1_Stop();
			return 1;
		}
	  Delay_us_IMU1(1);
	}
	IIC_IMU1_SCL=0;//ʱ�����0 	
	#endif	
	return 0;  
} 

/**************************ʵ�ֺ���********************************************
*����ԭ��:		void IIC_Ack(void)
*��������:	    ����ACKӦ��
*******************************************************************************/
void IIC_IMU1_Ack(void)
{
		#if USE_VER_5
	IIC_IMU1_SCL4=0;
	SDA_IMU1_OUT4();
	IIC_IMU1_SDA4=0;
	Delay_us_IMU1(2);
	IIC_IMU1_SCL4=1;
	Delay_us_IMU1(2);
	IIC_IMU1_SCL4=0;
	#else
	IIC_IMU1_SCL=0;
	SDA_IMU1_OUT();
	IIC_IMU1_SDA=0;
	Delay_us_IMU1(2);
	IIC_IMU1_SCL=1;
	Delay_us_IMU1(2);
	IIC_IMU1_SCL=0;
		#endif
}
	
/**************************ʵ�ֺ���********************************************
*����ԭ��:		void IIC_NAck(void)
*��������:	    ����NACKӦ��
*******************************************************************************/	    
void IIC_IMU1_NAck(void)
{
		#if USE_VER_5
	IIC_IMU1_SCL4=0;
	SDA_IMU1_OUT4();
	IIC_IMU1_SDA4=1;
	Delay_us_IMU1(2);
	IIC_IMU1_SCL4=1;
	Delay_us_IMU1(2);
	IIC_IMU1_SCL4=0;
	#else
	IIC_IMU1_SCL=0;
	SDA_IMU1_OUT();
	IIC_IMU1_SDA=1;
	Delay_us_IMU1(2);
	IIC_IMU1_SCL=1;
	Delay_us_IMU1(2);
	IIC_IMU1_SCL=0;
		#endif
}					 				     

/**************************ʵ�ֺ���********************************************
*����ԭ��:		void IIC_Send_Byte(u8 txd)
*��������:	    IIC����һ���ֽ�
*******************************************************************************/		  
void IIC_IMU1_Send_Byte(u8 txd)
{                        
    u8 t;  
	#if USE_VER_5
	SDA_IMU1_OUT4(); 	    
    IIC_IMU1_SCL4=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        IIC_IMU1_SDA4=(txd&0x80)>>7;
        txd<<=1; 	  
		Delay_us_IMU1(2);   
		IIC_IMU1_SCL4=1;
		Delay_us_IMU1(2); 
		IIC_IMU1_SCL4=0;	
		Delay_us_IMU1(2);
    }	 
	#else	
	SDA_IMU1_OUT(); 	    
    IIC_IMU1_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        IIC_IMU1_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		Delay_us_IMU1(2);   
		IIC_IMU1_SCL=1;
		Delay_us_IMU1(2); 
		IIC_IMU1_SCL=0;	
		Delay_us_IMU1(2);
    }	 
			#endif
} 	 
   
/**************************ʵ�ֺ���********************************************
*����ԭ��:		u8 IIC_Read_Byte(unsigned char ack)
*��������:	    //��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK 
*******************************************************************************/  
u8 IIC_IMU1_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
		#if USE_VER_5
		SDA_IMU1_IN4();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        IIC_IMU1_SCL4=0; 
        Delay_us_IMU1(2);
		IIC_IMU1_SCL4=1;
        receive<<=1;
        if(READ_IMU1_SDA4)receive++;   
		Delay_us_IMU1(2); 
    }					 
    if (ack)
        IIC_IMU1_Ack(); //����ACK 
    else
        IIC_IMU1_NAck();//����nACK  
	#else
	SDA_IMU1_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        IIC_IMU1_SCL=0; 
        Delay_us_IMU1(2);
		IIC_IMU1_SCL=1;
        receive<<=1;
        if(READ_IMU1_SDA)receive++;   
		Delay_us_IMU1(2); 
    }					 
    if (ack)
        IIC_IMU1_Ack(); //����ACK 
    else
        IIC_IMU1_NAck();//����nACK  
		#endif
    return receive;
}

/**************************ʵ�ֺ���********************************************
*����ԭ��:		unsigned char I2C_ReadOneByte(unsigned char I2C_Addr,unsigned char addr)
*��������:	    ��ȡָ���豸 ָ���Ĵ�����һ��ֵ
����	I2C_Addr  Ŀ���豸��ַ
		addr	   �Ĵ�����ַ
����   ��������ֵ
*******************************************************************************/ 
unsigned char I2C_IMU1_ReadOneByte(unsigned char I2C_Addr,unsigned char addr)
{
	unsigned char res=0;
	
	IIC_IMU1_Start();	
	IIC_IMU1_Send_Byte(I2C_Addr);	   //����д����
	res++;
	IIC_IMU1_Wait_Ack();
	IIC_IMU1_Send_Byte(addr); res++;  //���͵�ַ
	IIC_IMU1_Wait_Ack();	  
	//IIC_Stop();//����һ��ֹͣ����	
	IIC_IMU1_Start();
	IIC_IMU1_Send_Byte(I2C_Addr+1); res++;          //�������ģʽ			   
	IIC_IMU1_Wait_Ack();
	res=IIC_IMU1_Read_Byte(0);	   
    IIC_IMU1_Stop();//����һ��ֹͣ����

	return res;
}


/**************************ʵ�ֺ���********************************************
*����ԭ��:		u8 IICreadBytes(u8 dev, u8 reg, u8 length, u8 *data)
*��������:	    ��ȡָ���豸 ָ���Ĵ����� length��ֵ
����	dev  Ŀ���豸��ַ
		reg	  �Ĵ�����ַ
		length Ҫ�����ֽ���
		*data  ���������ݽ�Ҫ��ŵ�ָ��
����   ���������ֽ�����
*******************************************************************************/ 
u8 IIC_IMU1readBytes(u8 dev, u8 reg, u8 length, u8 *data){
    u8 count = 0;
	
	IIC_IMU1_Start();
	IIC_IMU1_Send_Byte(dev);	   //����д����
	IIC_IMU1_Wait_Ack();
	IIC_IMU1_Send_Byte(reg);   //���͵�ַ
    IIC_IMU1_Wait_Ack();	  
	IIC_IMU1_Start();
	IIC_IMU1_Send_Byte(dev+1);  //�������ģʽ	
	IIC_IMU1_Wait_Ack();
	
    for(count=0;count<length;count++){
		 
		 if(count!=length-1)data[count]=IIC_IMU1_Read_Byte(1);  //��ACK�Ķ�����
		 	else  data[count]=IIC_IMU1_Read_Byte(0);	 //���һ���ֽ�NACK
	}
    IIC_IMU1_Stop();//����һ��ֹͣ����
    return count;
}

/**************************ʵ�ֺ���********************************************
*����ԭ��:		u8 IICwriteBytes(u8 dev, u8 reg, u8 length, u8* data)
*��������:	    ������ֽ�д��ָ���豸 ָ���Ĵ���
����	dev  Ŀ���豸��ַ
		reg	  �Ĵ�����ַ
		length Ҫд���ֽ���
		*data  ��Ҫд�����ݵ��׵�ַ
����   �����Ƿ�ɹ�
*******************************************************************************/ 
u8 IIC_IMU1writeBytes(u8 dev, u8 reg, u8 length, u8* data){
  
 	u8 count = 0;
	IIC_IMU1_Start();
	IIC_IMU1_Send_Byte(dev);	   //����д����
	IIC_IMU1_Wait_Ack();
	IIC_IMU1_Send_Byte(reg);   //���͵�ַ
    IIC_IMU1_Wait_Ack();	  
	for(count=0;count<length;count++){
		IIC_IMU1_Send_Byte(data[count]); 
		IIC_IMU1_Wait_Ack(); 
	 }
	IIC_IMU1_Stop();//����һ��ֹͣ����

    return 1; //status == 0;
}

/**************************ʵ�ֺ���********************************************
*����ԭ��:		u8 IICreadByte(u8 dev, u8 reg, u8 *data)
*��������:	    ��ȡָ���豸 ָ���Ĵ�����һ��ֵ
����	dev  Ŀ���豸��ַ
		reg	   �Ĵ�����ַ
		*data  ���������ݽ�Ҫ��ŵĵ�ַ
����   1
*******************************************************************************/ 
u8 IIC_IMU1readByte(u8 dev, u8 reg, u8 *data){
	*data=I2C_IMU1_ReadOneByte(dev, reg);
    return 1;
}

/**************************ʵ�ֺ���********************************************
*����ԭ��:		unsigned char IICwriteByte(unsigned char dev, unsigned char reg, unsigned char data)
*��������:	    д��ָ���豸 ָ���Ĵ���һ���ֽ�
����	dev  Ŀ���豸��ַ
		reg	   �Ĵ�����ַ
		data  ��Ҫд����ֽ�
����   1
*******************************************************************************/ 
unsigned char IIC_IMU1writeByte(unsigned char dev, unsigned char reg, unsigned char data){
    return IIC_IMU1writeBytes(dev, reg, 1, &data);
}

/**************************ʵ�ֺ���********************************************
*����ԭ��:		u8 IICwriteBits(u8 dev,u8 reg,u8 bitStart,u8 length,u8 data)
*��������:	    �� �޸� д ָ���豸 ָ���Ĵ���һ���ֽ� �еĶ��λ
����	dev  Ŀ���豸��ַ
		reg	   �Ĵ�����ַ
		bitStart  Ŀ���ֽڵ���ʼλ
		length   λ����
		data    ��Ÿı�Ŀ���ֽ�λ��ֵ
����   �ɹ� Ϊ1 
 		ʧ��Ϊ0
*******************************************************************************/ 
u8 IIC_IMU1writeBitsm(u8 dev,u8 reg,u8 bitStart,u8 length,u8 data)
{

    u8 b;
    if (IIC_IMU1readByte(dev, reg, &b) != 0) {
        u8 mask = (0xFF << (bitStart + 1)) | 0xFF >> ((8 - bitStart) + length - 1);
        data <<= (8 - length);
        data >>= (7 - bitStart);
        b &= mask;
        b |= data;
        return IIC_IMU1writeByte(dev, reg, b);
    } else {
        return 0;
    }
}

/**************************ʵ�ֺ���********************************************
*����ԭ��:		u8 IICwriteBit(u8 dev, u8 reg, u8 bitNum, u8 data)
*��������:	    �� �޸� д ָ���豸 ָ���Ĵ���һ���ֽ� �е�1��λ
����	dev  Ŀ���豸��ַ
		reg	   �Ĵ�����ַ
		bitNum  Ҫ�޸�Ŀ���ֽڵ�bitNumλ
		data  Ϊ0 ʱ��Ŀ��λ������0 ���򽫱���λ
����   �ɹ� Ϊ1 
 		ʧ��Ϊ0
*******************************************************************************/ 
u8 IIC_IMU1writeBitm(u8 dev, u8 reg, u8 bitNum, u8 data){
    u8 b;
    IIC_IMU1readByte(dev, reg, &b);
    b = (data != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));
    return IIC_IMU1writeByte(dev, reg, b);
}

//------------------End of File----------------------------