void CONFIG_BTN1 (void);
void CONFIG_BTN2(void);
void CONFIG_TIMMER(void);
void PORTC_IRQHandler(void);
void LPIT0_Ch0_IRQHandler(void);
void LPIT0_Ch1_IRQHandler(void);
void CONFIG_LEDGREEN (void);
void LED_TEN_SECOND (void);

extern volatile int StateBTN1;
extern volatile int StateBTN2;
extern volatile int Set_Display;
extern volatile int Count;
extern volatile int Second;
extern volatile int BTN_LED;

extern volatile int  SecondAlarm;
extern volatile int  MinuteAlarm;
extern volatile int  HourAlarm;

extern volatile int  Hour;
extern volatile int  Minute;
