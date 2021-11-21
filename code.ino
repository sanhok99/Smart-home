int r1,r2,i_loopCount=0,j_loopCount=0;
int entry_count=0;
int exit_count=0;
int result=0;
int first_ir;
int second_ir;
int on=3,off=4,flag=0;
#include <TimeLib.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
void setup()
{
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  pinMode(7,INPUT);
  pinMode(8,INPUT);
  pinMode(on,OUTPUT);
  pinMode(off,OUTPUT);
  Serial.println(entry_count);
  Serial.println(exit_count);
  digitalWrite(on,HIGH);
  digitalWrite(off,LOW);
  lcd.setCursor(0,0);
  lcd.print("Project by");
  lcd.setCursor(1,7);
  lcd.print("Shounak");
}
void loop()
{
  r1=digitalRead(7);
  delay(5);
  r2=digitalRead(8);
  if(r1==0 && r2!=0) //while entering the first sensor is high and the second switch is low
  {
	  r2=digitalRead(8); //read the second sensor's input
	  Serial.println("first read first ");
	  while(r2!=0) //wait till the second sensor gets high
	  {
	  if( i_loopCount==1500)
	  {
	  Serial.print(i_loopCount);
	  i_loopCount=0;
	  Serial.println("Time up SIR. For first sensor");
	  break;
	  }
	  r2=digitalRead(8);
	  i_loopCount=i_loopCount+1;
	  Serial.println(i_loopCount);
	  }
	  if(r2==0)
	  {
		  flag=1;
		  entry_count=entry_count+1;
		  lcd.begin();
		  lcd.setCursor(0,0);
		  lcd.print("Entry Number ");
		  lcd.setCursor(13,0);
		  lcd.print(entry_count);
		  Serial.println("second read");
		  i_loopCount=0;
	  }
	  else if(r2!=0)
	  {
	 	 r1=0;
	  }
  }
  else if(r1!=0 && r2==0) //while exiting the second sensor is high and the first sensor is low
  {
	  r1=digitalRead(7); //reading the first sensor
	  Serial.println("second read first ");
	  //Serial.println(s_ir_second);
	  while(r1!=0) //waiting for the first sensor to get high
	  {
		  if( j_loopCount==1500)
		  {
			  Serial.print(j_loopCount);
			  j_loopCount=0;
			  Serial.println(" Time up SIR. For second sensor");
			  break;
		  }
		  r1=digitalRead(7);
		  j_loopCount=j_loopCount+1;
		  Serial.println(j_loopCount);
	  }
	  if(r1==0)
	  {
		  flag=1;
		  exit_count=exit_count+1;
		  lcd.begin();
		  lcd.setCursor(0,0);
		  lcd.print("Exit Number ");
		  lcd.setCursor(12,0);
		  lcd.print(exit_count);
		  Serial.println("first read");
		  j_loopCount=0;
	  }
	  else
	  {
	  	r2=0;
	  }
  }
  if(flag==1&&result>=0)
  {
	  flag=0;
	  result=entry_count-exit_count; //calculating the result
	  if(result>=0)
	  {
		  if(result==1)
		  {
			  digitalWrite(off,HIGH);
			  digitalWrite(on,LOW);
			  delay(100);
			  digitalWrite(on,HIGH);  
		  }
		  else if(result==0)
		  {
			  digitalWrite(off,LOW);
			  delay(100);
			  digitalWrite(off,HIGH);
		  }
		  Serial.print("total ");
		  Serial.println(result);
		  lcd.begin();
		  lcd.setCursor(4,0);
		  lcd.print("Total ");
		  lcd.setCursor(10,0);
		  lcd.print(result);
	  }
	  else if(result<0)
	  {
		  Serial.print(result);
		  Serial.print(" ");
		  lcd.begin();
		  lcd.setCursor(0,0);
		  lcd.print("Abnormal issue");
		  lcd.setCursor(3,1);
		  lcd.print("...FIXED...");
		  result=0;
		  exit_count=0;
		  entry_count=0;
		  Serial.println(result);
		}
  	}
}
