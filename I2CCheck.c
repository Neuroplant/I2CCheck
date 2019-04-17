#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>
#include <pcf8574.h>
#include <pca9685.h>
#include <wiringPiI2C.h>
#include <lcd.h>

#define DEV_LCD		0x27
#define BASE_LCD  	64
#define RS        	BASE_LCD+0 
#define RW 			BASE_LCD+1 
#define EN 			BASE_LCD+2 
#define LED 		BASE_LCD+3 
#define D4 			BASE_LCD+4 
#define D5 			BASE_LCD+5 
#define D6 			BASE_LCD+6 
#define D7 			BASE_LCD+7

#define DEV_PWM		0x40	
#define BASE_PWM 	128
#define MAX_PWM		4095
#define HERTZ		50

int lcdhd;
int pwmhd;

int main(void) {
  int i;
  if (wiringPiSetup() == -1) {
    printf("wiringPi failed");
  }
  pcf8574Setup(BASE_LCD,DEV_LCD);
  for (i=0;i<8;i++) {
    pinMode(BASE_LCD+i,OUTPUT);
  }
  digitalWrite(LED,HIGH);
  digitalWrite(RW,LOW);
  lcdhd = lcdInit(2,16,4,RS,EN,D4,D5,D6,D7,0,0,0,0);
  if(lcdhd == -1) {
	  printf("LCDInit failed");
	  return 1;
  }
	
	wiringPiI2CSetup(DEV_PWM);
	pwmhd = pca9685Setup(BASE_PWM, DEV_PWM, HERTZ);
	if (pwmhd < 0){
		printf("PWM Modul fail");
		return pwmhd;
	}
	pinMode(7,OUTPUT);
	digitalWrite(7,LOW);
	pcs9685PWMReset(pwmhd);
	for (i=0;i<8;i++) {
		pinMode(BASE_PWM+i,OUTPUT);
	}
	while(1==1) {
		for (i=1;i<PWM_MAX;i++) {
			pwmWrite(BASE_PWM+2,i);
			lcdPosition(lcdhd,0,0);
			lcdPrintf(lcdhd,"Licht %i",i);
		}
	}
}
			
	
