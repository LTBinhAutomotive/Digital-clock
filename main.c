#include"UART_UNIT.h"
#include"CLOCK_UNIT.h"
#include"SPI_UNIT.h"
#include"LED_UNIT.h"
#include"BUTTON_UNIT.h"
#include"../LIB/UART.h"
#include<string.h>

void DisplayTime (void);
void DisplayDate (void);
void DisplayAlarm(void);
void Send_Display(void);

void Set_Time (void);
void Set_Date (void);
void Set_Alarm(void);
static volatile int  Flag = 0;                                    // FLAG IDLE
static volatile int  State = 1;																		// State display User manual

void Check_Data(volatile unsigned char *DataTemp);                // check wrong format
void Decrease_LED_7_SEG (void);                                   // decrease led
void Alarm_Occurs(void);

static volatile unsigned char TempDate[11]={0};
static volatile unsigned char TempTime[9]={0};
static volatile unsigned char TempAlarm[9]={0};
static volatile int  IndexDate  = 0;
static volatile int  IndexTime  = 0;
static volatile int  IndexAlarm = 0;
volatile int StateBTN1 = 0;																					//button 1
volatile int StateBTN2 = 0;																					//button 2
volatile int Count = 0;																							//count 5s , 3s
volatile int Set_Display = 1;
volatile int BTN_LED = 1;

static unsigned char DIGITn[]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A};
static unsigned char LEDn[]  ={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};

static volatile int  Number1 = 0;
static volatile int  Number2 = 0;

volatile int Second   = 0;
volatile int Minute   = 0;
volatile int Hour     = 18;

static volatile int  Day     = 1;
static volatile int  Month   = 1;
static volatile int  Year1   = 19;
static volatile int  Year2   = 91;

volatile int  SecondAlarm = 0;
volatile int  MinuteAlarm = 0;
volatile int  HourAlarm   = 18;

int main()
{
	SOSOC_SCG  ( );
	SPLL_SCG   ( );
	CONFIG_UART( );
	CONFIG_SPI ( );
	CONFIG_LED ( );
	CONFIG_BTN1( );
	CONFIG_BTN2( );
	CONFIG_TIMMER( );
	CONFIG_LEDGREEN( );

	while(1)
	{
		if( Set_Display == 1)               //User manual
		{
			Send_Display ();
		}
		
		switch(StateBTN1)
		{
			case 0:
				while(Count != 6)
				{
					DisplayTime();
					Decrease_LED_7_SEG ();    				//Increase or decrease brightness
					if(StateBTN1 ==1) break;
				}
				while(Count != 9 )
				{
					DisplayDate();
					Decrease_LED_7_SEG ();
					if(StateBTN1 ==1) break;
				}
				break;
			case 1:
				DisplayDate();
				Decrease_LED_7_SEG ();
				break;
			case 2:
				DisplayTime();
				Decrease_LED_7_SEG ();
				break;
			case 3:
				DisplayAlarm();
				Decrease_LED_7_SEG ();
				break;
		}
	}
}

/*set display time */
void DisplayTime ( void )
{
	if ( Flag == 1)
	{
		IndexTime = 0;
		Set_Time ();
		Check_Data(TempTime);
		if ( State == 0)
		{
			for(volatile int i = 0 ;TempTime[i] != '\0' ;++i)
			{
				TempTime[i] = '\0' ;
			}
			State = 1;
		}
		Flag = 0;
	}

	/* 1. second   */
		Number1 = Second % 10;
		Transmit_SPI (LEDn[1] ,DIGITn[Number1] );
		Number2 = Second / 10;
		Transmit_SPI (LEDn[2] ,DIGITn[Number2] );

		Transmit_SPI (LEDn[3] ,DIGITn[10] );
	
	/* 2. Minute  */
		Number1 = Minute % 10;
		Transmit_SPI (LEDn[4] ,DIGITn[Number1] );
		Number2 = Minute / 10;
		Transmit_SPI (LEDn[5] ,DIGITn[Number2] );
	
		Transmit_SPI (LEDn[6] ,DIGITn[10] );
	
	/* 3. Hour   */
		Number1 = Hour % 10;
		Transmit_SPI (LEDn[7] ,DIGITn[Number1] );
		Number2 = Hour / 10;
		Transmit_SPI (LEDn[8] ,DIGITn[Number2] );
		
		if(Second >= 60)
		{
			Second = 0;
			Minute++;
			if(Minute >= 60)
			{
				Minute = 0;
				Hour++;
				if(Hour >= 24)
				{
					Hour = 0;
				}
			}
		}
}

/*set display date */
void DisplayDate ( void )
{
	if (Flag == 1)
	{
		IndexDate = 0;
		Set_Date ();
		Check_Data(TempDate);
		if (State == 0)
		{
			for(volatile int i = 0 ; TempDate[i] != '\0' ;++i)
			{
				TempDate[i] = '\0' ;
			}
			State = 1;
		}
		Flag = 0;
	}
	
		Number1 = Day % 10;
		Transmit_Point (LEDn[7] , 1 , DIGITn[Number1]);
		Number2 = Day / 10;
		Transmit_SPI (LEDn[8] ,DIGITn[Number2] );
	
		Number1 = Month % 10;
		Transmit_Point (LEDn[5] , 1 , DIGITn[Number1]);
		Number2 = Month / 10;
		Transmit_SPI (LEDn[6] ,DIGITn[Number2] );
	
		Number1 = Year1 % 10;
		Transmit_SPI (LEDn[3] ,DIGITn[Number1] );
		Number2 = Year1 / 10;
		Transmit_SPI (LEDn[4] ,DIGITn[Number2] );
	
		Number1 = Year2 % 10;
		Transmit_SPI (LEDn[1] ,DIGITn[Number1] );
		Number2 = Year2 / 10;
		Transmit_SPI (LEDn[2] ,DIGITn[Number2] );
		
		if(Day >= 30)
		{
			Day = 0;
			Month++;
			if(Month >= 12)
			{
				Month = 0;
				Year1++;
				if((Year1 == 99) && (Year2 == 99))
				{
					Year1 = 0;
					Year2 = 0;
				}
			}
		}
}

/*set display alarm */
void DisplayAlarm ( void )
{
	if ( Flag == 1)
	{
		IndexAlarm = 0;
		Set_Alarm ();
		Check_Data(TempAlarm);
		if ( State == 0)
		{
			for(volatile int i = 0 ; TempAlarm[i] != '\0' ;++i)
			{
				TempAlarm[i] = '\0' ;
			}
			State = 1;
		}
		Flag = 0;
	}
	
	/* 1. second   */
		Number1 = SecondAlarm % 10;
		Transmit_SPI (LEDn[1] ,DIGITn[Number1] );
		Number2 = SecondAlarm / 10;
		Transmit_SPI (LEDn[2] ,DIGITn[Number2] );
	
		Transmit_SPI (LEDn[3] ,DIGITn[10] );
	
	/* 2. Minute  */
		Number1 = MinuteAlarm % 10;
		Transmit_SPI (LEDn[4] ,DIGITn[Number1] );
		Number2 = MinuteAlarm / 10;
		Transmit_SPI (LEDn[5] ,DIGITn[Number2] );
	
		Transmit_SPI (LEDn[6] ,DIGITn[10] );
	
	/* 3. Hour   */
		Number1 = HourAlarm % 10;
		Transmit_SPI (LEDn[7] ,DIGITn[Number1] );
		Number2 = HourAlarm / 10;
		Transmit_SPI (LEDn[8] ,DIGITn[Number2] );
		
		if(SecondAlarm == 60)
		{
			SecondAlarm = 0;
			MinuteAlarm++;
			if(MinuteAlarm == 60)
			{
				MinuteAlarm = 0;
				HourAlarm++;
				if(HourAlarm == 24)
				{
					HourAlarm = 0;
				}
			}
		}
	
}

/*User manual*/
void Send_Display (void)
{
	if(StateBTN1 == 0)
	{
		UART_SendString("\n Repeat - Display the time (5s) - Display the date (3s) \n BTN 1: STATE TRANSITION \n BTN 2: INCREASE AND DECREASE BRIGHTNESS ");
		Set_Display = 0;
	}
	else if(StateBTN1 == 1)
	{
		UART_SendString("\n Setting Date(EX: 01.01.1991): ");
		Set_Display = 0;
	}
	else if(StateBTN1 == 2)
	{
		UART_SendString("\n Setting Time(EX: 18-00-25): ");
		Set_Display = 0;
	}
	else if(StateBTN1 == 3)
	{
		UART_SendString("\n Setting Alarm(EX: 18-00-30): ");
		Set_Display = 0;
	}
}

/* set time*/
void Set_Time(void)
{
	int i  = 0;
	Hour   = 0;
	Minute = 0;
	Second = 0;
	
	while(TempTime[i] != '-')
	{
		Hour = Hour*10 + TempTime[i]-48;
		i++;
	}
	i++;
	while(TempTime[i] != '-')
	{
		Minute = Minute*10 + TempTime[i]-48;
		i++;
	}
	i++;
	while(TempTime[i] != '\0')
	{
		Second = Second*10 + TempTime[i]-48;
		i++;
	}
}

/*set date*/
void Set_Date(void)
{
	int i = 0;
	Day   = 0;
	Month = 0;
	Year1 = 0;
	Year2 = 0;
	
	while(TempDate[i] != '.')
	{
		Day = Day *10 + TempDate[i]-48;
		i++;
	}
	i++;
	while(TempDate[i] != '.')
	{
		Month = Month*10 + TempDate[i]-48;
		i++;
	}
	i++;
	while(i < 8)
	{
		Year1 = Year1*10 + TempDate[i]-48;
		i++;
	}
	while(TempDate[i] != '\0')
	{
		Year2 = Year2*10 + TempDate[i]-48;
		i++;
	}
}

/* set alarm*/
void Set_Alarm(void)
{
	int i  = 0;
	HourAlarm   = 0;
	MinuteAlarm = 0;
	SecondAlarm = 0;
	
	while(TempAlarm[i] != '-')
	{
		HourAlarm = HourAlarm*10 + TempAlarm[i]-48;
		i++;
	}
	i++;
	while(TempAlarm[i] != '-')
	{
		MinuteAlarm = MinuteAlarm*10 + TempAlarm[i]-48;
		i++;
	}
	i++;
	while(TempAlarm[i] != '\0')
	{
		SecondAlarm = SecondAlarm*10 + TempAlarm[i]-48;
		i++;
	}
}

/*Increase or decrease brightness*/
void Decrease_LED_7_SEG (void)
{
	switch(StateBTN2)
	{
		case 0:
			Transmit_SPI (0x0A , 0x09);
			break;
		case 1:
			Transmit_SPI (0x0A , 0x04);
			break;
		case 2:
			Transmit_SPI (0x0A , 0x00);
			break;
		case 3:
			Transmit_SPI (0x0C , 0x00);
			break;
		default :
			Transmit_SPI (0x0C , 0x01);
			Transmit_SPI (0x0A , 0x0F);
			break;
	}
}

/*check wrong format */
void Check_Data(volatile unsigned char *DataTemp)
{
	int i = 0;
	State = 1;
	while(DataTemp[i] != ('\0'))
	{
		switch(DataTemp[i])
		{
			case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': case '0': case '.': case '-': case '\0':
				break;
			default:
				UART_SendString("\r\r!!!!!!Wrong format!!!!!!\r\n");
				State = 0;
		}
		i++;
	}
	if (Second > 60 )
	{
		UART_SendString("\r\r!!!!!!--Wrong format Second--!!!!!!\r\n");
		State = 0;
	}
	else if(Minute > 60 )
	{
		UART_SendString("\r\r!!!!!!--Wrong format Minute--!!!!!!\r\n");
		State = 0;
	}
	else if(Hour > 23 )
	{
		UART_SendString("\r\r!!!!!!--Wrong format Hour--!!!!!!\r\n");
		State = 0;
	}
	else if(Day > 30 )
	{
		UART_SendString("\r\r!!!!!!--Wrong format Day--!!!!!!\r\n");
		State = 0;
	}
	else if(Month > 12 )
	{
		UART_SendString("\r\r!!!!!!--Wrong format Month--!!!!!!\r\n");
		State = 0;
	}
	else if (SecondAlarm > 60 )
	{
		UART_SendString("\r\r!!!!!!--Wrong format SecondAlarm--!!!!!!\r\n");
		State = 0;
	}
	else if(MinuteAlarm > 60 )
	{
		UART_SendString("\r\r!!!!!!--Wrong format MinuteAlarm--!!!!!!\r\n");
		State = 0;
	}
	else if(HourAlarm > 23 )
	{
		UART_SendString("\r\r!!!!!!--Wrong format HourAlarm--!!!!!!\r\n");
		State = 0;
	}
}

/*interrupt UART */
void LPUART1_RxTx_IRQHandler(void)
{ 
	
	if( (LPUART_1->STAT & (1u << 21)) == (1u << 21) )
	{
		if(StateBTN1 == 1)
		{
			TempDate[IndexDate] = (char)LPUART_1->DATA;
			IndexDate++;
			TempDate[IndexDate] = '\0';
		}
		if(StateBTN1 == 2)
		{
			TempTime[IndexTime] = (char)LPUART_1->DATA;
			IndexTime++;
			TempTime[IndexTime] = '\0';
		}
		if(StateBTN1 == 3)
		{
			TempAlarm[IndexAlarm] = (char)LPUART_1->DATA;
			IndexAlarm++;
			TempAlarm[IndexAlarm] = '\0';
		}
	}
	
	if( (LPUART_1->STAT & (1u << 20)) == (1u << 20) )
	{
		LPUART_1->STAT |= (1u << 20);
		if(StateBTN1 == 1 || (StateBTN1 == 2)||(StateBTN1 == 3))
		{
			Flag = 1;
		}
	}
}
