#include <TimerOne.h> // 시간 참조
#include <Wire.h>  
#include <LiquidCrystal_I2C.h> //lcd 참조
#include <EEPROM.h>
#include "pitches.h"
#include <SoftwareSerial.h>
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
SoftwareSerial mySerial(2,3);

char choose=0; //선택의 기로
char k=0;       //노래  선택의 기로   
int lcd_key     = 0;
int adc_key_in  = 0;

  int old_state=0;
  int state=0;
  LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
//int8_t h
typedef struct {
  char ampm;  //4
  int8_t hours;  //5
  int8_t minutes; //6
  int8_t seconds;  //7

  char ampm1;  //8
  int8_t hours1;  //9
  int8_t minutes1; //10
  int8_t seconds1; //11
  }Time;         //시,분,초 넣을 구조체 Time

Time ctime ={0,0,0};  // current time

void bear3()
{
   int melody[] = {
  NOTE_C5,NOTE_C5,NOTE_C5,NOTE_C5,NOTE_C5,               //도도도도도
  NOTE_E5,NOTE_G5,NOTE_G5,NOTE_E5,NOTE_C5,               //미솔솔미도
  NOTE_G5,NOTE_G5,NOTE_E5,NOTE_G5,NOTE_G5,NOTE_E5,       //솔솔미솔솔미
  NOTE_C5,NOTE_C5,NOTE_C5,                               //도도도
  NOTE_G5,NOTE_G5,NOTE_E5,NOTE_C5,                       //솔솔미도
  NOTE_G5,NOTE_G5,NOTE_G5,                               //솔솔솔
  NOTE_G5,NOTE_G5,NOTE_E5,NOTE_C5,                       //솔솔미도
  NOTE_G5,NOTE_G5,NOTE_G5,                               //솔솔솔
  NOTE_G5,NOTE_G5,NOTE_E5,NOTE_C5,                       //솔솔미도
  NOTE_G5,NOTE_G5,NOTE_G5,NOTE_A5,NOTE_G5,               //솔솔솔라솔
  NOTE_C6,NOTE_G5,NOTE_C6,NOTE_G5,                       //도솔도솔
  NOTE_E5,NOTE_D5,NOTE_C5                                //미레도
  };

  int noteDurations[]={
  4,8,8,4,4,
  4,8,8,4,4,
  8,8,4,8,8,4,
  4,4,2,
  4,4,4,4,
  4,4,2,
  4,4,4,4,
  4,4,2,
  4,4,4,4,
  8,8,8,8,2,
  4,4,4,4,
  4,4,2
  };
  
  for (int i = 0; i < 49; i++) {
    lcd_key = read_LCD_buttons();
    int Durations = 1000/noteDurations[i];    // 음계의 음길이 계산
    tone(8, melody[i], Durations);    
    int pauseBetweenNotes = Durations *1.3 ;
    delay(pauseBetweenNotes);
    noTone(8);
    if(lcd_key == 4)
      break;
  }
  
  
  }

void mario(){

int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
};
//Mario main them tempo
int tempo[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};

  for (int i = 0; i < 78; i++) {
    lcd_key = read_LCD_buttons();
    int Durations = 1000/tempo[i];    // 음계의 음길이 계산
    tone(8, melody[i], Durations);    
    int pauseBetweenNotes = Durations *1.3 ;
    delay(pauseBetweenNotes);
    noTone(8);
     if(lcd_key == 4)
      break;
  }



}


void mari0_under(){



int underworld_melody[] = {
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_DS4,
  NOTE_DS4, NOTE_GS3,
  NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,
  NOTE_AS3, NOTE_A3, NOTE_GS3,
  0, 0, 0
};
//Underwolrd tempo
int underworld_tempo[] = {
  12, 12, 12, 12,
  12, 12, 6,
  3,      
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  6, 18, 18, 18,
  6, 6,
  6, 6,
  6, 6,
  18, 18, 18, 18, 18, 18,
  10, 10, 10,
  10, 10, 10,
  3, 3, 3
};

for (int i = 0; i < 78; i++) {
    lcd_key = read_LCD_buttons();
    int Durations = 1000/underworld_tempo[i];    // 음계의 음길이 계산
    tone(8, underworld_melody[i], Durations);    
    int pauseBetweenNotes = Durations *1.3 ;
    delay(pauseBetweenNotes);
    noTone(8);
     if(lcd_key == 4)
      break;
  }



}

 char str[20]; //시계 들어갈 배열
 char str2[5]; //시계AMPM
 char str15[20]; //알람시계
 char str20[5]={"AM"};  //알람ampm
 char x =0; // ampm 구분할 변수
 char count=0; //시간 재는 변수
 static char i =0;

char key_in=0;
char key_X=0;

char input='0';


 char read_LCD_buttons()   //버튼설정
 {
  
   adc_key_in=analogRead(0);
   input=mySerial.read();
    if(input=='U')
    return lcd_key=btnUP;
    else if(input=='D')
    return lcd_key=btnDOWN;
    else if(input=='R')
    return lcd_key=btnRIGHT;
    else if(input=='L')
    return  lcd_key=btnLEFT;
    else if(input=='S')
     return lcd_key=btnSELECT;
  if(adc_key_in ==0)
  {
    state = 1;
    if(old_state != state)
    {
      old_state = state;
      return btnUP;
    }
    lcd_key = 5;
  }
  
  else if(adc_key_in >320 && adc_key_in <330)
  {
    state = 1;
    if(old_state != state)
    {
      old_state = state;
      return btnLEFT; 
    }
     lcd_key = 5;
  }
  
  else if(adc_key_in >138 && adc_key_in <141)
  {
    state = 1;
    if(old_state != state)
    {
      old_state = state;
      return btnDOWN; 
    }
   
    lcd_key = 5;
  }
else if(adc_key_in >490 && adc_key_in <505)
  {
    state = 1;
    if(old_state != state)
    {
      old_state = state;
      return btnRIGHT; 
    }
    lcd_key = 5;
  }
  else if(adc_key_in >720 && adc_key_in <740)
  {
    state = 1;
    if(old_state != state)
    {
      old_state = state;
      return btnSELECT; 
    }
   
    lcd_key = 5;
  }

  else
  {
    state = 0;
    old_state = 0;
    return btnNONE;
  }
 

 }
  
  
  


void display_current() //현재시간 띄우기
{
  lcd_key=read_LCD_buttons();
  lcd.backlight();
  lcd.setCursor(0,0);
  sprintf(str,"%s %02d : %02d : %02d",str2,ctime.hours,ctime.minutes,ctime.seconds);
  lcd.print(str);
  lcd.setCursor(0,1);
  lcd.print("Current time      ");
  Serial.print(lcd_key);
 switch (lcd_key)               // 버튼 판단
 {
   case btnRIGHT:  //0
      
      break;
   case btnLEFT :  //3
    
     break;
   case btnUP :
     
      break;
   case btnSELECT:
  {  
    lcd.clear();
    choose=1;
  }
 case btnNONE:
    {
       
    }
   break;
  
  
  }
}

void display_present()  //현재시간 수정
{
  lcd_key=read_LCD_buttons();
  lcd.backlight();
  lcd.setCursor(0,0);
  sprintf(str,"%s %02d : %02d : %02d",str2,ctime.hours,ctime.minutes,ctime.seconds);
  lcd.print(str);
  lcd.setCursor(0,1);
  lcd.print("Current_SET");
  Serial.print(lcd_key);
 switch (lcd_key)               // 버튼 판단
 {
   case btnRIGHT:  //0
      i++;
      break;
   case btnLEFT :  //3
     i--;
     break;
   case btnUP :
     if(i == 0)
      {
        if(x==0){
        sprintf(str2,"%c%c",80,77);
        x=1;  
        }
        else if(x==1){
        sprintf(str2,"%c%c",65,77);
        x=0;
      }
        
      }
      else if(i == 3 || i ==4)
      {
        ctime.hours++;
        if(ctime.hours > 12)
        {
          ctime.hours = 0;
        }
        return ctime.hours;
      }
     
      else if(i == 8 || i ==9)
      {
        ctime.minutes++;
        if(ctime.minutes > 60)
        {
          ctime.minutes = 0;
        }
      }
       break;

   case btnDOWN :
      if(i == 0)
      {
           if(x==1){
        sprintf(str2,"%c%c",80,77);
        x=1;  
        }
        else if(x==0){
        sprintf(str2,"%c%c",65,77);
        x=0;
      }
        
      }
      else if(i == 3 || i ==4)
      {
        ctime.hours--;
        if(ctime.hours <0)
        {
          ctime.hours = 12;
        }
      }
      else if(i == 8 || i ==9)
      {
        ctime.minutes--;
        if(ctime.minutes <0)
        {
          ctime.minutes = 59;
        }
      }
      break;
   case btnSELECT:
  {
   
    lcd.clear();
    choose=2;
  }
 case btnNONE:
    {
        lcd.setCursor(i,0);
        lcd.blink();
        delay(100);
    }
   break;
}
}


void display_alarm()   //알람시간 수정
{
  
  lcd_key=read_LCD_buttons();
  lcd.backlight();
  lcd.setCursor(0,0);
 
  
  sprintf(str15,"%s  %02d : %02d : %02d  ",str20,ctime.hours1,ctime.minutes1,ctime.seconds1);
  lcd.print(str15);
  lcd.setCursor(0,1);
  lcd.print("ALARM_SET ");
  lcd.setCursor(i,0);
  lcd.blink();
  delay(100);
   switch (lcd_key)               // 버튼 판단
   {
   Serial.print(lcd_key);
   case btnRIGHT:  //0
      
      i++;
      if( i > 12)
      {
        i = 0;
      }
    break;

 
   case btnLEFT :  //3
     i--;
      if( i < 0)
      {
        i = 12;
      }
     break;
   case btnUP :
     if(i == 0)
      {
        if(x==0){
        sprintf(str20,"%c%c",80,77);
        x=1;  
        }
        else if(x==1){
        sprintf(str20,"%c%c",65,77);
        x=0;
      }
        
      }
      else if(i == 4 || i ==5)
      {
        ctime.hours1++;
        if(ctime.hours1 > 12)
        {
          ctime.hours1 = 0;
        }//return ctime.hours1;
      }
     
      else if(i == 9 || i ==10)
      {
        ctime.minutes1++;
        if(ctime.minutes1 > 60)
        {
          ctime.minutes1 = 0;
        }
      }
       break;

   case btnDOWN :
      if(i == 0)
      {
        if(x==1){
        sprintf(str20,"%c%c",80,77);
        x=1;  
        }
        else if(x==0){
        sprintf(str20,"%c%c",65,77);
        x=0;
      }
        
      }
      else if(i == 4 || i ==5)
      {
        ctime.hours1--;
        if(ctime.hours1 <0)
        {
          ctime.hours1 = 12;
        }
      }
      else if(i == 9 || i ==10)
      {
        ctime.minutes1--;
        if(ctime.minutes1 <0)
        {
          ctime.minutes1 = 59;
        }
      }
      break;
 case btnSELECT:
  {     
    EEPROM.write(4,ctime.ampm1);
    EEPROM.write(5,ctime.hours1);
    EEPROM.write(6,ctime.minutes1);
    EEPROM.write(7,ctime.seconds1);
    lcd.clear();
    choose=3;
 }
    case btnNONE:
    {
        lcd.setCursor(i,0);
        lcd.blink();
        delay(100);
    }
   break;
  }
}


void alram_music_choose()  //알람음악 설정
{
  lcd_key=read_LCD_buttons();
  lcd.setCursor(0, 0);
    lcd.print("Music Select    ");
    lcd.setCursor(0, 1);
    lcd.print("1   ");
    lcd.print("2   ");
    lcd.print("3     ");
    lcd.setCursor(i, 1);
 switch (lcd_key)               // 버튼 판단
 {
   case btnRIGHT:  //0
      
      i++;
      if( i > 12)
      {
        i = 0;
      }
      //delay(1000);
   break;

 
   case btnLEFT :  //3
     i--;
      if( i < 0)
      {
        i = 12;
      }
     // delay(1000);
      break;
   case btnUP :
      
       break;

   case btnDOWN :
      
      break;
   case btnSELECT:
       if (i == 0)
        {
            k = 1; //1번노래
        }
        else if (i == 4)
        {
           k = 2; //2번노래
        }
        else if (i == 8)
        {
            k = 3; //3번노래
        }
        else
        {
            break;
        }
        EEPROM.write(10, k);     //알람소리를 EEPROM에 저장
        lcd.clear();
        choose = 0; 
    
    
    
    break;
    case btnNONE:
    {
        lcd.setCursor(i,1);
        lcd.blink();
        delay(100);
    }
   
  
   break;

  
  
  
  
  }
}
 

void timerIsr()  //시간설정
{
  count++;

  sprintf(str,"%s %02d : %02d : %02d",str2,ctime.hours,ctime.minutes,ctime.seconds);  
     
  
  if(count%100==0){
    ctime.seconds++;

    if(ctime.seconds%10==0)
    {
      EEPROM.write(0,ctime.ampm);
      EEPROM.write(1,ctime.hours);
      EEPROM.write(2,ctime.minutes);
      EEPROM.write(3,ctime.seconds);
    }                                 //10초마다 eeprom에 ctime값을 주소 4에 저장
    
    if(ctime.seconds>=60){
      ctime.minutes++;
      ctime.seconds=0;  
    }
    if(ctime.minutes>=60){
      ctime.hours++;
      ctime.minutes=0;
    }
    if(ctime.hours>=12){
      ctime.hours=0;
      if(x==0){
        sprintf(str2,"%c%c",'P','M');
        x=1;  
      }
      else if(x==1){
        sprintf(str2,"%c%c",'A','M');
        x=0;
      }
    }
     
    sprintf(str,"%s %02d : %02d : %02d",str2,ctime.hours,ctime.minutes,ctime.seconds);  
  }
}

void setup() {
   Serial.begin(9600);
   lcd.init();
   Timer1.initialize(10000);
   Timer1.attachInterrupt(timerIsr);
   sprintf(str2,"%c%c",65,77);   //AMPM
   mySerial.begin(9600);
   ctime.ampm=EEPROM.read(0);
   ctime.hours=EEPROM.read(1);
   ctime.minutes=EEPROM.read(2);
   ctime.seconds=EEPROM.read(3);

   ctime.ampm1=EEPROM.read(4);
   ctime.hours1=EEPROM.read(5);
   ctime.minutes1=EEPROM.read(6);
   ctime.seconds1=EEPROM.read(7);

   
} 

void loop() {
  //Serial.println(lcd_key);
  //lcd_key=read_LCD_buttons();

 while(choose==0){
  display_current();

      if (strcmp(str2,str20)== 0&&ctime.hours == ctime.hours1 && ctime.minutes == ctime.minutes1 && ctime.seconds == ctime.seconds1){
        if (k == 1)
        {
            lcd.setCursor(0, 0);
            lcd.print("ALARM!! ALARM!!");
            lcd.setCursor(0, 1);
            lcd.print("ALARM!! ALARM!!");
            bear3();
        }
        else if (k == 2)
        {
            lcd.setCursor(0, 0);
            lcd.print("ALARM!! ALARM!!");
            lcd.setCursor(0, 1);
            lcd.print("ALARM!! ALARM!!");
            mario();
        }
        else if (k == 3)
        {
            lcd.setCursor(0, 0);
            lcd.print("ALARM!! ALARM!!");
            lcd.setCursor(0, 1);
            lcd.print("ALARM!! ALARM!!");
            mari0_under();
        }
        delay(100);
    }
  }

    
 while(choose==1)
 {
  display_present();
 }
  while(choose==2)
  {
    display_alarm();
  }   
 while(choose==3)    { 
    alram_music_choose();
 }

  
  }

 
