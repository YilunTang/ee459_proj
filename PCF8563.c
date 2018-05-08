//PCF8563

/****c*
 *  NAME
 *    Pcf8563 Real Time Clock support routines
 *  AUTHOR
 *    Joe Robertson, jmr
 *    orbitalair@bellsouth.net
 *    
 *  CREATION DATE
 *    9/24/06,  init - built off of usart demo.  using mikroC
 *  NOTES
 *  HISTORY
 *    10/14/06 ported to CCS compiler, jmr
 *    2/21/09  changed all return values to hex val and not bcd, jmr
 *    1/10/10  ported to arduino, jmr
 *    2/14/10  added 3 world date formats, jmr
 *    1/22/10, jmr,  ported to arduino 1.0.  changed header include, wire.send -> wire.write, wire.receive -> wire.read
 *    28/02/2012 A. Pasotti
 *             fixed a bug in RTCC_ALARM_AF,
 *             added a few (not really useful) methods
 *    12/26/12, jmr, merged in fix for arduino 1.0.1 Wire.
 *                   added version method to print out code version.
 *    2/6/15  made gettime, getdate more convenient
 *                   rechecked and added to examples.  ino's are most up to date.
 *  TODO
 *    done- Add Euro date format
 *    done- Add short time (hh:mm) format
 *    Add 24h/12h format
 *    Add timer support
 ******
 *  Robodoc embedded documentation.
 *  http://www.xs4all.nl/~rfsber/Robo/robodoc.html
 */

// #if defined(ARDUINO) && ARDUINO >= 100
// #define char uint8_t
// #define send( X ) write( static_cast<uint8_t>(X) )
// #define receive( X ) read( X )
// #define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
// #else
// #include "WProgram.h"
// #endif

// #include <Wire.h>
#include "PCF8563.h"

// Rtc_Pcf8563(void)
// {
// 	// Wire.begin();
// 	Rtcc_Addr = RTCC_R>>1;	
// }

static inline unsigned long long S_to_binary_(const char *s)
{
        unsigned long long i = 0;
        while (*s) {
                i <<= 1;
                i += *s++ - '0';
        }
        return i;
}

void initClock()
{  	  
  unsigned char abuf;
  abuf = RTCC_STAT1_ADDR;
  unsigned char wbuf;
  wbuf = 0x00;
  i2c_io (Rtcc_Addr, &abuf, 1, &wbuf, 1, NULL, 0);
  _delay_ms(50);

  abuf = RTCC_STAT2_ADDR;
  wbuf = 0x00;
  i2c_io (Rtcc_Addr, &abuf, 1, &wbuf, 1, NULL, 0);
  _delay_ms(50);

  abuf = RTCC_SEC_ADDR;
  wbuf = 0x01;
  // buf[2] = {RTCC_SEC_ADDR, 0x01};
  i2c_io (Rtcc_Addr, &abuf, 1, &wbuf, 1, NULL, 0);
  _delay_ms(50);

  abuf = RTCC_MIN_ADDR;
  wbuf = 0x01;
  // buf[2] = {RTCC_MIN_ADDR, 0x01};
  i2c_io (Rtcc_Addr, &abuf, 1, &wbuf, 1, NULL, 0);
  _delay_ms(50);

  abuf = RTCC_HR_ADDR;
  wbuf = 0x01;
  // buf[2] = {RTCC_HR_ADDR, 0x01};
  i2c_io (Rtcc_Addr, &abuf, 1, &wbuf, 1, NULL, 0);
  _delay_ms(50);

  abuf = RTCC_DAY_ADDR;
  wbuf = 0x01;
  // buf[2] = {RTCC_DAY_ADDR, 0x01};
  i2c_io (Rtcc_Addr, &abuf, 1, &wbuf, 1, NULL, 0);
  _delay_ms(50);

  abuf = RTCC_WEEKDAY_ADDR;
  wbuf = 0x01;
  // buf[2] = {RTCC_WEEKDAY_ADDR, 0x01};
  i2c_io (Rtcc_Addr, &abuf, 1, &wbuf, 1, NULL, 0);
  _delay_ms(50);

  abuf = RTCC_MONTH_ADDR;
  wbuf = 0x01;
  // buf[2] = {RTCC_MONTH_ADDR, 0x01};
  i2c_io (Rtcc_Addr, &abuf, 1, &wbuf, 1, NULL, 0);
  _delay_ms(50);

  abuf = RTCC_YEAR_ADDR;
  wbuf = 0x01;
  // buf[2] = {RTCC_YEAR_ADDR, 0x01};
  i2c_io (Rtcc_Addr, &abuf, 1, &wbuf, 1, NULL, 0);
  _delay_ms(50);

  abuf = RTCC_ALRM_MIN_ADDR;
  wbuf = 0x80;
  // buf[2] = {RTCC_ALRM_MIN_ADDR, 0x80};
  i2c_io (Rtcc_Addr, &abuf, 1, &wbuf, 1, NULL, 0);
  _delay_ms(50);

  abuf = RTCC_ALRM_HR_ADDR;
  wbuf = 0x80;
  // buf[2] = {RTCC_ALRM_HR_ADDR, 0x80};
  i2c_io (Rtcc_Addr, &abuf, 1, &wbuf, 1, NULL, 0);
  _delay_ms(50);

  abuf = RTCC_ALRM_DAY_ADDR;
  wbuf = 0x80;
  // buf[2] = {RTCC_ALRM_DAY_ADDR, 0x80};
  i2c_io (Rtcc_Addr, &abuf, 1, &wbuf, 1, NULL, 0);
  _delay_ms(50);

  abuf = RTCC_ALRM_WEEKDAY_ADDR;
  wbuf = 0x80;
  // buf[2] = {RTCC_ALRM_WEEKDAY_ADDR, 0x80};
  i2c_io (Rtcc_Addr, &abuf, 1, &wbuf, 1, NULL, 0);
  _delay_ms(50);

  abuf = RTCC_CLKOUT_ADDR;
  wbuf = 0x00;
  // buf[2] = {RTCC_CLKOUT_ADDR, 0x00};
  i2c_io (Rtcc_Addr, &abuf, 1, &wbuf, 1, NULL, 0);
  _delay_ms(50);

  abuf = RTCC_TIMERCTRL_ADDR;
  wbuf = 0x00;
  // buf[2] = {RTCC_TIMERCTRL_ADDR, 0x00};
  i2c_io (Rtcc_Addr, &abuf, 1, &wbuf, 1, NULL, 0);
  _delay_ms(50);
}

/* Private internal functions, but useful to look at if you need a similar func. */
unsigned char decToBcd(unsigned char val)
{
  return ( (val/10*16) + (val%10) );
}

unsigned char bcdToDec(unsigned char val)
{
  return ( (val/16*10) + (val%16) );
}


void clearStatus()
{
 //  Wire.beginTransmission(Rtcc_Addr);	// Issue I2C start signal
	// Wire.send(0x0);
 //  Wire.send(0x0); 				//control/status1
 //  Wire.send(0x0); 				//control/status2
 //  Wire.endTransmission();  
}

void setTime(char input_hour, char input_minute, char input_sec)
{
 //  Wire.beginTransmission(Rtcc_Addr);	// Issue I2C start signal
 //  Wire.send(RTCC_SEC_ADDR);   	// send addr low char, req'd

 //  Wire.send(decToBcd(sec)); 		//set seconds
 //  Wire.send(decToBcd(minute));	//set minutes
 //  Wire.send(decToBcd(hour));		//set hour
	// Wire.endTransmission();
  unsigned char abuf;
  unsigned char wbuf;

  abuf = RTCC_SEC_ADDR;
  wbuf = decToBcd(input_sec);
  i2c_io (Rtcc_Addr, &abuf, 1, &wbuf, 1, NULL, 0);
  _delay_ms(10);

  abuf = RTCC_MIN_ADDR;
  wbuf = decToBcd(input_minute);
  i2c_io (Rtcc_Addr, &abuf, 1, &wbuf, 1, NULL, 0);
  _delay_ms(10);

  abuf = RTCC_HR_ADDR;
  wbuf = decToBcd(input_hour);
  i2c_io (Rtcc_Addr, &abuf, 1, &wbuf, 1, NULL, 0);
  _delay_ms(10);
}

void setDate(char input_day, char input_weekday, char input_month, char input_century, char input_year)
{
    /* year val is 00 to 99, xx
        with the highest bit of month = century
        0=20xx
        1=19xx
        */
  month = decToBcd(input_month);
  if (input_century == 1){
      month |= RTCC_CENTURY_MASK;
  }
  else {
      month &= ~RTCC_CENTURY_MASK;
  }
    // Wire.beginTransmission(Rtcc_Addr);    // Issue I2C start signal
    // Wire.send(RTCC_DAY_ADDR);
    // Wire.send(decToBcd(day));            //set day
    // Wire.send(decToBcd(weekday));    //set weekday
    // Wire.send(month);                         //set month, century to 1
    // Wire.send(decToBcd(year));        //set year to 99
    // Wire.endTransmission();
  unsigned char abuf;
  unsigned char wbuf;

  abuf = RTCC_DAY_ADDR;
  wbuf = decToBcd(input_day);
  i2c_io (Rtcc_Addr, &abuf, 1, &wbuf, 1, NULL, 0);
  _delay_ms(10);

  abuf = RTCC_WEEKDAY_ADDR;
  wbuf = decToBcd(input_weekday);
  i2c_io (Rtcc_Addr, &abuf, 1, &wbuf, 1, NULL, 0);
  _delay_ms(10);

  abuf = RTCC_MONTH_ADDR;
  wbuf = decToBcd(input_month);
  i2c_io (Rtcc_Addr, &abuf, 1, &wbuf, 1, NULL, 0);
  _delay_ms(10);

  abuf = RTCC_YEAR_ADDR;
  wbuf = decToBcd(input_year);
  i2c_io (Rtcc_Addr, &abuf, 1, &wbuf, 1, NULL, 0);
  _delay_ms(10);
}

/* enable alarm interrupt
 * whenever the clock matches these values an int will
 * be sent out pin 3 of the Pcf8563 chip
 */
// void enableAlarm()
// {

//     //set status2 AF val to zero
//     status2 &= ~RTCC_ALARM_AF;
//     //enable the interrupt
//     status2 |= RTCC_ALARM_AIE;

//     //enable the interrupt
//     // Wire.beginTransmission(Rtcc_Addr);  // Issue I2C start signal
//     // Wire.send(RTCC_STAT2_ADDR);
//     // Wire.send(status2);
//     // Wire.endTransmission();
// }


/*
* Read status char
* internal usage only here. see alarmEnabled, alarmActive.
*/
char readStatus2()
{
    /* set the start char of the status 2 data */
    // Wire.beginTransmission(Rtcc_Addr);
    // Wire.send(RTCC_STAT2_ADDR);
    // Wire.endTransmission();

    // Wire.requestFrom(Rtcc_Addr, 1); //request 1 chars
    // return Wire.read();
  return 0;
}

/*
* Returns true if AIE is on
*
*/
bool alarmEnabled()
{
    return readStatus2() & RTCC_ALARM_AIE;
}

/*
* Returns true if AF is on
*
*/
bool alarmActive()
{
    return readStatus2() & RTCC_ALARM_AF;
}


/* set the alarm values
 * whenever the clock matches these values an int will
 * be sent out pin 3 of the Pcf8563 chip
 */
// void setAlarm(char min, char hour, char day, char weekday)
// {
//     if (min <99) {
//         min = constrain(min, 0, 59);
//         min = decToBcd(min);
//         min &= ~RTCC_ALARM;
//     } else {
//         min = 0x0; min |= RTCC_ALARM;
//     }

//     if (hour <99) {
//         hour = constrain(hour, 0, 23);
//         hour = decToBcd(hour);
//         hour &= ~RTCC_ALARM;
//     } else {
//         hour = 0x0; hour |= RTCC_ALARM;
//     }

//     if (day <99) {
//         day = constrain(day, 1, 31);
//         day = decToBcd(day); day &= ~RTCC_ALARM;
//     } else {
//         day = 0x0; day |= RTCC_ALARM;
//     }

//     if (weekday <99) {
//         weekday = constrain(weekday, 0, 6);
//         weekday = decToBcd(weekday);
//         weekday &= ~RTCC_ALARM;
//     } else {
//         weekday = 0x0; weekday |= RTCC_ALARM;
//     }

//     enableAlarm();

//     //TODO bounds check  the inputs first
//     // Wire.beginTransmission(Rtcc_Addr);    // Issue I2C start signal
//     // Wire.send(RTCC_ALRM_MIN_ADDR);
//     // Wire.send(min);                //minute alarm value reset to 00
//     // Wire.send(hour);                //hour alarm value reset to 00
//     // Wire.send(day);                //day alarm value reset to 00
//     // Wire.send(weekday);            //weekday alarm value reset to 00
//     // Wire.endTransmission();
// }

/**
* Get alarm, set values to RTCC_NO_ALARM (99) if alarm flag is not set
*/
// void getAlarm()
// {
//     /* set the start char of the alarm data */
//     // Wire.beginTransmission(Rtcc_Addr);
//     // Wire.send(RTCC_ALRM_MIN_ADDR);
//     // Wire.endTransmission();

//     // Wire.requestFrom(Rtcc_Addr, 4); //request 4 chars
//     // alarm_minute = Wire.read();
//     if(B(10000000) & alarm_minute){
//         alarm_minute = RTCC_NO_ALARM;
//     } else {
//         alarm_minute = bcdToDec(alarm_minute & B(01111111));
//     }
//     // alarm_hour = Wire.read();
//     if(B(10000000) & alarm_hour){
//         alarm_hour = RTCC_NO_ALARM;
//     } else {
//         alarm_hour = bcdToDec(alarm_hour & B(00111111));
//     }
//     // alarm_day = Wire.read();
//     if(B(10000000) & alarm_day){
//         alarm_day = RTCC_NO_ALARM;
//     } else {
//         alarm_day = bcdToDec(alarm_day  & B(00111111));
//     }
//     // alarm_weekday = Wire.read();
//     if(B(10000000) & alarm_weekday){
//         alarm_weekday = RTCC_NO_ALARM;
//     } else {
//         alarm_weekday = bcdToDec(alarm_weekday  & B(00000111));
//     }
// }

/**
* Set the square wave pin output
*/
// void setSquareWave(char frequency)
// {
//     // Wire.beginTransmission(Rtcc_Addr);    // Issue I2C start signal
//     // Wire.send(RTCC_CLKOUT_ADDR);
//     // Wire.send(frequency);
//     // Wire.endTransmission();
// }

// void clearSquareWave()
// {
//     setSquareWave(SQW_DISABLE);
// }

/**
* Reset the alarm leaving interrupt unchanged
*/
// void resetAlarm()
// {
//     //set status2 AF val to zero to reset alarm
//     status2 &= ~RTCC_ALARM_AF;
//     // Wire.beginTransmission(Rtcc_Addr);
//     // Wire.send(RTCC_STAT2_ADDR);
//     // Wire.send(status2);
//     // Wire.endTransmission();
// }


// void clearAlarm()
// {
// 	//set status2 AF val to zero to reset alarm 
// 	status2 &= ~RTCC_ALARM_AF;
// 	//turn off the interrupt
// 	status2 &= ~RTCC_ALARM_AIE;
		
//  //  Wire.beginTransmission(Rtcc_Addr);
// 	// Wire.send(RTCC_STAT2_ADDR);
//  //  Wire.send(status2); 
//  //  Wire.endTransmission();  
// }

/* call this first to load current date values to variables */
void getDate()
{  
	/* set the start char of the date data */
	// Wire.beginTransmission(Rtcc_Addr);
 // 	Wire.send(RTCC_DAY_ADDR);
 // 	Wire.endTransmission();
  	
 // 	Wire.requestFrom(Rtcc_Addr, 4); //request 4 chars
	//0x3f = 0b00111111
	// day = bcdToDec(Wire.receive() & 0x3f);
	//0x07 = 0b00000111
	// weekday = bcdToDec(Wire.receive() & 0x07);
	//get raw month data char and set month and century with it.
	// month = Wire.receive();
	// if (month & RTCC_CENTURY_MASK) {
	// 	century = 1;
	// }
	// else {
	// 	century = 0;
	// }
	// //0x1f = 0b00011111
	// month = month & 0x1f;
	// month = bcdToDec(month);
	// year = bcdToDec(Wire.receive());  
  unsigned char rbuf;
  unsigned char abuf;

  abuf = RTCC_DAY_ADDR;
  uint8_t status = i2c_io(RTCC_R, &abuf, 1, NULL, 0, &rbuf, 1);
  _delay_ms(5);
  if(status==0){
    day = bcdToDec(rbuf & 0x3f);
  }

  abuf = RTCC_WEEKDAY_ADDR;
  status = i2c_io(RTCC_R, &abuf, 1, NULL, 0, &rbuf, 1);
  _delay_ms(5);
  if(status==0){
    weekday = bcdToDec(rbuf & 0x07);
  }

  abuf = RTCC_MONTH_ADDR;
  status = i2c_io(RTCC_R, &abuf, 1, NULL, 0, &rbuf, 1);
  _delay_ms(5);
  if(status==0){
    month = bcdToDec(rbuf & 0x1f);
  }

  abuf = RTCC_YEAR_ADDR;
  status = i2c_io(RTCC_R, &abuf, 1, NULL, 0, &rbuf, 1);
  _delay_ms(5);
  if(status==0){
    year = bcdToDec(rbuf);
  }
}


/* call this first to load current time values to variables */
void getTime()
{  
	/* set the start char , get the 2 status chars */
	// Wire.beginTransmission(Rtcc_Addr);
 // 	Wire.send(RTCC_STAT1_ADDR);
 // 	Wire.endTransmission();
  	
 // 	Wire.requestFrom(Rtcc_Addr, 5); //request 5 chars
 // 	status1 = Wire.receive();
 // 	status2 = Wire.receive();
 // 	0x7f = 0b01111111
 // 	sec = bcdToDec(Wire.receive() & 0x7f);
	// minute = bcdToDec(Wire.receive() & 0x7f);
	// 0x3f = 0b00111111
	// hour = bcdToDec(Wire.receive() & 0x3f);
  unsigned char rbuf;
  unsigned char abuf;

  abuf = RTCC_SEC_ADDR;
  uint8_t status = i2c_io(RTCC_R, &abuf, 1, NULL, 0, &rbuf, 1);
  _delay_ms(5);
  if(status==0){
    second = bcdToDec(rbuf & 0x7f);
  }

  abuf = RTCC_MIN_ADDR;
  status = i2c_io(RTCC_R, &abuf, 1, NULL, 0, &rbuf, 1);
  _delay_ms(5);
  if(status==0){
    minute = bcdToDec(rbuf & 0x7f);
  }

  abuf = RTCC_HR_ADDR;
  status = i2c_io(RTCC_R, &abuf, 1, NULL, 0, &rbuf, 1);
  _delay_ms(5);
  if(status==0){
    hour = bcdToDec(rbuf & 0x3f);
  }
}

// char *version(){
//   return RTCC_VERSION;  
// }

// char *formatTime(char style)
// {
// 	getTime();
// 	switch (style) {
// 		case RTCC_TIME_HM:
// 			strOut[0] = '0' + (hour / 10);
// 		 	strOut[1] = '0' + (hour % 10);
// 		 	strOut[2] = ':';
// 			strOut[3] = '0' + (minute / 10);
// 		 	strOut[4] = '0' + (minute % 10);
// 		 	strOut[5] = '\0';
// 			break;
// 		case RTCC_TIME_HMS:
// 		default:
// 			strOut[0] = '0' + (hour / 10);
// 		 	strOut[1] = '0' + (hour % 10);
// 		 	strOut[2] = ':';
// 			strOut[3] = '0' + (minute / 10);
// 		 	strOut[4] = '0' + (minute % 10);
// 		 	strOut[5] = ':';
// 			strOut[6] = '0' + (sec / 10);
// 		 	strOut[7] = '0' + (sec % 10);
// 		 	strOut[8] = '\0';
//  			break;
// 		}
//  	return strOut;
// }
 

// char *formatDate(char style)
// {
// 	getDate();
	
// 		switch (style) {
		
// 		case RTCC_DATE_ASIA:
// 			//do the asian style, yyyy-mm-dd
// 			if ( century == 1 ){
// 			 	strDate[0] = '1';
// 			 	strDate[1] = '9';
// 		 	}
// 			else {
// 				strDate[0] = '2';
// 				strDate[1] = '0';
// 			}
// 			strDate[2] = '0' + (year / 10 );
// 		 	strDate[3] = '0' + (year % 10);
// 		 	strDate[4] = '-';	
// 			strDate[5] = '0' + (month / 10);
// 		 	strDate[6] = '0' + (month % 10);
// 		 	strDate[7] = '-';
// 			strDate[8] = '0' + (day / 10);
// 		 	strDate[9] = '0' + (day % 10);
// 		 	strDate[10] = '\0';
// 			break;
// 		case RTCC_DATE_US: 
// 	  //the pitiful US style, mm/dd/yyyy
// 			strDate[0] = '0' + (month / 10);
// 		 	strDate[1] = '0' + (month % 10);
// 		 	strDate[2] = '/';
// 			strDate[3] = '0' + (day / 10);
// 		 	strDate[4] = '0' + (day % 10);
// 		 	strDate[5] = '/';
// 		 	if ( century == 1 ){
// 			 	strDate[6] = '1';
// 			 	strDate[7] = '9';
// 		 	}
// 			else {
// 				strDate[6] = '2';
// 				strDate[7] = '0';
// 			}
// 			strDate[8] = '0' + (year / 10 );
// 		 	strDate[9] = '0' + (year % 10);
// 		 	strDate[10] = '\0';
// 		 	break;
// 		case RTCC_DATE_WORLD:
// 		default:
// 			//do the world style, dd-mm-yyyy
// 			strDate[0] = '0' + (day / 10);
// 		 	strDate[1] = '0' + (day % 10);
// 		 	strDate[2] = '-';
// 			strDate[3] = '0' + (month / 10);
// 		 	strDate[4] = '0' + (month % 10);
// 		 	strDate[5] = '-';
			
// 		 	if ( century == 1 ){
// 			 	strDate[6] = '1';
// 			 	strDate[7] = '9';
// 		 	}
// 			else {
// 				strDate[6] = '2';
// 				strDate[7] = '0';
// 			}
// 			strDate[8] = '0' + (year / 10 );
// 		 	strDate[9] = '0' + (year % 10);
// 		 	strDate[10] = '\0';
// 			break; 	
		
// 	}
//  	return strDate;
// }

unsigned char getSecond() {	  
 //  getTime();
	// return sec;	
  unsigned char rbuf;
  unsigned char abuf;

  abuf = RTCC_SEC_ADDR;
  uint8_t status = i2c_io(RTCC_R, &abuf, 1, NULL, 0, &rbuf, 1);
  _delay_ms(5);
  while(status!=0){
    status = i2c_io(RTCC_R, &abuf, 1, NULL, 0, &rbuf, 1);
  }
  second = bcdToDec(rbuf & 0x7f);
  return second;
}

unsigned char getMinute() {
 //  getTime();
	// return minute;
  unsigned char rbuf;
  unsigned char abuf;

  abuf = RTCC_MIN_ADDR;
  uint8_t status = i2c_io(RTCC_R, &abuf, 1, NULL, 0, &rbuf, 1);
  _delay_ms(5);
  while(status!=0){
    status = i2c_io(RTCC_R, &abuf, 1, NULL, 0, &rbuf, 1);
  }
  minute = bcdToDec(rbuf & 0x7f);
  return minute;
}

unsigned char getHour() {
  // getTime();
  // return hour;
  unsigned char rbuf;
  unsigned char abuf;

  abuf = RTCC_HR_ADDR;
  uint8_t status = i2c_io(RTCC_R, &abuf, 1, NULL, 0, &rbuf, 1);
  _delay_ms(5);
  while(status!=0){
    status = i2c_io(RTCC_R, &abuf, 1, NULL, 0, &rbuf, 1);
  }
  hour = bcdToDec(rbuf & 0x7f);
  return hour;
}

// char getAlarmMinute() {
//     getAlarm();
//     return alarm_minute;
// }

// char getAlarmHour() {
//     getAlarm();
//     return alarm_hour;
// }

// char getAlarmDay() {
//     getAlarm();
//     return alarm_day;
// }

// char getAlarmWeekday() {
//     getAlarm();
//     return alarm_weekday;
// }

unsigned char getDay() {
  getDate();
	return day;
}

unsigned char getMonth() {
	getDate();
  return month;
}

unsigned char getYear() {
  getDate();
	return year;
}

unsigned char getWeekday() {
  getDate();
	return weekday;
}

// char getStatus1() {
// 	return status1;
// }

// char getStatus2() {
// 	return status2;
// }